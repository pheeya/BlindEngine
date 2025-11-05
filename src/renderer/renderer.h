#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM


#include <renderer/model/model.h>
#include <glad/glad.h>
#include <ecs/component.h>
#include <engine/engine.h>
#include <list/list.h>

struct BeRenderer{
BeList* renderList;
BeShader* defaultShader;
BeList* frames;

};


void be_render_model(struct BeRenderer* _renderer,model_t * _model);

void renderer_submit_model(struct BeRenderer* _engine,model_t* _model);
void renderer_render_frames(struct BeRenderer* _engine, float _dt, float _unscaledDt);




#endif
