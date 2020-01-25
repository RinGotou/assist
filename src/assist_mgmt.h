#pragma once
#include "assist_common.h"

namespace kagami {
  vector<string> BuildStringVector(string source);
  string CombineStringVector(vector<string> target);

  bool InformCallbackFacilities(CallbackFacilityLauncher launcher, ObjectTypeFetcher fetcher);
  bool InformMemoryMgmtInterface(MemoryDisposer disposer_ptr, MemoryDisposer group_disposer_ptr);
  bool InformErrorThrowingInterface(ErrorInformer informer);

  IntValue FromIntObject(string id, void *obj_map);
  FloatValue FromFloatObject(string id, void *obj_map);
  BoolValue FromBoolObject(string id, void *obj_map);
  StringValue FromStringObject(string id, void *obj_map);
  WideStringValue FromWideStringObject(string id, void *obj_map);
  FunctionPointerValue FromFunctionPointerObject(string id, void *obj_map);
  ObjectPointerValue FromObjPointerObject(string id, void *obj_map);

  void ReturnIntObject(int64_t value, VMState state);
  void ReturnFloatObject(double value, VMState state);
  void ReturnBoolObject(bool value, VMState state);
  void ReturnStringObject(string value, VMState state);
  void ReturnWideStringObject(wstring value, VMState state);
  void ReturnFunctionPointerObject(GenericFunctionPointer value, VMState state);
  void ReturnObjPointerObject(GenericPointer value, VMState state);

  void ThrowError(string msg, VMState state);
  ExtActivityReturnType GetObjectType(void *obj_map, string id);
}

#define KAGAMI_STANDARD_EXTENSION                                              \
EXPORTED int kagami_LoadExtension(kagami::ExtInterfaces *interfaces) {                  \
  bool facilities_result = kagami::InformCallbackFacilities(                   \
    interfaces->launcher, interfaces->type_fetcher);                           \
  bool mem_mgmt_result = kagami::InformMemoryMgmtInterface(                    \
    interfaces->disposer, interfaces->group_disposer);                         \
  bool error_throwing_result = kagami::InformErrorThrowingInterface(           \
    interfaces->error_informer);                                               \
  int result = facilities_result && mem_mgmt_result && error_throwing_result ? \
    1 : 0;                                                                     \
  return result;                                                               \
}
