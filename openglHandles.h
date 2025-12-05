#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>
#include <sstream>

// handle opengl errors
inline void GLClearError() {
   while(glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line) {
   while (GLenum error = glGetError()) {
      const GLubyte* errString = gluErrorString(error);
      std::cout << "OpenGl Error: (" << errString << "): " << function 
         << file << " : " << line << std::endl;
      return false;
   }
   return true;
}

// NOTE: !(x) makes sure the NOT has higher precedence
// when used in certain conditions
#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(func) GLClearError();\
   func;\
   ASSERT(GLLogCall(#func, __FILE__, __LINE__));\
