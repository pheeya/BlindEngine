#include "system.h"
#include <be_assert.h>

void system_register(BeSystemsRegistry *_registry,
                     BeSystemFunction _systemFunc, BeSystemsTarget _target) {
  switch (_target) {
  case SYSTEMS_TARGET_STARTUP: {

    list_add(_registry->startup_list, _systemFunc);
    break;
  }
  }
}

void system_register_timed(BeSystemsRegistry *_registry,
                           BeSystemTimedFunction _systemFunc,
                           BeSystemsTarget _target) {
  switch (_target)

  {
  case SYSTEMS_TARGET_UPDATE: {

    list_add(_registry->update_list, _systemFunc);
    break;
  }
  case SYSTEMS_TARGET_RENDERER_UPDATE: {

    list_add(_registry->renderer_update_list, _systemFunc);
    break;
  }
  case SYSTEMS_TARGET_FIXED_UPDATE: {

    list_add(_registry->fixed_update_list, _systemFunc);
    break;
  }
  };
}
