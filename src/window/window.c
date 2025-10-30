#include <window/window.h>
#include <stdlib.h>
#include <be_assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"




void onglfw_window_close(GLFWwindow *glfw)
{
    window_t *win = (window_t *)glfwGetWindowUserPointer(glfw);
    if (win == NULL)
    {
        printf("Couldn't find window associated with glfw window\n");
        exit(1);
    }

    win->window_close_callback(win);
}
window_t *window_create(void *owner)
{
    window_t *win = malloc(sizeof(window_t));
    win->owner = owner;
    ASSERT_MALLOC(win);
    GLFWwindow *glfwWindow;

    if (!glfwInit())
    {
        exit(-1);
    }
    glfwWindow = glfwCreateWindow(500,500, "Blind Engine", NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(glfwWindow);
    win->glfwWindow = glfwWindow;

    int version = gladLoadGL();
    if (version == 0)
    {
        printf("Failed to initialize opengl context\n");
        exit(-1);
    }

    glfwSetWindowUserPointer(win->glfwWindow, win);
    return win;
}

void window_terminate(window_t *win)
{
    glfwTerminate();

    free(win);
}

bool window_should_close(window_t *_window)
{
    return glfwWindowShouldClose(_window->glfwWindow);
}

void window_set_close_callback(window_t *win, window_close_callback_t _cb)
{
    win->window_close_callback = _cb;
    glfwSetWindowCloseCallback(win->glfwWindow, onglfw_window_close);
}

void window_before_render(engine_t *_engine)
{
}
void window_post_render(engine_t *_engine)
{
    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
}
