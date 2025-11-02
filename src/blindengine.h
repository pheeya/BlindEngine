#ifndef BLIND_ENGINE_API
#define BLIND_ENGINE_API


// blindengine is no longer a dll, it's a static lib like hazel engine now
// #ifdef _WIN32
//     #define BLIND_ENGINE_EXPORT __declspec(dllexport)
//     #define BLIND_ENGINE_IMPORT __declspec(dllimport)
// #elif linux
//     #define BLIND_ENGINE_EXPORT __attribute__((visibility("default")))
//     #define BLIND_ENGINE_IMPORT
// #endif

// #ifdef BLIND_ENGINE_COMPILING
//     #define BLIND_ENGINE_FUNC BLIND_ENGINE_EXPORT
// #else
//     #define BLIND_ENGINE_FUNC BLIND_ENGINE_IMPORT
// #endif

#include <engine/engine.h>
#include <ecs/system.h>
#include <ecs/component.h>
#include <ecs/entity.h>
#include <ecs/system_function_pointer.h>
#include <application/application.h>
#include <window/window.h>
#include <renderer/rendererSystem.h>
#include <components/component_list.h>
#include <components/transform/transform.h>
#include <renderer/model/model.h>
#include <logger/logger.h>
void be_register_startup(engine_t *engine, BeSystemFunction _system);
void be_register_update(engine_t *engine, BeSystemTimedFunction _system);
void be_register_fixed_update(engine_t *engine, BeSystemTimedFunction _system);
void be_register_render(engine_t *engine, BeSystemTimedFunction _system);

void engine_register_default_components(engine_t *engine);

component_id_t engine_register_component(engine_t *engine, void *_prototype, size_t _size);

entity_t engine_create_entity(engine_t *engine);

void *engine_add_component(engine_t *engine, component_id_t _component, entity_t _to);

bool engine_remove_component(engine_t *engine, component_id_t _component, entity_t _from);
bool engine_has_component(engine_t *engine, component_id_t _component, entity_t entity);

uint32_t engine_get_component_count(engine_t *engine, component_id_t _component);
uint32_t engine_get_entity_count(engine_t *engine);

#endif
