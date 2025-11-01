#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM


#include <renderer/model/model.h>
#include <glad/glad.h>
#include <ecs/component.h>
#include <engine/engine.h>


typedef struct {

} renderer_t;

void renderer_init(engine_t* _engine);

void renderer_render_model(model_t * _model);

void renderer_submit_model(model_t* _model);
void renderer_render_cameras(engine_t* _engine, float _dt, float _unscaledDt);

#endif
