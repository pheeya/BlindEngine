#include <be_assert.h>
#include <ecs/systems_run.h>
#include <engine/engine.h>

engine_t *engine_create(BeLogger *_appLogger) {
  engine_t *engine = malloc(sizeof(engine_t));
  engine->appLogger = _appLogger;

  BeLogger *engineLogger = malloc(sizeof(BeLogger));
  engineLogger->prefix = "be";
  engine->engineLogger = engineLogger;
  ASSERT_MALLOC(engine);

  entity_registry_t *EntityRegistry = entity_registry_create(25);
  component_registry_t *ComponentRegistry =
      component_registry_create_registry(50);
  BeSystemsRegistry *SystemRegistry = system_registry_create();

  engine->entityRegistry = EntityRegistry;
  engine->componentRegistry = ComponentRegistry;
  engine->systemRegistry = SystemRegistry;

  return engine;
}

void engine_stop(engine_t *engine) { engine->running = false; }

void engine_run(engine_t *engine) {
  engine->running = true;
  systems_run_startup(engine);
  while (engine->running) {
    systems_run_update(engine, -1, -1);
    systems_run_renderer_update(engine, -1, -1);
    systems_run_fixed_update(engine, -1, -1);
  }
}
