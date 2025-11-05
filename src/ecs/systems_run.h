#ifndef ECS_SYSTEMS_RUNNER
#define ECS_SYSTEMS_RUNNER
#include <engine/engine.h>





void systems_run_startup(BeEngine *_engine);
void systems_run_update(BeEngine *_engine, float _dt, float _unscaledDt);

void systems_run_fixed_update(BeEngine* _engine, float _dt, float _unscaledDt);

void systems_run_renderer_update(BeEngine *_engine, float _dt, float _unscaledDt);



#endif
