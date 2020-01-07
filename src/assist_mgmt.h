#pragma once
#include "assist_common.h"

namespace kagami {
  bool InformCallbackFacilities(CallbackFacilityLauncher launcher);
  bool InformMemoryMgmtInterface(MemoryDisposer disposer_ptr, MemoryDisposer group_disposer_ptr);

  IntValue FromIntObject(string id, void *obj_map);
  FloatValue FromFloatObject(string id, void *obj_map);
  BoolValue FromBoolObject(string id, void *obj_map);
  StringValue FromStringObject(string id, void *obj_map);
  WideStringValue FromWideStringObject(string id, void *obj_map);
  void ReturnIntObject(int64_t value, VMState state);
  void ReturnFloatObject(double value, VMState state);
  void ReturnBoolObject(bool value, VMState state);
  void ReturnStringObject(string value, VMState state);
  void ReturnWideStringObject(wstring value, VMState state);
}
