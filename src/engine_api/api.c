#include "blindengine.h"


// // components
component_id_t COMPONENT_TRANSFORM;
component_id_t COMPONENT_MODEL;
component_id_t COMPONENT_CAMERA;

void engine_register_system(engine_t *engine, systems_target_t _target, system_function_pointer_t _system)
{
    system_register(engine->SystemRegistry, _system, _target);
}

void engine_register_default_components(engine_t *engine)
{

    transform_t pos = component_transform_get_prototype();
    COMPONENT_TRANSFORM = engine_register_component(engine, &pos, sizeof(transform_t));

    model_t modelPrototype = component_model_get_prototype();
    COMPONENT_MODEL = engine_register_component(engine, &modelPrototype, sizeof(model_t));
}

component_id_t engine_register_component(engine_t *engine, void *_prototype, size_t _size)
{
    component_id_t id = component_register(engine->ComponentRegistry, _prototype, _size, 100, MAX_ENTITIES);
    return id;
}

entity_t engine_create_entity(engine_t *engine)
{
    entity_t en = entity_create(engine->EntityRegistry);

    return en;
}

void *engine_add_component(engine_t *engine, component_id_t _component, entity_t _entity)
{
    void *comp = component_create_instance(engine->ComponentRegistry, _component, entity_get_id(_entity));

    return comp;
}

bool engine_remove_component(engine_t *engine, component_id_t _component, entity_t _from)
{
    bool did = component_remove_instance(engine->ComponentRegistry, _component, entity_get_id(_from));
    return did;
}

bool engine_has_component(engine_t *engine, component_id_t _component, entity_t entity)
{
    bool exists = component_exists(engine->ComponentRegistry, _component, entity_get_id(entity));
    return exists;
}

uint32_t engine_get_component_count(engine_t *engine, component_id_t _component)
{
    component_pool_t *pool = component_registry_get_pool(engine->ComponentRegistry, _component);

    return pool->set->dataCount;
}

uint32_t engine_get_entity_count(engine_t *engine)
{
    return engine->EntityRegistry->count;
}
