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
  void ReturnIntObject(int64_t value, ReturningTunnel tunnel);
  void ReturnFloatObject(double value, ReturningTunnel tunnel);
  void ReturnBoolObject(bool value, ReturningTunnel tunnel);
  void ReturnStringObject(string value, ReturningTunnel tunnel);
  void ReturnWideStringObject(wstring value, ReturningTunnel tunnel);
}
