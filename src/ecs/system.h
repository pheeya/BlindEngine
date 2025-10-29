#ifndef ECS_SYSTEMS
#define ECS_SYSTEMS
#include <stdint.h>
#include <list/list.h>
#include <ecs/system_function_pointer.h>
#include <ecs/system_registry.h>



typedef uint8_t systems_target_t;


// compile time constants to make them work with switch statements
#define SYSTEMS_TARGET_STARTUP  0
#define SYSTEMS_TARGET_FIRST  1
#define SYSTEMS_TARGET_PRE_UPDATE  2
#define SYSTEMS_TARGET_UPDATE  3
#define SYSTEMS_TARGET_POST_UPDATE  4
#define SYSTEMS_TARGET_RENDERER_UPDATE  5
#define SYSTEMS_TARGET_FIXED_UPDATE  6
 



void system_register(systems_registry_t *_registry, system_function_pointer_t _systemFunc, systems_target_t _target);






#endif
