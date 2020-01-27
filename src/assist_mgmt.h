#pragma once
#include "assist_types.h"

namespace kagami {
  MemoryDisposer GetMemoryDisposer();
  ObjectDumper GetObjectDumper();
  DescriptorFetcher GetDescriptorFetcher();

  vector<string> BuildStringVector(string source);
  string CombineStringVector(vector<string> target);

  bool InformCallbackFacilities(ExtInterfaces &interfaces);
  bool InformMemoryMgmtInterface(MemoryDisposer disposer_ptr);
  bool InformErrorThrowingInterface(ErrorInformer informer);
  bool InformDescriptorInterface(DescriptorFetcher fetcher);

  template <typename _Type>
  optional<_Type> 
    FromDescriptor(Descriptor desc) {
    ObjectDumper dumper = GetObjectDumper();
    MemoryDisposer disposer = GetMemoryDisposer();
    void *dest = nullptr;
    _Type value;

    int dump_result = dumper(&desc, &dest);
    if (dump_result != 1) return nullopt;

    if constexpr (_IsStringObject(_RevObjectTypeTrait<_Type>::type)) {
      typename _CharTypeTrait<_Type>::Type *ptr = dest;
      value = _Type(dest);
      disposer(dest, _RevObjectTypeTrait<_Type>::type);
    }
    else {
      _Type value = *(_Type *)dest;
      disposer(dest);
    }
    
    return value;
  }

  template <ObjectType _TypeCode>
  optional<typename _ObjectTypeTrait<_TypeCode>::Type>
    FromObject(string id, void *obj_map) {
    Descriptor desc;
    DescriptorFetcher fetcher = GetDescriptorFetcher();
    ObjectDumper dumper = GetObjectDumper();
    MemoryDisposer disposer = GetMemoryDisposer();
    typename _ObjectTypeTrait<_TypeCode>::Type value;

    int fetch_result = fetcher(&desc, obj_map, id.data());
    if (fetch_result != 1) return nullopt;
    if (desc.type != _TypeCode) return nullopt;

    if constexpr (_IsStringObject(_TypeCode)) {
      typename _CharTypeTrait<typename _ObjectTypeTrait<_TypeCode>::Type>::Type
        *buffer = nullptr;
      int dump_result = dumper(desc, (void **)&buffer);
      if (dump_result != 1) return nullopt;
      value = typename _ObjectTypeTrait<_TypeCode>::Type(buffer);
      disposer(buffer, _TypeCode);
    }
    else {
      typename _ObjectTypeTrait<_TypeCode>::Type *buffer = nullptr;
      int dump_result = dumper(&desc, (void **)&buffer);
      if (dump_result != 1) return nullopt;
      value = *buffer;
      disposer(buffer, _TypeCode);
    }

    return value;
  }

  DescriptorValue GetDesciptor(string id, void *obj_map);
  DescriptorValue GetArrayElementDescriptor(Descriptor arr_desc, size_t index);

  void ReturnIntObject(int64_t value, VMState state);
  void ReturnFloatObject(double value, VMState state);
  void ReturnBoolObject(bool value, VMState state);
  void ReturnStringObject(string value, VMState state);
  void ReturnWideStringObject(wstring value, VMState state);
  void ReturnFunctionPointerObject(GenericFunctionPointer value, VMState state);
  void ReturnObjPointerObject(GenericPointer value, VMState state);

  void ThrowError(string msg, VMState state);
  ObjectType GetObjectType(void *obj_map, string id);
}

#define KAGAMI_STANDARD_EXTENSION                                                                   \
EXPORTED int kagami_LoadExtension(kagami::ExtInterfaces *interfaces) {                              \
  bool facilities_result = kagami::InformCallbackFacilities(*interfaces);                           \
  bool mem_mgmt_result = kagami::InformMemoryMgmtInterface(interfaces->disposer);                   \
  bool error_throwing_result = kagami::InformErrorThrowingInterface(                                \
    interfaces->error_informer);                                                                    \
  bool descriptor_result = kagami::InformDescriptorInterface(interfaces->desc_fetcher);             \
  int result = facilities_result && mem_mgmt_result && error_throwing_result && descriptor_result ? \
    1 : 0;                                                                                          \
  return result;                                                                                    \
}
