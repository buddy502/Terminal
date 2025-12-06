#pragma once

#include "openglHandles.h"

#include <fstream>
#include <sstream>

#include <iostream>
#include <string>
#include <vector>

#define MAX_WIN_BUF 10

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
   int capacity;
   int count;
   std::vector<GLFWwindow*> buf;
   s_WindowBuf() :
         capacity(MAX_WIN_BUF),
         count(0),
         buf(std::vector<GLFWwindow*>(MAX_WIN_BUF)){}
};


class TerminalWindow {
   public:
      GLFWwindow* glfwWindow = nullptr;
      s_WindowValues winVal;

      TerminalWindow() {}

      // initialize glfw window
      int initTermWindow(s_WindowBuf &winBuf, s_WindowValues &winVal);
      // the main initializer function in main for now
      int termLoop();
};

// public incase of need for s_WindowValues
class WindowBuffers : public TerminalWindow {
   public:
      s_WindowBuf winBuf;
      WindowBuffers() : winBuf() {}

      void createGlfwWindow(s_WindowBuf &winBuf, s_WindowValues& winVal);
};

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
