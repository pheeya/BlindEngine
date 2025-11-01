#ifndef BLIND_ENGINE
#define BLIND_ENGINE
#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/system_registry.h>
#include <stdbool.h>
typedef struct
{
    bool running;
    entity_registry_t *entityRegistry;
    component_registry_t *componentRegistry;
    BeSystemsRegistry *systemRegistry;
} engine_t;



extern engine_t App;



engine_t *engine_create();

void engine_run(engine_t* engine);
void engine_stop(engine_t* engine);



#endif
