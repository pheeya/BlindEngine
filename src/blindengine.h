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
#include <renderer/renderer.h>
#include <components/component_list.h>
#include <components/transform/transform.h>
#include <renderer/model/model.h>
#include <logger/logger.h>
void be_register_startup(BeEngine *engine, BeSystemFunction _system);
void be_register_update(BeEngine *engine, BeSystemTimedFunction _system);
void be_register_fixed_update(BeEngine *engine, BeSystemTimedFunction _system);
void be_register_render(BeEngine *engine, BeSystemTimedFunction _system);

void engine_register_default_components(BeEngine *engine);

void be_sys_renderer_create(BeEngine* _engine);

// ecs
ComponentId engine_register_component(BeEngine *engine, void *_prototype, size_t _size);

entity_t engine_create_entity(BeEngine *engine);

void *engine_add_component(BeEngine *engine, ComponentId _component, entity_t _to);

bool engine_remove_component(BeEngine *engine, ComponentId _component, entity_t _from);
bool engine_has_component(BeEngine *engine, ComponentId _component, entity_t entity);

uint32_t engine_get_component_count(BeEngine *engine, ComponentId _component);
uint32_t engine_get_entity_count(BeEngine *engine);

#endif
