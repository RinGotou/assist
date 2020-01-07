#include "assist_mgmt.h"

namespace kagami {
  static ObjectValueFetcher
    int_fetcher     = nullptr,
    float_fetcher   = nullptr,
    bool_fetcher    = nullptr,
    string_fetcher  = nullptr,
    wstring_fetcher = nullptr;
  static MemoryDisposer
    disposer        = nullptr,
    group_disposer  = nullptr;

  bool InformCallbackFacilities(CallbackFacilityLauncher launcher) {
    int_fetcher = launcher("int");
    float_fetcher = launcher("float");
    bool_fetcher = launcher("bool");
    string_fetcher = launcher("string");
    wstring_fetcher = launcher("wstring");
    return (int_fetcher != nullptr)
      && (float_fetcher != nullptr)
      && (bool_fetcher != nullptr)
      && (string_fetcher != nullptr)
      && (wstring_fetcher != nullptr);
  }

  bool InformMemoryMgmtInterface(MemoryDisposer disposer_ptr, MemoryDisposer group_disposer_ptr) {
    disposer = disposer_ptr;
    group_disposer = group_disposer_ptr;
    return (disposer != nullptr) && (group_disposer_ptr != nullptr);
  }

  IntValue FromIntObject(string id, void *obj_map) {
    int64_t *buffer = nullptr;
    int result = int_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    int64_t value = *buffer;
    disposer(buffer);
    return value;
  }

  FloatValue FromFloatObject(string id, void *obj_map) {
    double *buffer = nullptr;
    int result = float_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    double value = *buffer;
    disposer(buffer);
    return value;
  }

  BoolValue FromBoolObject(string id, void *obj_map) {
    int *buffer = nullptr;
    int result = bool_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    bool value = (*buffer == 1);
    disposer(buffer);
    return value;
  }

  StringValue FromStringObject(string id, void *obj_map) {
    char *buffer = nullptr;
    int result = string_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    string value(buffer);
    group_disposer(buffer);
    return value;
  }

  WideStringValue FromWideStringObject(string id, void *obj_map) {
    wchar_t *buffer = nullptr;
    int result = wstring_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    wstring value(buffer);
    group_disposer(buffer);
    return value;
  }

  void ReturnIntObject(int64_t value, VMState state) {
    state.tunnel(&value, state.ret_slot, kExtTypeInt);
  }

  void ReturnFloatObject(double value, VMState state) {
    state.tunnel(&value, state.ret_slot, kExtTypeFloat);
  }

  void ReturnBoolObject(bool value, VMState state) {
    int buffer = value ? 1 : 0;
    state.tunnel(&buffer, state.ret_slot, kExtTypeBool);
  }

  void ReturnStringObject(string value, VMState state) {
    char *buffer = new char[value.size() + 1];
    std::strcpy(buffer, value.data());
    state.tunnel(buffer, state.ret_slot, kExtTypeString);
    delete[] buffer;
  }

  void ReturnWideStringObject(wstring value, VMState state) {
    wchar_t *buffer = new wchar_t[value.size() + 1];
    std::wcscpy(buffer, value.data());
    state.tunnel(buffer, state.ret_slot, kExtTypeWideString);
    delete[] buffer;
  }
}