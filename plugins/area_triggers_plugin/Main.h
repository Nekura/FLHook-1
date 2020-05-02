#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <math.h>
#include <list>
#include <map>
#include <algorithm>
#include <FLHook.h>
#include <plugin.h>
#include "PluginUtilities.h"

PLUGIN_RETURNCODE returncode;

void AddExceptionInfoLog(struct SEHException* pep);
#define LOG_EXCEPTION { AddLog("ERROR Exception in %s", __FUNCTION__); AddExceptionInfoLog(0); }