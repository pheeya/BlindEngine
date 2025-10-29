#ifndef WINDOW
#define WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <engine/engine.h>

typedef struct window_t window_t;

typedef void (*window_close_callback_t)(window_t *window);
typedef struct window_t
{
    GLFWwindow *glfwWindow;
    window_close_callback_t window_close_callback;
    void* owner;

} window_t;

window_t *window_create(void* owner);
void window_terminate(window_t* win);
bool window_should_close(window_t *_window);

void window_before_render(engine_t *_engine);
void window_post_render(engine_t *_engine);

void window_set_close_callback(window_t *win, window_close_callback_t _cb);
#endif
