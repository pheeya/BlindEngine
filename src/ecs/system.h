#ifndef ECS_SYSTEMS
#define ECS_SYSTEMS
#include <list/list.h>
#include <ecs/system_function_pointer.h>
#include <ecs/system_registry.h>
#include <engine/engine.h>




void system_register_startup(engine_t* _engine, BeSystemFunction _systemFunc);
void system_register_update(engine_t *_registry, BeSystemTimedFunction _systemFunc);
void system_register_render(engine_t *_registry, BeSystemTimedFunction _systemFunc);
void system_register_fixed_update(engine_t *_registry, BeSystemTimedFunction _systemFunc);



#endif
