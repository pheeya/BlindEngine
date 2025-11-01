#include "system.h"
#include <be_assert.h>

void system_register_startup(BeSystemsRegistry *_registry, BeSystemFunction _systemFunc){
be_list_append(_registry->startup_list, _systemFunc);
}
void system_register_update(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc){
be_list_append(_registry->update_list, _systemFunc);
}
void system_register_render(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc){
be_list_append(_registry->renderer_update_list, _systemFunc);
}
void system_register_fixed_update(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc){
be_list_append(_registry->fixed_update_list,_systemFunc);
}


