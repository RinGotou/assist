#pragma once
#include "assist_common.h"

namespace kagami {
  void InformCallbackFacilities(CallbackFacilityLauncher launcher);
  void InformMemoryMgmtInterface(MemoryDisposer disposer, MemoryDisposer group_disposer);
}
