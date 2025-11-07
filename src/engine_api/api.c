#include "blindengine.h"

// // components
ComponentId COMPONENT_TRANSFORM;
ComponentId COMPONENT_MODEL;
ComponentId COMPONENT_CAMERA;

void be_register_startup(BeEngine *engine, BeSystemFunction _system) {
  system_register_startup(engine, _system);
}
void be_register_update(BeEngine *engine, BeSystemTimedFunction _system) {
  system_register_update(engine, _system);
}
void be_register_fixed_update(BeEngine *engine, BeSystemTimedFunction _system) {
  system_register_fixed_update(engine, _system);
}
void be_register_render(BeEngine *engine, BeSystemTimedFunction _system) {
  system_register_render(engine, _system);
}
void be_sys_renderer_create(BeEngine *_engine) {
struct BeRenderer* renderer = malloc(sizeof(struct BeRenderer));

  renderer->defaultShader= shader_load_from_file("../assets/shaders/Test");
  renderer->renderList = be_list_create(64,sizeof(model_t *));
_engine->renderer = renderer;
}


void engine_register_default_components(BeEngine *engine) {

  transform_t pos = component_transform_get_prototype();
  COMPONENT_TRANSFORM =
      engine_register_component(engine, &pos, sizeof(transform_t));

  model_t modelPrototype = component_model_get_prototype();
  COMPONENT_MODEL =
      engine_register_component(engine, &modelPrototype, sizeof(model_t));
}


// ecs
ComponentId engine_register_component(BeEngine *engine, void *_prototype,
                                         size_t _size) {
  ComponentId id = component_register(engine->componentRegistry, _prototype,
                                         _size, 100, MAX_ENTITIES);
  return id;
}

entity_t engine_create_entity(BeEngine *engine) {
  entity_t en = entity_create(engine->entityRegistry);

  return en;
}

void *engine_add_component(BeEngine *engine, ComponentId _component,
                           entity_t _entity) {
  void *comp = component_create_instance(engine->componentRegistry, _component,
                                         entity_get_id(_entity));

  return comp;
}

bool engine_remove_component(BeEngine *engine, ComponentId _component,
                             entity_t _from) {
  bool did = component_remove_instance(engine->componentRegistry, _component,
                                       entity_get_id(_from));
  return did;
}

bool engine_has_component(BeEngine *engine, ComponentId _component,
                          entity_t entity) {
  bool exists = component_exists(engine->componentRegistry, _component,
                                 entity_get_id(entity));
  return exists;
}

uint32_t engine_get_component_count(BeEngine *engine,
                                    ComponentId _component) {
  component_pool_t *pool =
      component_registry_get_pool(engine->componentRegistry, _component);

  return pool->set->dataCount;
}

uint32_t engine_get_entity_count(BeEngine *engine) {
  return engine->entityRegistry->count;
}
