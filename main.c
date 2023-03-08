#include "main.h"

int main()
{
  GLFWwindow *window = initialize_window(720, 720, "mandelbrot");

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    return 1;
  }

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GLfloat vertices[8] = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0x0);
  glEnableVertexAttribArray(0);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  GLuint elements[6] = {0, 1, 2, 2, 1, 3};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  const char **shaders = get_shaders();
  GLuint shaderProgram = create_program(shaders);
  glUseProgram(shaderProgram);

  double time = glfwGetTime();
  double fps = 30.0f;
  struct timespec req = {0};

  glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
 
  double ar = aspect_ratio(window);
  GLuint ar_uniform = glGetUniformLocation(shaderProgram, "ar");
  glUniform1f(ar_uniform, ar);
  int64_t pc = pixel_count(window);

  double x_pos = 0.0f;
  GLuint x_pos_uniform = glGetUniformLocation(shaderProgram, "x_pos");
  glUniform1f(x_pos_uniform, x_pos);

  double y_pos = 0.0f;
  GLuint y_pos_uniform = glGetUniformLocation(shaderProgram, "y_pos");
  glUniform1f(y_pos_uniform, y_pos);

  double height = 1.0f;
  GLuint height_uniform = glGetUniformLocation(shaderProgram, "height");
  glUniform1f(height_uniform, height);

  int32_t bound = 100;
  GLuint bound_uniform = glGetUniformLocation(shaderProgram, "bound");
  glUniform1i(bound_uniform, bound);

  while (!glfwWindowShouldClose(window)) {

    if (ar != aspect_ratio(window)) {
      ar = aspect_ratio(window);
      glUniform1f(ar_uniform, ar);
      //printf("resized\n");
      pc = pixel_count(window);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);

    int8_t input = 0;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      x_pos += 1.0f / fps * height;
      glUniform1f(x_pos_uniform, x_pos);
      input = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      x_pos -= 1.0f / fps * height;
      glUniform1f(x_pos_uniform, x_pos);
      input = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      y_pos += 1.0f / fps * height;
      glUniform1f(y_pos_uniform, y_pos);
      input = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      y_pos -= 1.0f / fps * height;
      glUniform1f(y_pos_uniform, y_pos);
      input = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      height *= 1.0f + 1.0f / fps;
      glUniform1f(height_uniform, height);
      input = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
      height /= 1.0f + 1.0f / fps;
      glUniform1f(height_uniform, height);
      input = 1;
    }
    glfwPollEvents();

    if (input) {
      int64_t total = 1;
      // this does not seem to be useful on my new hardware:
      /*
      for (int32_t i = 0; i < 10000; i++) {
        float Cr = (random()/(RAND_MAX/2.0f)-1.0f)/ar*height+x_pos;
        float Ci = (random()/(RAND_MAX/2.0f)-1.0f)*height+y_pos;
        float Zr = Cr;
        float Zi = Ci;
        int32_t i;
        for (i = 0; i < 100; i++) {
          if (Zr * Zr + Zi * Zi >= 4.0f) {
            break;
          }
          float temp = Zr;
          Zr = Zr * Zr - Zi * Zi + Cr;
          Zi = 2.0f * temp * Zi + Ci;
        }
        total += i;
      }    
      bound = (bound + UINT64_C(1000000000) * 720 * 720 / total / pc) / 2;
      bound = bound > 256 ? 256 : bound;
      */
      if (height < 0.5) {
        bound = (3.0f - 2.0f * height) * 256.0f;
      } else {
        bound = 256.0f / height;
        if (bound < 6) {
          bound = 6;
        }
      }
      printf("total: %lld bound: %d\n", total, bound);
      glUniform1i(bound_uniform, bound);
    }

    req.tv_nsec = (int64_t)(((1.0f / fps) - (glfwGetTime() - time)) * 1000000000.0f);
    nanosleep(&req, NULL);
    time = glfwGetTime();

  }

  glDeleteProgram(shaderProgram);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vao);
  glfwTerminate();
 
  return 0;
}
