#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <unordered_map>
#include <string>
#include "assist.h"

using std::unordered_map;
using std::string;
using std::pair;

using FunctionParameters = pair<string, const char *>;

extern __declspec(dllexport) int kagami_LoadExtension(kagami::CallbackFacilityLauncher launcher, 
  kagami::MemoryDisposer disposer, kagami::MemoryDisposer group_disposer);
extern __declspec(dllexport) const char *kagami_ParameterInformer(const char *id);

extern __declspec(dllexport) int sample_helloworld(void *obj_map, kagami::ReturningTunnel tunnel);
extern __declspec(dllexport) int sample_plus(void *obj_map, kagami::ReturningTunnel tunnel);