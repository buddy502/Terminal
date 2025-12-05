#pragma once

#include "openglHandles.h"

#include <fstream>
#include <sstream>

#include <iostream>
#include <string>

struct WindowValues {
   int Width = 800;
   int Height = 640;
   const char* Title = "Terminal";
};

class TerminalWindow {
   public:
      TerminalWindow() {
         values = WindowValues();
      }

      GLFWwindow* glfwWindow = nullptr;
      WindowValues values;

      // initialize glfw window
      int initTermWindow();

      // the main initializer function in main for now
      int init();
};

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
