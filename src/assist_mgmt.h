#pragma once
#include "assist_types.h"

namespace kagami {
  MemoryDisposer GetMemoryDisposer();
  ObjectDumper GetObjectDumper();
  DescriptorFetcher GetDescriptorFetcher();

  vector<string> BuildStringVector(string source);
  string CombineStringVector(vector<string> target);

  bool InformCallbackFacilities(ExtInterfaces &interfaces);

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
      value = *(_Type *)dest;
      disposer(dest, _RevObjectTypeTrait<_Type>::type);
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
  size_t GetArrayObjectCapacity(Descriptor desc);
  DescriptorValue GetArrayElementDescriptor(Descriptor arr_desc, size_t index);
  vector<Descriptor> GetArrayElements(Descriptor desc);

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

