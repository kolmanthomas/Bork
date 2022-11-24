#pragma once

#include <GLFW/glfw3.h>

#include <iostream>

#define glCheckError() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            GLuint id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam);

GLenum glCheckError_(const char *file, int line);
