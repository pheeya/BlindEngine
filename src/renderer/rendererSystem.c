#include "rendererSystem.h"
#include <GLFW/glfw3.h>
#include <components/camera.h>
#include <components/component_list.h>
#include <ecs/component.h>
#include <engine/engine.h>
#include <renderer/model/surface/shader.h>
#include <types/list/list.h>
static list_t *m_renderModels;
static shader_t *m_defaultShader;

void renderer_init(engine_t *_engine) {
  m_defaultShader = shader_load_from_file("../assets/shaders/Test");
  m_renderModels = list_create_dynamic(sizeof(model_t *), 50, true);
}

void renderer_render_model(model_t *_model) {

  for (int i = 0; i < _model->mesh_count; i++) {
    shader_bind(m_defaultShader);

    glBindVertexArray(_model->buffers[i].vao);
    glDrawElements(GL_TRIANGLES, _model->meshes[i].trisCount, GL_UNSIGNED_INT,
                   0);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
void render_all(engine_t *_engine, camera_t *_cam){

  // submitted models
  for (int i = 0; i < m_renderModels->count; i++) {
    model_t **_pointer = (model_t **)list_getAt(m_renderModels, i);
    model_t *_model = *_pointer;
    renderer_render_model(_model);
  }

  // model components
  component_pool_t *pool =
      component_registry_get_pool(_engine->ComponentRegistry, COMPONENT_MODEL);

  for (int i = 0; i < pool->set->dataPages.count; i++) {

    model_t *dataArray =
        (model_t *)pool->set->dataPages.pagePointers[i]->content;
    for (int j = 0; j < pool->set->dataPages.pagePointers[i]->count; j++) {
      model_t *model = dataArray + j;

      renderer_render_model(model);
    }
  }

}
void renderer_render_cameras(engine_t *_engine) {

  glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(.1f, .1f, .1f, 1);
  component_pool_t *cameraPool =
      component_registry_get_pool(_engine->ComponentRegistry, COMPONENT_CAMERA);

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


void renderer_clear_submitted_models() { list_clear(m_renderModels); }

/// @brief Submit models to render manually without using the model component.
/// Use with caution - expects pointer stability. Otherwise clear the list and
/// provide fresh pointers.
/// @param _model
void renderer_submit_model(model_t *_model) {
  list_add(m_renderModels, &_model);
}
