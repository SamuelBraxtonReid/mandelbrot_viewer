#ifndef window_h
#define window_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow*, int32_t, int32_t);

GLFWwindow* initialize_window(int32_t, int32_t, char *);

double aspect_ratio(GLFWwindow *);

int64_t pixel_count(GLFWwindow *);

#endif
