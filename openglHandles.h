#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>

struct s_ShaderFile {
   std::string vertexShader;
   std::string fragmentShader;
};

inline struct s_ShaderFile ParseShaderFile(const std::string& filepath) {
   enum class ShaderType {
      NONE = -1, VERTEX = 0, FRAGMENT = 1
   };

   std::ifstream stream(filepath);
   std::string line;
   std::stringstream ss[2];
   ShaderType type = ShaderType::NONE;

   while (getline(stream, line)) {
      if (line.find("#shader") != std::string::npos) {
         if (line.find("vertex") != std::string::npos)
            type = ShaderType::VERTEX;
         else if (line.find("fragment") != std::string::npos)
            type = ShaderType::FRAGMENT;
      }
      else {
         ss[(int)type] << line << '\n';
      }
   }

   return { ss[0].str(), ss[1].str() };
}

class GLHandles {
   public:
      s_ShaderFile shaderFile;

      GLHandles() = default;
      ~GLHandles() = default;

      uint CompileShader(uint type, const std::string& shaderSource);
      uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

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
   ASSERT(GLLogCall(#func, __FILE__, __LINE__));
