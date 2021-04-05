// Includes
#include "Main.h"

namespace Utilities {

std::vector<const char *> listgraphs;
std::vector<uint> npcnames;

// Function to return a Personality. Possible improvements in the future to get
// this to load from a config file
pub::AI::SetPersonalityParams HkMakePersonality(int graphid) {

    pub::AI::SetPersonalityParams p;
    p.iStateGraph = pub::StateGraph::get_state_graph(
        listgraphs[graphid], pub::StateGraph::TYPE_STANDARD);
    p.bStateID = true;

    p.personality.EvadeDodgeUse.evade_dodge_style_weight[0] = 0.4f;
    p.personality.EvadeDodgeUse.evade_dodge_style_weight[1] = 0.0f;
    p.personality.EvadeDodgeUse.evade_dodge_style_weight[2] = 0.4f;
    p.personality.EvadeDodgeUse.evade_dodge_style_weight[3] = 0.2f;
    p.personality.EvadeDodgeUse.evade_dodge_cone_angle = 1.5708f;
    p.personality.EvadeDodgeUse.evade_dodge_interval_time = 10.0f;
    p.personality.EvadeDodgeUse.evade_dodge_time = 1.0f;
    p.personality.EvadeDodgeUse.evade_dodge_distance = 75.0f;
    p.personality.EvadeDodgeUse.evade_activate_range = 100.0f;
    p.personality.EvadeDodgeUse.evade_dodge_roll_angle = 1.5708f;
    p.personality.EvadeDodgeUse.evade_dodge_waggle_axis_cone_angle = 1.5708f;
    p.personality.EvadeDodgeUse.evade_dodge_slide_throttle = 1.0f;
    p.personality.EvadeDodgeUse.evade_dodge_turn_throttle = 1.0f;
    p.personality.EvadeDodgeUse.evade_dodge_corkscrew_roll_flip_direction =
        true;
    p.personality.EvadeDodgeUse.evade_dodge_interval_time_variance_percent =
        0.5f;
    p.personality.EvadeDodgeUse.evade_dodge_cone_angle_variance_percent = 0.5f;
    p.personality.EvadeDodgeUse.evade_dodge_direction_weight[0] = 0.25f;
    p.personality.EvadeDodgeUse.evade_dodge_direction_weight[1] = 0.25f;
    p.personality.EvadeDodgeUse.evade_dodge_direction_weight[2] = 0.25f;
    p.personality.EvadeDodgeUse.evade_dodge_direction_weight[3] = 0.25f;

    p.personality.EvadeBreakUse.evade_break_roll_throttle = 1.0f;
    p.personality.EvadeBreakUse.evade_break_time = 1.0f;
    p.personality.EvadeBreakUse.evade_break_interval_time = 10.0f;
    p.personality.EvadeBreakUse.evade_break_afterburner_delay = 0.0f;
    p.personality.EvadeBreakUse.evade_break_turn_throttle = 1.0f;
    p.personality.EvadeBreakUse.evade_break_direction_weight[0] = 1.0f;
    p.personality.EvadeBreakUse.evade_break_direction_weight[1] = 1.0f;
    p.personality.EvadeBreakUse.evade_break_direction_weight[2] = 1.0f;
    p.personality.EvadeBreakUse.evade_break_direction_weight[3] = 1.0f;
    p.personality.EvadeBreakUse.evade_break_style_weight[0] = 1.0f;
    p.personality.EvadeBreakUse.evade_break_style_weight[1] = 1.0f;
    p.personality.EvadeBreakUse.evade_break_style_weight[2] = 1.0f;

    p.personality.BuzzHeadTowardUse.buzz_min_distance_to_head_toward = 500.0f;
    p.personality.BuzzHeadTowardUse
        .buzz_min_distance_to_head_toward_variance_percent = 0.25f;
    p.personality.BuzzHeadTowardUse.buzz_max_time_to_head_away = 1.0f;
    p.personality.BuzzHeadTowardUse.buzz_head_toward_engine_throttle = 1.0f;
    p.personality.BuzzHeadTowardUse.buzz_head_toward_turn_throttle = 1.0f;
    p.personality.BuzzHeadTowardUse.buzz_head_toward_roll_throttle = 1.0f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_turn_throttle = 1.0f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_cone_angle = 1.5708f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_cone_angle_variance_percent =
        0.5f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_waggle_axis_cone_angle = 0.3491f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_roll_angle = 1.5708f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_interval_time = 10.0f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_interval_time_variance_percent =
        0.5f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_direction_weight[0] = 0.25f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_direction_weight[1] = 0.25f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_direction_weight[2] = 0.25f;
    p.personality.BuzzHeadTowardUse.buzz_dodge_direction_weight[3] = 0.25f;
    p.personality.BuzzHeadTowardUse.buzz_head_toward_style_weight[0] = 0.33f;
    p.personality.BuzzHeadTowardUse.buzz_head_toward_style_weight[1] = 0.33f;
    p.personality.BuzzHeadTowardUse.buzz_head_toward_style_weight[2] = 0.33f;

    p.personality.BuzzPassByUse.buzz_distance_to_pass_by = 1000.0f;
    p.personality.BuzzPassByUse.buzz_pass_by_time = 1.0f;
    p.personality.BuzzPassByUse.buzz_break_direction_cone_angle = 1.5708f;
    p.personality.BuzzPassByUse.buzz_break_turn_throttle = 1.0f;
    p.personality.BuzzPassByUse.buzz_drop_bomb_on_pass_by = true;
    p.personality.BuzzPassByUse.buzz_break_direction_weight[0] = 1.0f;
    p.personality.BuzzPassByUse.buzz_break_direction_weight[1] = 1.0f;
    p.personality.BuzzPassByUse.buzz_break_direction_weight[2] = 1.0f;
    p.personality.BuzzPassByUse.buzz_break_direction_weight[3] = 1.0f;
    p.personality.BuzzPassByUse.buzz_pass_by_style_weight[2] = 1.0f;

    p.personality.TrailUse.trail_lock_cone_angle = 0.0873f;
    p.personality.TrailUse.trail_break_time = 0.5f;
    p.personality.TrailUse.trail_min_no_lock_time = 0.1f;
    p.personality.TrailUse.trail_break_roll_throttle = 1.0f;
    p.personality.TrailUse.trail_break_afterburner = true;
    p.personality.TrailUse.trail_max_turn_throttle = 1.0f;
    p.personality.TrailUse.trail_distance = 100.0f;

    p.personality.StrafeUse.strafe_run_away_distance = 100.0f;
    p.personality.StrafeUse.strafe_attack_throttle = 1.0f;

    p.personality.EngineKillUse.engine_kill_search_time = 0.0f;
    p.personality.EngineKillUse.engine_kill_face_time = 1.0f;
    p.personality.EngineKillUse.engine_kill_use_afterburner = true;
    p.personality.EngineKillUse.engine_kill_afterburner_time = 2.0f;
    p.personality.EngineKillUse.engine_kill_max_target_distance = 100.0f;

    p.personality.RepairUse.use_shield_repair_pre_delay = 0.0f;
    p.personality.RepairUse.use_shield_repair_post_delay = 1.0f;
    p.personality.RepairUse.use_shield_repair_at_damage_percent = 0.2f;
    p.personality.RepairUse.use_hull_repair_pre_delay = 0.0f;
    p.personality.RepairUse.use_hull_repair_post_delay = 1.0f;
    p.personality.RepairUse.use_hull_repair_at_damage_percent = 0.2f;

    p.personality.GunUse.gun_fire_interval_time = 0.1f;
    p.personality.GunUse.gun_fire_interval_variance_percent = 0.05f;
    p.personality.GunUse.gun_fire_burst_interval_time = 15.0f;
    p.personality.GunUse.gun_fire_burst_interval_variance_percent = 0.05f;
    p.personality.GunUse.gun_fire_no_burst_interval_time = 1.0f;
    p.personality.GunUse.gun_fire_accuracy_cone_angle = 0.00001f;
    p.personality.GunUse.gun_fire_accuracy_power = 100.0f;
    p.personality.GunUse.gun_range_threshold = 1.0f;
    p.personality.GunUse.gun_target_point_switch_time = 0.0f;
    p.personality.GunUse.fire_style = 0;
    p.personality.GunUse.auto_turret_interval_time = 0.1f;
    p.personality.GunUse.auto_turret_burst_interval_time = 15.0f;
    p.personality.GunUse.auto_turret_no_burst_interval_time = 0.1f;
    p.personality.GunUse.auto_turret_burst_interval_variance_percent = 0.1f;
    p.personality.GunUse.gun_range_threshold_variance_percent = 1.0f;
    p.personality.GunUse.gun_fire_accuracy_power_npc = 100.0f;

    p.personality.MineUse.mine_launch_interval = 0.5f;
    p.personality.MineUse.mine_launch_cone_angle = 0.7854f;
    p.personality.MineUse.mine_launch_range = 200.0f;

    p.personality.MissileUse.missile_launch_interval_time = 0.0f;
    p.personality.MissileUse.missile_launch_interval_variance_percent = 0.5f;
    p.personality.MissileUse.missile_launch_range = 800.0f;
    p.personality.MissileUse.missile_launch_cone_angle = 0.01745f;
    p.personality.MissileUse.missile_launch_allow_out_of_range = false;

    p.personality.DamageReaction.evade_break_damage_trigger_percent = 1.0f;
    p.personality.DamageReaction.evade_dodge_more_damage_trigger_percent =
        0.25f;
    p.personality.DamageReaction.engine_kill_face_damage_trigger_percent = 1.0f;
    p.personality.DamageReaction.engine_kill_face_damage_trigger_time = 0.2f;
    p.personality.DamageReaction.roll_damage_trigger_percent = 0.4f;
    p.personality.DamageReaction.roll_damage_trigger_time = 0.2f;
    p.personality.DamageReaction.afterburner_damage_trigger_percent = 0.2f;
    p.personality.DamageReaction.afterburner_damage_trigger_time = 0.5f;
    p.personality.DamageReaction.brake_reverse_damage_trigger_percent = 1.0f;
    p.personality.DamageReaction.drop_mines_damage_trigger_percent = 0.25f;
    p.personality.DamageReaction.drop_mines_damage_trigger_time = 0.1f;
    p.personality.DamageReaction.fire_guns_damage_trigger_percent = 1.0f;
    p.personality.DamageReaction.fire_guns_damage_trigger_time = 1.0f;
    p.personality.DamageReaction.fire_missiles_damage_trigger_percent = 1.0f;
    p.personality.DamageReaction.fire_missiles_damage_trigger_time = 1.0f;

    p.personality.MissileReaction.evade_missile_distance = 800.0f;
    p.personality.MissileReaction.evade_break_missile_reaction_time = 1.0f;
    p.personality.MissileReaction.evade_slide_missile_reaction_time = 1.0f;
    p.personality.MissileReaction.evade_afterburn_missile_reaction_time = 1.0f;

    p.personality.CountermeasureUse.countermeasure_active_time = 5.0f;
    p.personality.CountermeasureUse.countermeasure_unactive_time = 0.0f;

    p.personality.FormationUse.force_attack_formation_active_time = 0.0f;
    p.personality.FormationUse.force_attack_formation_unactive_time = 0.0f;
    p.personality.FormationUse.break_formation_damage_trigger_percent = 0.01f;
    p.personality.FormationUse.break_formation_damage_trigger_time = 1.0f;
    p.personality.FormationUse.break_formation_missile_reaction_time = 1.0f;
    p.personality.FormationUse.break_apart_formation_missile_reaction_time =
        1.0f;
    p.personality.FormationUse.break_apart_formation_on_evade_break = true;
    p.personality.FormationUse.break_formation_on_evade_break_time = 1.0f;
    p.personality.FormationUse.formation_exit_top_turn_break_away_throttle =
        1.0f;
    p.personality.FormationUse.formation_exit_roll_outrun_throttle = 1.0f;
    p.personality.FormationUse.formation_exit_max_time = 5.0f;
    p.personality.FormationUse.formation_exit_mode = 1;

    p.personality.Job.wait_for_leader_target = false;
    p.personality.Job.maximum_leader_target_distance = 3000;
    p.personality.Job.flee_when_leader_flees_style = false;
    p.personality.Job.scene_toughness_threshold = 4;
    p.personality.Job.flee_scene_threat_style = 4;
    p.personality.Job.flee_when_hull_damaged_percent = 0.01f;
    p.personality.Job.flee_no_weapons_style = true;
    p.personality.Job.loot_flee_threshold = 4;
    p.personality.Job.attack_subtarget_order[0] = 5;
    p.personality.Job.attack_subtarget_order[1] = 6;
    p.personality.Job.attack_subtarget_order[2] = 7;
    p.personality.Job.field_targeting = 3;
    p.personality.Job.loot_preference = 7;
    p.personality.Job.combat_drift_distance = 25000;
    p.personality.Job.attack_order[0].distance = 5000;
    p.personality.Job.attack_order[0].type = 11;
    p.personality.Job.attack_order[0].flag = 15;
    p.personality.Job.attack_order[1].type = 12;

    return p;
}

// Return random infocard ID from list that was loaded in
uint rand_name() {
    int randomIndex = rand() % npcnames.size();
    return npcnames.at(randomIndex);
}

// Function called by next function to remove spawned NPCs from our data
bool IsFLHookNPC(CShip *ship) {
    // If it's a player do nothing
    if (ship->is_player() == true) {
        return false;
    }

    // Is it a FLHook NPC?
    std::list<uint>::iterator iter = Main::NPCs.begin();
    while (iter != Main::NPCs.end()) {
        if (*iter == ship->get_id()) {
            ship->clear_equip_and_cargo();
            Main::NPCs.erase(iter);
            Survival::NPCDestroyed(ship);
            return true;
            break;
        }
        iter++;
    }
    return false;
}

// Function to log output (usually NPCs that have been created)
void Logging(const char *szString, ...) {
    FILE *Logfile;
    fopen_s(&Logfile, "./flhook_logs/npc_log.log", "at");
    char szBufString[1024];
    va_list marker;
    va_start(marker, szString);
    _vsnprintf_s(szBufString, sizeof(szBufString) - 1, szString, marker);
    char szBuf[64];
    time_t tNow = time(0);
    tm t;
    localtime_s(&t, &tNow);
    strftime(szBuf, sizeof(szBuf), "%d/%m/%Y %H:%M:%S", &t);
    fprintf(Logfile, "%s %s\n", szBuf, szBufString);
    fflush(Logfile);
    fclose(Logfile);
}

// Logs the NPC being created
void Log_CreateNPC(std::wstring name) {
    // internal log
    std::wstring wscMsgLog = L"created <%name>";
    wscMsgLog = ReplaceStr(wscMsgLog, L"%name", name.c_str());
    std::string scText = wstos(wscMsgLog);
    Logging("%s", scText.c_str());
}

// Returns a random float between two
float rand_FloatRange(float a, float b) {
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

// Function that actually spawns the NPC
uint CreateNPC(std::wstring name, Vector pos, Matrix rot, uint iSystem,
               bool varyPos) {
    Main::NPC_ARCHTYPESSTRUCT arch = Main::mapNPCArchtypes[name];

    pub::SpaceObj::ShipInfo si;
    memset(&si, 0, sizeof(si));
    si.iFlag = 1;
    si.iSystem = iSystem;
    si.iShipArchetype = arch.Shiparch;
    si.mOrientation = rot;
    si.iLoadout = arch.Loadout;
    si.iLook1 = CreateID("li_newscaster_head_gen_hat");
    si.iLook2 = CreateID("pl_female1_journeyman_body");
    si.iComm = CreateID("comm_br_darcy_female");
    si.iPilotVoice = CreateID("pilot_f_leg_f01a");
    si.iHealth = -1;
    si.iLevel = 19;

    if (varyPos) {
        si.vPos.x = pos.x + rand_FloatRange(0, 1000);
        si.vPos.y = pos.y + rand_FloatRange(0, 1000);
        si.vPos.z = pos.z + rand_FloatRange(0, 2000);
    } else {
        si.vPos.x = pos.x;
        si.vPos.y = pos.y;
        si.vPos.z = pos.z;
    }

    // Define the string used for the scanner name. Because the
    // following entry is empty, the pilot_name is used. This
    // can be overriden to display the ship type instead.
    FmtStr scanner_name(0, 0);
    scanner_name.begin_mad_lib(0);
    scanner_name.end_mad_lib();

    // Define the string used for the pilot name. The example
    // below shows the use of multiple part names.
    FmtStr pilot_name(0, 0);
    pilot_name.begin_mad_lib(16163); // ids of "%s0 %s1"
    if (arch.Infocard != 0) {
        pilot_name.append_string(arch.Infocard);
        if (arch.Infocard2 != 0) {
            pilot_name.append_string(arch.Infocard2);
        }
    } else {
        pilot_name.append_string(rand_name()); // ids that replaces %s0
        pilot_name.append_string(rand_name()); // ids that replaces %s1
    }
    pilot_name.end_mad_lib();

    pub::Reputation::Alloc(si.iRep, scanner_name, pilot_name);
    pub::Reputation::SetAffiliation(si.iRep, arch.IFF);

    int rep;
    pub::Player::GetRep(1, rep);
    pub::Reputation::SetAttitude(si.iRep, rep, -0.9f);

    uint iSpaceObj;

    pub::SpaceObj::Create(iSpaceObj, si);

    pub::AI::SetPersonalityParams pers = HkMakePersonality(arch.Graph);
    pub::AI::SubmitState(iSpaceObj, &pers);

    Main::NPCs.push_back(iSpaceObj);

    return iSpaceObj;
}

void SendUniverseChatRedText(std::wstring wscXMLText) {
    // Encode message using the death message style (red text).
    std::wstring wscXMLMsg =
        L"<TRA data=\"" + set_wscDeathMsgStyleSys + L"\" mask=\"-1\"/> <TEXT>";
    wscXMLMsg += wscXMLText;
    wscXMLMsg += L"</TEXT>";

    char szBuf[0x1000];
    uint iRet;
    if (!HKHKSUCCESS(HkFMsgEncodeXML(wscXMLMsg, szBuf, sizeof(szBuf), iRet)))
        return;

    // Send to all players in system
    struct PlayerData *pPD = 0;
    while (pPD = Players.traverse_active(pPD)) {
        uint iClientID = HkGetClientIdFromPD(pPD);
        HkFMsgSendChat(iClientID, szBuf, iRet);
    }
}
} // namespace Utilities