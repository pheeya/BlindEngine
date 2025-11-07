#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM


#include <renderer/model/model.h>
#include <glad/glad.h>
#include <ecs/component.h>
#include <engine/engine.h>
#include <list/list.h>

struct BeRenderer{
model_t* renderList;
model_t* volatileList;
uint32_t lengthRenderList;
uint32_t lengthVolatileList;
BeShader* defaultShader;
};


void be_render_model(struct BeRenderer* _renderer,model_t * _model);

void renderer_submit_model(struct BeRenderer* _renderer,model_t* _model);
void renderer_sys_render_all(struct BeRenderer* _renderer, float _dt, float _unscaledDt);




#endif
