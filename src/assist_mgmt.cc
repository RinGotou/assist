#include "assist_mgmt.h"

namespace kagami {
  static ObjectValueFetcher
    int_fetcher      = nullptr,
    float_fetcher    = nullptr,
    bool_fetcher     = nullptr,
    string_fetcher   = nullptr,
    wstring_fetcher  = nullptr,
    func_ptr_fetcher = nullptr,
    obj_ptr_fetcher  = nullptr;
  static MemoryDisposer
    disposer        = nullptr,
    group_disposer  = nullptr;
  static ObjectTypeFetcher
    type_fetcher    = nullptr;
  static ErrorInformer 
    error_informer  = nullptr;

  vector<string> BuildStringVector(string source) {
    vector<string> result;
    string temp;
    for (auto unit : source) {
      if (unit == '|') {
        result.push_back(temp);
        temp.clear();
        continue;
      }
      temp.append(1, unit);
    }
    if (temp != "") result.push_back(temp);
    return result;
  }

  string CombineStringVector(vector<string> target) {
    string result;
    for (size_t i = 0; i < target.size(); ++i) {
      result = result + target[i] + "|";
    }
    result.pop_back();
    return result;
  }

  bool InformCallbackFacilities(CallbackFacilityLauncher launcher, ObjectTypeFetcher fetcher) {
    int_fetcher = launcher("int");
    float_fetcher = launcher("float");
    bool_fetcher = launcher("bool");
    string_fetcher = launcher("string");
    wstring_fetcher = launcher("wstring");
    func_ptr_fetcher = launcher("function_pointer");
    obj_ptr_fetcher = launcher("object_pointer");
    type_fetcher = fetcher;

    return (int_fetcher   != nullptr)
      && (float_fetcher   != nullptr)
      && (bool_fetcher    != nullptr)
      && (string_fetcher  != nullptr)
      && (wstring_fetcher != nullptr)
      && (type_fetcher    != nullptr);
  }

  bool InformMemoryMgmtInterface(MemoryDisposer disposer_ptr, MemoryDisposer group_disposer_ptr) {
    disposer = disposer_ptr;
    group_disposer = group_disposer_ptr;
    return (disposer != nullptr) && (group_disposer_ptr != nullptr);
  }

  bool InformErrorThrowingInterface(ErrorInformer informer) {
    error_informer = informer;
    return error_informer != nullptr;
  }

  IntValue FromIntObject(string id, void *obj_map) {
    int64_t *buffer = nullptr;
    int result = int_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    int64_t value = *buffer;
    disposer(buffer, kExtTypeInt);
    return value;
  }

  FloatValue FromFloatObject(string id, void *obj_map) {
    double *buffer = nullptr;
    int result = float_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    double value = *buffer;
    disposer(buffer, kExtTypeFloat);
    return value;
  }

  BoolValue FromBoolObject(string id, void *obj_map) {
    int *buffer = nullptr;
    int result = bool_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    bool value = (*buffer == 1);
    disposer(buffer, kExtTypeBool);
    return value;
  }

  StringValue FromStringObject(string id, void *obj_map) {
    char *buffer = nullptr;
    int result = string_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    string value(buffer);
    group_disposer(buffer, kExtTypeString);
    return value;
  }

  WideStringValue FromWideStringObject(string id, void *obj_map) {
    wchar_t *buffer = nullptr;
    int result = wstring_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    wstring value(buffer);
    group_disposer(buffer, kExtTypeWideString);
    return value;
  }

  FunctionPointerValue FromFunctionPointerObject(string id, void *obj_map) {
    GenericFunctionPointer *buffer = nullptr;
    int result = func_ptr_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    CABIContainer value{ *buffer };
    disposer(buffer, kExtTypeFunctionPointer);
    return value;
  }

  ObjectPointerValue FromObjPointerObject(string id, void *obj_map) {
    GenericPointer *buffer = nullptr;
    int result = obj_ptr_fetcher((void **)&buffer, obj_map, id.data());
    if (result != 1) return nullopt;
    GenericPointer value = *buffer;
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

  void ReturnFunctionPointerObject(GenericFunctionPointer value, VMState state) {
    CABIContainer obj{ value };
    state.tunnel(&obj, state.ret_slot, kExtTypeFunctionPointer);
  }

  void ReturnObjPointerObject(GenericPointer value, VMState state) {
    state.tunnel(&value, state.ret_slot, kExtTypeObjectPointer);
  }

  void ThrowError(string msg, VMState state) {
    error_informer(state.vm, msg.data());
  }

  ExtActivityReturnType GetObjectType(void *obj_map, string id) {
    return ExtActivityReturnType(type_fetcher(obj_map, id.data()));
  }
}