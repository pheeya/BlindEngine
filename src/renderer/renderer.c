#include "renderer.h"
#include <GLFW/glfw3.h>
#include <components/camera.h>
#include <components/component_list.h>
#include <ecs/component.h>
#include <renderer/model/surface/shader.h>

void renderer_render_model(struct BeRenderer* _renderer,model_t *_model) {

  for (int i = 0; i < _model->mesh_count; i++) {
    shader_bind(_renderer->defaultShader);

    glBindVertexArray(_model->buffers[i].vao);
    glDrawElements(GL_TRIANGLES, _model->meshes[i].trisCount, GL_UNSIGNED_INT,
                   0);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

// this is the old code where we rendererd from BeList, use this as reference for the function that now calls the new render_all function
//void render_all(struct BeRenderer *_renderer, camera_t *_cam){
//
//  // submitted models
//  for (int i = 0; i < _renderer->renderList->count; i++) {
//    model_t **_pointer = (model_t **)be_list_get_at(_renderer->renderList, i);
//    model_t *_model = *_pointer;
//    renderer_render_model(_renderer,_model);
//  }
//
//  // model components
//  component_pool_t *pool =
//      component_registry_get_pool(_engine->componentRegistry, COMPONENT_MODEL);
//
//  for (int i = 0; i < pool->set->dataPages.count; i++) {
//
//    model_t *dataArray =
//        (model_t *)pool->set->dataPages.pagePointers[i]->content;
//    for (int j = 0; j < pool->set->dataPages.pagePointers[i]->count; j++) {
//      model_t *model = dataArray + j;
//
//      renderer_render_model(_engine,model);
//    }
//  }
//
//}
void render_all(struct BeRenderer *_renderer, camera_t *_cam){

  // submitted models
  for (int i = 0; i < _renderer->lengthVolatileList; i++) {
    renderer_render_model(_renderer,&_renderer->volatileList[i]);
  }
  for (int i = 0; i < _renderer->lengthRenderList; i++) {
    renderer_render_model(_renderer,&_renderer->renderList[i]);
  }
}
void renderer_render_frames(struct BeRenderer* _renderer) {

  glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(.1f, .1f, .1f, 1);
  component_pool_t *cameraPool =
      component_registry_get_pool(_engine->componentRegistry, COMPONENT_CAMERA);

  for (int i = 0; i < cameraPool->set->dataPages.count; i++) {
    camera_t *cameraArray =
        (camera_t *)cameraPool->set->dataPages.pagePointers[i]->content;

    for (int j = 0; j < cameraPool->set->dataPages.pagePointers[i]->count;
         j++) {

      camera_t *cam = cameraArray + j;
           render_all(_engine, cam);   
     }
  }
}


void renderer_clear_submitted_models(struct BeRenderer* _renderer) { be_list_clear(_renderer->renderList); }

/// @brief Submit models to render manually without using the model component.
/// Use with caution - expects pointer stability. Otherwise clear the list and
/// provide fresh pointers.
/// @param _model
void renderer_submit_model(engine_t* _engine,model_t *_model) {
  list_add(m_renderModels, &_model);
}
