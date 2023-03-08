#include "window.h"

void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height)
{
  glViewport(0, 0, width, height);
}

GLFWwindow* initialize_window(int32_t width, int32_t height, char* title)
{
  glfwInit();
  
  // set OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
 
  // use only core functionality
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
  // disallow depricated functionality
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
 
  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    printf("failed to create window\n");
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);

  // disable vsync
  glfwSwapInterval(0);
 
  return window;
}

double aspect_ratio(GLFWwindow *window)
{
  int32_t width, height;
  glfwGetWindowSize(window, &width, &height);
  return (double) height / (double) width;
}

int64_t pixel_count(GLFWwindow *window)
{
  int32_t width, height;
  glfwGetWindowSize(window, &width, &height);
  return (int64_t) height * (int64_t) width;
}
