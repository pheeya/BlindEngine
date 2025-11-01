#include <stdlib.h>
#include <ecs/systems_run.h>
#include <ecs/system_function_pointer.h>
#include "systems_run.h"

void systems_run_startup(engine_t *_engine)
{
    BeSystemsRegistry *_registry = _engine->systemRegistry;
    for (int i = 0; i < _registry->startup_list->count; i++)
    {
        BeSystemFunction func = *(BeSystemFunction *)list_getAt(_registry->startup_list, i);
        func(_engine);
    }
}

void systems_run_update(engine_t *_engine, float _dt, float _unscaledDt)
{
    BeSystemsRegistry *_registry = _engine->systemRegistry;
    for (int i = 0; i < _registry->update_list->count; i++)
    {
      BeSystemTimedFunction func = *(BeSystemTimedFunction *)list_getAt(_registry->update_list, i);
        func(_engine, _dt, _unscaledDt);
    }
}


void systems_run_renderer_update(engine_t *_engine, float _dt, float _unscaledDt)
{
    BeSystemsRegistry *_registry = _engine->systemRegistry;
    for (int i = 0; i < _registry->renderer_update_list->count; i++)
    {
      BeSystemTimedFunction func = *(BeSystemTimedFunction *)list_getAt(_registry->update_list, i);
        func(_engine, _dt, _unscaledDt);
    }
}
void systems_run_fixed_update(engine_t *_engine, float _dt, float _unscaledDt)
{
    BeSystemsRegistry *_registry = _engine->systemRegistry;
    for (int i = 0; i < _registry->fixed_update_list->count; i++)
    {
      BeSystemTimedFunction func = *(BeSystemTimedFunction *)list_getAt(_registry->update_list, i);
        func(_engine, _dt, _unscaledDt);
    }
}
