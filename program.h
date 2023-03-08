#ifndef program_h
#define program_h

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

GLuint create_shader(const char *, GLenum);

GLuint create_program(const char **);

#endif
