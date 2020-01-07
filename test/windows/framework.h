#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include "assist.h"

extern __declspec(dllexport) int kagami_LoadExtension(kagami::CallbackFacilityLauncher launcher, 
  kagami::MemoryDisposer disposer, kagami::MemoryDisposer group_disposer);
extern __declspec(dllexport) const char *kagami_ParameterInformer(const char *id);