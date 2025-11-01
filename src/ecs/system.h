#ifndef ECS_SYSTEMS
#define ECS_SYSTEMS
#include <list/list.h>
#include <ecs/system_function_pointer.h>
#include <ecs/system_registry.h>





void system_register_startup(BeSystemsRegistry *_registry, BeSystemFunction _systemFunc);
void system_register_update(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc);
void system_register_render(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc);
void system_register_fixed_update(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc);



#endif
