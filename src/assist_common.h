#pragma once
#include <unordered_map>
#include "filestream.h"
#define ASSIST_VERSION 1

namespace kagami {
  using std::unordered_map;
  using std::pair;
  using MemoryDisposer = void(*)(void *);
  using ParameterInformer = const char *(*)(const char *);
  using ObjectValueFetcher = int(*)(void **, void *, const char *);
  using CallbackFacilityLauncher = ObjectValueFetcher(*)(const char *);
  using ExtensionLoader = int(*)(CallbackFacilityLauncher, MemoryDisposer, MemoryDisposer);

  const string kTypeIdNull = "null";
  const string kTypeIdInt = "int";
  const string kTypeIdFloat = "float";
  const string kTypeIdBool = "bool";
  const string kTypeIdString = "string";
  const string kTypeIdWideString = "wstring";
  const string kTypeIdInStream = "instream";
  const string kTypeIdOutStream = "outstream";
}
