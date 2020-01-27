#pragma once
#include "assist_common.h"

namespace kagami {
  const Descriptor kEmptyDescriptpr{ nullptr, kExtUnsupported };

  struct _UnsupportedObjectType {};
  struct NullObjectType {};

  template <ObjectType _TypeCode>
  struct _ObjectTypeTrait {
    using Type = _UnsupportedObjectType;
  };

  template <typename _Type>
  struct _RevObjectTypeTrait {
    static const ObjectType type = kExtUnsupported;
  };

#define INIT_OBJECT_TYPE(_TypeCode, _Type)                   \
  template <>                                                \
  struct _ObjectTypeTrait<_TypeCode> { using Type = _Type; };

  INIT_OBJECT_TYPE(kExtTypeNull, NullObjectType)
  INIT_OBJECT_TYPE(kExtTypeInt, int64_t)
  INIT_OBJECT_TYPE(kExtTypeFloat, double)
  INIT_OBJECT_TYPE(kExtTypeBool, int)
  INIT_OBJECT_TYPE(kExtTypeString, string)
  INIT_OBJECT_TYPE(kExtTypeWideString, wstring)
  INIT_OBJECT_TYPE(kExtTypeFunctionPointer, GenericFunctionPointer)
  INIT_OBJECT_TYPE(kExtTypeObjectPointer, GenericPointer)
  
#undef INIT_OBJECT_TYPE
#define INIT_REV_OBJECT_TYPE(_Type, _TypeCode)               \
  template <>                                                \
  struct _RevObjectTypeTrait<_Type> { static const ObjectType type = _TypeCode; };

  INIT_REV_OBJECT_TYPE(NullObjectType, kExtTypeNull)
  INIT_REV_OBJECT_TYPE(int64_t, kExtTypeInt)
  INIT_REV_OBJECT_TYPE(double, kExtTypeFloat)
  INIT_REV_OBJECT_TYPE(int, kExtTypeBool)
  INIT_REV_OBJECT_TYPE(string, kExtTypeString)
  INIT_REV_OBJECT_TYPE(wstring, kExtTypeWideString)
  INIT_REV_OBJECT_TYPE(GenericFunctionPointer, kExtTypeFunctionPointer)
  INIT_REV_OBJECT_TYPE(GenericPointer, kExtTypeObjectPointer)

#undef INIT_REV_OBJECT_TYPE
  
  constexpr bool _IsStringObject(ObjectType type) {
    return type == kExtTypeString || type == kExtTypeWideString;
  }

  //For future string replacement?
  template <typename _Type>
  struct _CharTypeTrait { using Type = _UnsupportedObjectType; };
  template <>
  struct _CharTypeTrait<string> { using Type = char; };
  template <>
  struct _CharTypeTrait<wstring> { using Type = wchar_t; };

  template <ObjectType _TypeCode>
  struct _CharTypeTraitS { using Type = _UnsupportedObjectType; };
  template <>
  struct _CharTypeTraitS<kExtTypeString> { using Type = char; };
  template <>
  struct _CharTypeTraitS<kExtTypeWideString> { using Type = wchar_t; };
}