#pragma once
#include <unordered_map>
#include <vector>
#include <optional>
#include <cstdlib>
#include "filestream.h"
#define ASSIST_VERSION 1

namespace kagami {
  using std::unordered_map;
  using std::pair;
  using std::vector;
  using std::optional;
  using std::nullopt;

  using MemoryDisposer = void(*)(void *);
  using ParameterInformer = const char *(*)(const char *);
  using ObjectValueFetcher = int(*)(void **, void *, const char *);
  using CallbackFacilityLauncher = ObjectValueFetcher(*)(const char *);
  using ExtensionLoader = int(*)(CallbackFacilityLauncher, MemoryDisposer, MemoryDisposer);
  using ReturningTunnel = void(*)(void *, void *, int);

  using IntValue = optional<int64_t>;
  using FloatValue = optional<double>;
  using BoolValue = optional<bool>;
  using StringValue = optional<string>;
  using WideStringValue = optional<wstring>;

  const string kTypeIdNull = "null";
  const string kTypeIdInt = "int";
  const string kTypeIdFloat = "float";
  const string kTypeIdBool = "bool";
  const string kTypeIdString = "string";
  const string kTypeIdWideString = "wstring";
  const string kTypeIdInStream = "instream";
  const string kTypeIdOutStream = "outstream";

  enum ExtActivityReturnType {
    kExtTypeInt        = 1,
    kExtTypeFloat      = 2,
    kExtTypeBool       = 3,
    kExtTypeString     = 4,
    kExtTypeWideString = 5
  };

  extern "C" struct VMState {
    void *obj_map, *ret_slot;
    ReturningTunnel tunnel;
  };
}
