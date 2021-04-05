// Survival by Raikkonen

#include "Main.h"

namespace Survival {

std::list<GAME> Games;
std::list<SURVIVAL> Survivals;

void LoadSurvivalSettings(const std::string& scPluginCfgFile) {
    Games.clear();
    INI_Reader ini;
    if (ini.open(scPluginCfgFile.c_str(), false)) {
        while (ini.read_header()) {
            if (ini.is_header("survival")) {
                SURVIVAL survival;
                while (ini.read_value()) {
                    if (ini.is_value("system")) {
                        survival.iSystemID = CreateID(ini.get_value_string(0));
                    } else if (ini.is_value("pos")) {
                        survival.pos.x = ini.get_value_float(0);
                        survival.pos.y = ini.get_value_float(1);
                        survival.pos.z = ini.get_value_float(2);
                    } else if (ini.is_value("wave")) {
                        uint params = ini.get_num_parameters() - 1;
                        WAVE wave;
                        wave.iReward = ini.get_value_int(0);
                        uint pos = 1;
                        while (pos < params) {
                            std::wstring ship = stows(ini.get_value_string(pos));
                            pos++;
                            int num = ini.get_value_int(pos);
                            pos++;

                            for (int i = 0; i < num; i++)
                                wave.NPCs.push_back(ship);
                        }

                        survival.Waves.push_back(wave);
                    }
                }
                Survivals.push_back(survival);
            }
        }
        ini.close();
    }
}

void ShowPlayerMissionText(uint iClientID, uint iInfocardID,
                           MissionMessageType type) {
    FmtStr caption(0, 0);
    caption.begin_mad_lib(iInfocardID);
    caption.end_mad_lib();

    pub::Player::DisplayMissionMessage(
        iClientID, caption, type, true);
}

bool PlayerChecks(uint iClientID, uint iMember, uint iSystemID) {
    wchar_t *wszActiveCharname =
        (wchar_t *)Players.GetActiveCharacterName(iMember);

    // Check player is in the correct system
    uint iSystemID2;
    pub::Player::GetSystem(iMember, iSystemID2);
    if (iSystemID2 != iSystemID) {
        PrintUserCmdText(iClientID,
                         L"%s needs to be in the "
                         L"System to start a Survival game.",
                         wszActiveCharname);
        return false;
    }
       
    // Check player is in space
    uint iShip;
    pub::Player::GetShip(iMember, iShip);
    if (!iShip) {
        PrintUserCmdText(iClientID, L"%s needs to be in "
                         L"space to start a Survival game.",
                         wszActiveCharname);
        return false;
    }

    // Is the player already in a game?
    for (auto &game : Games) {
        std::vector<uint>::iterator it =
            std::find(game.StoreMemberList.begin(), game.StoreMemberList.end(),
                      iClientID);
        if (it != game.StoreMemberList.end()) {
            PrintUserCmdText(iClientID,
                             L"%s is already in a Surival game.",
                             wszActiveCharname);
            return false;
        }
    }
        
    return true;
}

bool NewGame(uint iClientID, const std::wstring &wscCmd,
             const std::wstring &wscParam, const wchar_t *usage) {
	// Initialise game struct
    GAME game;
    game.iWaveNumber = 0;
    pub::Player::GetSystem(iClientID, game.iSystemID);

    // Is there a game already in this system?
    for (auto &g : Games) {
        if (game.iSystemID == g.iSystemID) {
            PrintUserCmdText(
                iClientID,
                L"There is already a Survival game occuring in this System. Go "
                L"to another System or wait until the game is over");
            return true;
        }
    }

    // Is a survival game possible in this system?
    for (auto &survival : Survivals) {
        if (survival.iSystemID == game.iSystemID) {
            game.Survival = survival;
            break;
        }
        PrintUserCmdText(iClientID,
                         L"There isn't an available game in this System.");
        return true;   
    }

    // Is there anyone in the system who isn't in the group?
    struct PlayerData *pPD = 0;
    while (pPD = Players.traverse_active(pPD)) {
        uint iClientID2 = HkGetClientIdFromPD(pPD);
        uint iClientSystemID = 0;
        pub::Player::GetSystem(iClientID2, iClientSystemID);

        if (game.iSystemID != iClientSystemID) {
            PrintUserCmdText(iClientID, L"There are players in the System who "
                                        L"are not part of your group.");
            return true;
        }
    }

	// Is player in a group?
    game.iGroupID = Players.GetGroupID(iClientID);
    if (game.iGroupID != 0) {
        // Get players in the group
        CPlayerGroup *group = CPlayerGroup::FromGroupID(game.iGroupID);
        st6::vector<unsigned int> tempList;
        group->StoreMemberList(tempList);
        for (auto &player : tempList)
            game.StoreMemberList.push_back(player);
    } else
        // Store just the player
        game.StoreMemberList.push_back(iClientID);
    
       // Check each member of the group passes the checks
    for (auto const &player : game.StoreMemberList) {
        if (!PlayerChecks(iClientID, player, game.iSystemID))
            return true;

        // Beam the players to a point in the system
        Matrix rot = {0.0f, 0.0f, 0.0f};
        HkRelocateClient(player, game.Survival.pos, rot);

        // Play start sound
        pub::Audio::PlaySoundEffect(player,CreateID("rmb_inrangeships_01"));
    }

    NewWave(game);
    Games.push_back(game);
    return true;
}

void NewWave(GAME & game) {
    // Defend yourself!
    for (auto const &player : game.StoreMemberList)
        ShowPlayerMissionText(player, 22612, MissionMessageType_Type2);

    // Spawn NPCS
    uint iShip;
    Vector pos;
    Matrix rot;
    pub::Player::GetShip(game.StoreMemberList.front(), iShip);
    pub::SpaceObj::GetLocation(iShip, pos, rot);

    for (auto &npc : game.Survival.Waves.at(game.iWaveNumber).NPCs) {
        game.iSpawnedNPCs.push_back(Utilities::CreateNPC(npc, pos, rot, game.iSystemID,
                                               true));
        Utilities::Log_CreateNPC(npc);
    }
}

// This is only called when it's an FLHook spawned NPC (see main.cpp)
void NPCDestroyed(CShip *ship) {
    for (auto &game : Games) {

        // Remove NPC if part of a wave
        game.iSpawnedNPCs.remove(ship->get_id());
        
        // If there's no more NPCs, end of the wave
        if (game.iSpawnedNPCs.empty())
            EndWave(game);

        return;
    }
}

void EndWave(GAME & game) {
    // Payout reward
    if (game.iGroupID != 0) {
        CPlayerGroup *group = CPlayerGroup::FromGroupID(game.iGroupID);
        group->RewardMembers(game.Survival.Waves.at(game.iWaveNumber).iReward);
    } else {
        wchar_t *wszActiveCharname = (wchar_t *)Players.GetActiveCharacterName(
            game.StoreMemberList.front());
        HkAddCash(wszActiveCharname,
                  game.Survival.Waves.at(game.iWaveNumber).iReward);
    }
    
    // Increment Wave
    game.iWaveNumber++;

	// Is there a next wave? If so start it on a timer. If not, EndSurvival()
    if (game.iWaveNumber >= game.Survival.Waves.size())
        EndSurvival(game);
    else
        NewWave(game);
}

void EndSurvival(GAME & game) {
    for (auto const &player : game.StoreMemberList) {
        // Mission Result: Success
        ShowPlayerMissionText(player, 1231, MissionMessageType_Type3);
        
        // You did it, area is clear. Good job.
        pub::Audio::PlaySoundEffect(player, CreateID("rmb_success_ships_01"));
    }

	// Red Text Universe 
}

void Disqualify(uint iClientID) {
    // Are they even in a game?
    for (std::list<GAME>::iterator git = Games.begin(); git != Games.end(); git++) {
        std::vector<uint>::iterator it =
            std::find(git->StoreMemberList.begin(), git->StoreMemberList.end(),
                      iClientID);
        if (it != git->StoreMemberList.end()) {

            // Remove from group
            if (git->iGroupID != 0) {
                CPlayerGroup *group = CPlayerGroup::FromGroupID(git->iGroupID);
                group->DelMember(iClientID); // Remove from group
            }

            // Remove from member list
            git->StoreMemberList.erase(it);

            // Mission Failed.
            ShowPlayerMissionText(iClientID, 13085, MissionMessageType_Type3); 

             // Any members left?
            if (git->StoreMemberList.empty())
                Games.erase(git);
            else {
                wchar_t *wszActiveCharname =
                    (wchar_t *)Players.GetActiveCharacterName(iClientID);
                for (auto &player : git->StoreMemberList)
                    PrintUserCmdText(player, L"%s has fled the battle.",
                                     wszActiveCharname);
            }
            return;
        }
    }
}

// Remove from games and show disqualify messages if these hooks occur

void __stdcall DisConnect(unsigned int iClientID, enum EFLConnection state) {
    Main::returncode = DEFAULT_RETURNCODE;
    Disqualify(iClientID);
}

void __stdcall BaseEnter(unsigned int iBaseID, unsigned int iClientID) {
    Disqualify(iClientID);
}

void __stdcall PlayerLaunch(unsigned int iShip, unsigned int iClientID) {
    Main::returncode = DEFAULT_RETURNCODE;
    Disqualify(iClientID);
}
}

//Death msg hook


// 22045 Destroy All the Hostile Fighters
// 24070 Destroy the Enemy Ships