#pragma once

#include <fstream>
#include <sstream>

#include <iostream>
#include <string>
#include <vector>

#include "openglHandles.h"
#include "charBuf.h"

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

class WindowBuffers {
   public:
      s_WindowValues winVal;
      s_WindowBuf winBuf;

      WindowBuffers() = default;
      void createGlfwWindow(s_WindowBuf &winBuf, s_WindowValues& winVal);
};

class TerminalWindow {
   private:
      FontManager fontManager;
      GLHandles glHandles;

      s_MemLine *memline;
      MemBlock memblock;
      uint fontID = 0;
   public:
      WindowBuffers windowBuffers;

      GLFWwindow* glfwWindow = nullptr;

      TerminalWindow() = default;

      // initialize glfw window
      GLFWwindow* createTermWindow(s_WindowBuf &winBuf, s_WindowValues &winVal);

      static void character_callback(GLFWwindow* window, unsigned int codepoint);

      void Init();
      void OnRender();  // handle text rendering
      void OnUpdate();  // handle possible window creation

      // the main initializer function in main for now
      int mainLoop();
};

