#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <unordered_map>
#include <string>
#include "assist.h"

#ifdef _WIN32
#define EXPORTED __declspec(dllexport)
#else 
#define EXPORTED
#endif

using std::unordered_map;
using std::string;
using std::pair;

using FunctionParameters = pair<string, const char *>;

extern "C" {
  EXPORTED int kagami_LoadExtension(kagami::ExtInterfaces *interfaces);
  EXPORTED const char *kagami_ParameterInformer(const char *id);

  EXPORTED int sample_helloworld(kagami::VMState state);
  EXPORTED int sample_plus(kagami::VMState state);
  EXPORTED int sample_throw_error(kagami::VMState state);
}
