#include <engine/engine.h>
#include <be_assert.h>
#include <ecs/systems_run.h>

engine_t *engine_create()
{
    engine_t *engine = malloc(sizeof(engine_t));
    ASSERT_MALLOC(engine);

    entity_registry_t *EntityRegistry = entity_registry_create(25);
    component_registry_t *ComponentRegistry = component_registry_create_registry(50);
    BeSystemsRegistry *SystemRegistry = system_registry_create();

    engine->EntityRegistry = EntityRegistry;
    engine->ComponentRegistry = ComponentRegistry;
    engine->SystemRegistry = SystemRegistry;

    return engine;
}

void engine_stop(engine_t *engine)
{
    engine->running = false;
}

void engine_run(engine_t *engine)
{
    engine->running = true;

    systems_run_startup(engine);
    while (engine->running)
    {
        systems_run_update(engine,-1,-1);
        systems_run_renderer_update(engine);
  systems_run_fixed_update(engine,-1,-1); 
   }
}
