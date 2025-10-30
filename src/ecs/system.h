#ifndef ECS_SYSTEMS
#define ECS_SYSTEMS
#include <stdint.h>
#include <list/list.h>
#include <ecs/system_function_pointer.h>
#include <ecs/system_registry.h>



typedef uint8_t BeSystemsTarget;


// compile time constants to make them work with switch statements
#define SYSTEMS_TARGET_STARTUP  0
#define SYSTEMS_TARGET_UPDATE  1
#define SYSTEMS_TARGET_RENDERER_UPDATE  2
#define SYSTEMS_TARGET_FIXED_UPDATE  3
 



void system_register(BeSystemsRegistry *_registry, BeSystemFunction _systemFunc, BeSystemsTarget _target);
void system_register_timed(BeSystemsRegistry *_registry, BeSystemTimedFunction _systemFunc, BeSystemsTarget _target);





#endif
