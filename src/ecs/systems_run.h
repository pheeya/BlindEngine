#ifndef ECS_SYSTEMS_RUNNER
#define ECS_SYSTEMS_RUNNER
#include <engine/engine.h>





void systems_run_startup(engine_t *_engine);
void systems_run_first(engine_t *_engine);
void systems_run_pre_update(engine_t *_engine);
void systems_run_update(engine_t *_engine);
void systems_run_post_update(engine_t *_engine);


/// @brief This is just another system target, the name is just for semantics. You don't have to use a renderer and you don't have to subscribe your renderer to this target. Any system can subscribe to this.
/// @param _engine 
void systems_run_renderer_update(engine_t *_engine);


void systems_run_fixed_update(engine_t *_engine);

#endif