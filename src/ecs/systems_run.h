#ifndef ECS_SYSTEMS_RUNNER
#define ECS_SYSTEMS_RUNNER
#include <engine/engine.h>





void systems_run_startup(engine_t *_engine);
void systems_run_update(engine_t *_engine, float _dt, float _unscaledDt);

void systems_run_fixed_update(engine_t* _engine, float _dt, float _unscaledDt);

void systems_run_renderer_update(engine_t *_engine, float _dt, float _unscaledDt);



#endif
