#ifndef BLIND_ENGINE
#define BLIND_ENGINE
#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/system_registry.h>
#include <stdbool.h>
#include <logger/logger.h>



typedef struct
{
    bool running;
    entity_registry_t *entityRegistry;
    component_registry_t *componentRegistry;
    BeSystemsRegistry *systemRegistry;
    BeLogger* engineLogger;
    BeLogger* appLogger;
    struct BeRenderer* renderer;
} BeEngine;



extern BeEngine App;



BeEngine *engine_create(BeLogger* _appLogger);

void engine_run(BeEngine* engine);
void engine_stop(BeEngine* engine);



#endif
