#ifndef WINDOW
#define WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <engine/engine.h>

struct BeWindow;

typedef void (*BeWindowCloseCallback)(struct BeWindow *window);
struct BeWindow
{
    GLFWwindow *glfwWindow;
    BeWindowCloseCallback window_close_callback;
    void* owner;

};

struct BeWindow *window_create(void* owner);
void window_terminate(struct BeWindow* win);
bool window_should_close(struct BeWindow *_window);

void window_set_close_callback(struct BeWindow *win, BeWindowCloseCallback _cb);

void window_update(BeEngine* _engine, float _dt, float _unscaledDt);
void window_render(BeEngine* _engine, float _dt, float _unscaledDt);
#endif
