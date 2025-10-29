#ifndef BLIND_ENGINE_APPLICATION
#define BLIND_ENGINE_APPLICATION
#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/system.h>
#include <engine/engine.h>
typedef struct
{
    engine_t* engine;
} application_t;




application_t* application_create();


#endif