#pragma once
#ifdef _MSC_VER
#pragma warning(disable:26812)
#pragma warning(disable:4996)
#endif
#include <unordered_map>
#include <vector>
#include <optional>
#include <cstdlib>
#include <cstring>
#include <string>
#define ASSIST_VERSION 1

namespace kagami {
  using std::unordered_map;
  using std::pair;
  using std::vector;
  using std::optional;
  using std::nullopt;
  using std::string;
  using std::wstring;

  using MemoryDisposer = void(*)(void *, int);
  using ParameterInformer = const char *(*)(const char *);
  using ObjectValueFetcher = int(*)(void **, void *, const char *);
  using CallbackFacilityLauncher = ObjectValueFetcher(*)(const char *);
  using ObjectTypeFetcher = int(*)(void *, const char *);
  using ReturningTunnel = void(*)(void *, void *, int);
  using ErrorInformer = void(*)(void*, const char*);

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
    kExtTypeNull       = 0,
    kExtTypeInt        = 1,
    kExtTypeFloat      = 2,
    kExtTypeBool       = 3,
    kExtTypeString     = 4,
    kExtTypeWideString = 5,
    kExtCustomTypes    = 100
  };

  extern "C" struct VMState {
    void *obj_map, *ret_slot, *vm;
    ReturningTunnel tunnel;
  };
  
  extern "C" struct ExtInterfaces {
    CallbackFacilityLauncher launcher;
    MemoryDisposer disposer;
    MemoryDisposer group_disposer;
    ObjectTypeFetcher type_fetcher;
    ErrorInformer error_informer;
  };
}
