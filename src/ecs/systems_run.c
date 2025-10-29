#include <stdlib.h>
#include <ecs/systems_run.h>
#include <types/system_function_pointer.h>
#include "systems_run.h"

void systems_run_startup(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->startup_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->startup_list, i);
        func(_engine);
    }
}

void systems_run_first(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->first_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->first_list, i);
        func(_engine);
    }
}

void systems_run_pre_update(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->pre_update_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->pre_update_list, i);
        func(_engine);
    }
}

void systems_run_update(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->update_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->update_list, i);
        func(_engine);
    }
}

void systems_run_post_update(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->post_update_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->post_update_list, i);
        func(_engine);
    }
}

void systems_run_renderer_update(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->renderer_update_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->renderer_update_list, i);
        func(_engine);
    }
}
void systems_run_fixed_update(engine_t *_engine)
{
    systems_registry_t *_registry = _engine->SystemRegistry;
    for (int i = 0; i < _registry->fixed_update_list->count; i++)
    {
        system_function_pointer_t func = *(system_function_pointer_t *)list_getAt(_registry->fixed_update_list, i);
        func(_engine);
    }
}