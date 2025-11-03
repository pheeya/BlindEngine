#include "system.h"
#include <be_assert.h>
void system_register_startup(engine_t* _engine, BeSystemFunction _systemFunc){
be_list_append(_engine->systemRegistry->startup_list, &_systemFunc);
}
void system_register_update(engine_t* _engine, BeSystemTimedFunction _systemFunc){
be_list_append(_engine->systemRegistry->update_list, &_systemFunc);
}
void system_register_render(engine_t* _engine, BeSystemTimedFunction _systemFunc){
be_list_append(_engine->systemRegistry->renderer_update_list, &_systemFunc);
}
void system_register_fixed_update(engine_t* _engine, BeSystemTimedFunction _systemFunc){
be_list_append(_engine->systemRegistry->fixed_update_list,&_systemFunc);
}


