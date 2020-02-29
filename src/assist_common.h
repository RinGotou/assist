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
  using ObjectTypeFetcher = int(*)(void *, const char *);
  using ReturningTunnel = void(*)(void *, void *, int);
  using ErrorInformer = void(*)(void*, const char*);
  using GenericFunctionPointer = void(*)();
  using GenericPointer = uintptr_t;
 
  const string kTypeIdNull = "null";
  const string kTypeIdInt = "int";
  const string kTypeIdFloat = "float";
  const string kTypeIdBool = "bool";
  const string kTypeIdString = "string";
  const string kTypeIdWideString = "wstring";
  const string kTypeIdInStream = "instream";
  const string kTypeIdOutStream = "outstream";
  const string kTypeIdFunctionPointer = "function_pointer";
  const string kTypeIdObjectPointer = "object_pointer";

  enum ObjectType {
    kExtUnsupported = -1,
    kExtTypeNull = 0,
    kExtTypeInt = 1,
    kExtTypeFloat = 2,
    kExtTypeBool = 3,
    kExtTypeString = 4,
    kExtTypeWideString = 5,
    kExtTypeFunctionPointer = 6,
    kExtTypeObjectPointer = 7,
    kExtTypeArray = 8,
    kExtCustomTypes = 100
  };

  extern "C" struct VMState {
    void *obj_map, *ret_slot, *vm;
    ReturningTunnel tunnel;
  };

  extern "C" struct Descriptor {
    void *ptr;
    ObjectType type;
  };

  using ArrayElementFetcher = int(*)(Descriptor *, Descriptor *, size_t);
  using ObjectDumper = int(*)(Descriptor *, void **);
  using DescriptorFetcher = int(*)(Descriptor *, void *, const char *);
  using CapacityInformer = size_t(*)(Descriptor);

  extern "C" struct ExtInterfaces {
    MemoryDisposer disposer;
    ObjectTypeFetcher type_fetcher;
    ErrorInformer error_informer;
    DescriptorFetcher desc_fetcher;
    ArrayElementFetcher arr_elem_fetcher;
    ObjectDumper dumper;
    CapacityInformer capacity_informer;
  };

  using IntValue = optional<int64_t>;
  using FloatValue = optional<double>;
  using BoolValue = optional<bool>;
  using StringValue = optional<string>;
  using WideStringValue = optional<wstring>;
  using FunctionPointerValue = optional<GenericFunctionPointer>;
  using ObjectPointerValue = optional<GenericPointer>;
  using DescriptorValue = optional<Descriptor>;

  template <typename... _Type>
  bool HasValue(_Type... opt) { return (opt.has_value() && ...); }

  template <typename _Lhs, typename... _Rhs>
  inline bool Compare(_Lhs lhs, _Rhs... rhs) {
    return ((lhs == rhs) || ...);
  }
}
