#include <window/window.h>
#include <GLFW/glfw3.h>
#include <be_assert.h>
#include <glad/glad.h>
#include <stdlib.h>

void onglfw_window_close(GLFWwindow *glfw) {
  struct BeWindow *win = (struct BeWindow *)glfwGetWindowUserPointer(glfw);
  if (win == NULL) {
    printf("Couldn't find window associated with glfw window\n");
    exit(1);
  }

  win->window_close_callback(win);
}
struct BeWindow *window_create(void *owner) {
  struct BeWindow *win = malloc(sizeof(struct BeWindow));
  win->owner = owner;
  ASSERT_MALLOC(win);
  GLFWwindow *glfwWindow;

  if (!glfwInit()) {
    exit(-1);
  }
  glfwWindow = glfwCreateWindow(500, 500, "Blind Engine", NULL, NULL);
  if (!glfwWindow) {
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(glfwWindow);
  win->glfwWindow = glfwWindow;

  int version = gladLoadGL();
  if (version == 0) {
    printf("Failed to initialize opengl context\n");
    exit(-1);
  }

  glfwSetWindowUserPointer(win->glfwWindow, win);
  return win;
}

void window_terminate(struct BeWindow *win) {
  glfwTerminate();

  free(win);
}

bool window_should_close(struct BeWindow *_window) {
  return glfwWindowShouldClose(_window->glfwWindow);
}

void window_set_close_callback(struct BeWindow *win, BeWindowCloseCallback _cb) {
  win->window_close_callback = _cb;
  glfwSetWindowCloseCallback(win->glfwWindow, onglfw_window_close);
}

void window_update(BeEngine *_engine, float _dt, float _unscaledDt) {
  glfwPollEvents();
}
void window_render(BeEngine *_engine, float _dt, float _unscaledDt) {
  glfwSwapBuffers(glfwGetCurrentContext());
}
