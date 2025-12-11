#include "openglHandles.h"

uint GLHandles::CompileShader(uint type, const std::string& shaderSource) {
   uint id = glCreateShader(type);
   const char* src = shaderSource.c_str();
   GLCall(glShaderSource(id, 1, &src, nullptr));
   GLCall(glCompileShader(id));

   int result;
   GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
   if (result == GL_FALSE){
      int length;
      GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
      char* message = (char*)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(id, length, &length, message));
      std::cout << "Failed to compile shader" << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(id));
      return 0;
   }

   return id;
}

uint GLHandles::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
   GLCall(uint program = glCreateProgram());

   uint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
   uint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

   GLCall(glAttachShader(program, vs));
   GLCall(glAttachShader(program, fs));

   GLCall(glLinkProgram(program));
   GLCall(glValidateProgram(program));

   GLCall(glDeleteShader(vs));
   GLCall(glDeleteShader(fs));

   return program;
}
