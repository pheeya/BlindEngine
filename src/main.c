#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <ecs/component.h>
#include <ecs/entity.h>
#include <ecs/system.h>
#include <ecs/component.h>
#include <window/window.h>
#include <ecs/systems_run.h>
#include <engine/engine.h>
#include <blindengine.h>
#include <application/application.h>
#include <components/component_list.h>
#include <systems/testsystem/testsystem.h>
#include <renderer/model/model.h>
#include <renderer/rendererSystem.h>
#include <freetype/ftcache.h>



// // components
// component_id_t COMPONENT_TRANSFORM;
// component_id_t COMPONENT_MODEL;

// void RegisterComponents(engine_t *engine)
// {

//     transform_t pos = component_transform_get_prototype();
//     COMPONENT_TRANSFORM = engine_register_component(engine, &pos, sizeof(transform_t));

//     model_t modelPrototype = component_model_get_prototype();
//     COMPONENT_MODEL = engine_register_component(engine, &modelPrototype, sizeof(model_t));
// }

// void OnWindowCloseAttempted(window_t *wind)
// {
//     engine_t *owner = (engine_t *)wind->owner;
//     engine_stop(owner);
//     window_terminate(wind);
// }
// int main(int _numArgs, char *args[])
// {

//     application_t *App = application_create();
//     engine_t *engine = App->engine;

//     window_t *window = window_create(engine);

//     // register systems

//     engine_register_system(engine, SYSTEMS_TARGET_UPDATE, window_before_render);

//     engine_register_system(engine, SYSTEMS_TARGET_FIRST, ts_first);
//     engine_register_system(engine, SYSTEMS_TARGET_STARTUP, ts_startup);
//     engine_register_system(engine, SYSTEMS_TARGET_UPDATE, ts_update);
//     engine_register_system(engine, SYSTEMS_TARGET_POST_UPDATE, ts_post_update);

//     engine_register_system(engine, SYSTEMS_TARGET_FIRST, renderer_init);
//     engine_register_system(engine, SYSTEMS_TARGET_RENDERER_UPDATE, renderer_render_all);

//     engine_register_system(engine, SYSTEMS_TARGET_RENDERER_UPDATE, window_post_render);

//     window_set_close_callback(window, OnWindowCloseAttempted);

//     // register components
//     RegisterComponents(engine);

//     engine_run(engine);
//     systems_run_startup(engine);

//     return 0;
// }
