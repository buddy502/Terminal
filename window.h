#pragma once

#include "openglHandles.h"

#include <fstream>
#include <sstream>

#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

struct s_WindowValues {
   int Width = 800;
   int Height = 640;
   const char* Title = "Terminal";

   s_WindowValues() = default;

   s_WindowValues(int width, int height, const char* title)
      : Width(width), Height(height), Title(title) {}
};

// create a buffer of windows
// NOTE: Allocate size
struct s_WindowBuf {
   int count;
   std::vector<GLFWwindow*> buf;
   s_WindowBuf() :
         count(0), buf(){}
};


class TerminalWindow {
   public:
      GLFWwindow* glfwWindow = nullptr;
      s_WindowValues winVal;

      TerminalWindow() = default;

      // initialize glfw window
      GLFWwindow* createTermWindow(s_WindowBuf &winBuf, s_WindowValues &winVal);
      // the main initializer function in main for now
      int termLoop(s_WindowBuf &winBuf, s_WindowValues &winVal);
};

// public incase of need for s_WindowValues
class WindowBuffers : public TerminalWindow {
   public:
      s_WindowBuf winBuf;
      WindowBuffers() = default;

      void createGlfwWindow(s_WindowBuf &winBuf, s_WindowValues& winVal);
};

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
