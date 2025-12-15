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

      WindowBuffers windowBuffers;

      GLFWwindow* glfwWindow = nullptr;

      s_MemLine *memline = nullptr;
      MemBlock memblock;

      uint fontID{};
   public:

      TerminalWindow() = default;

      ~TerminalWindow();

      // initialize glfw window
      GLFWwindow* createTermWindow(s_WindowBuf &winBuf, s_WindowValues &winVal);

      static void character_callback(GLFWwindow* window, unsigned int codepoint);

      static void key_callback(GLFWwindow* window,
         int key, int scancode, int action, int mods);

      void Init();
      void OnRender();  // handle text rendering
      void OnUpdate();  // handle possible window creation

      // the main initializer function in main for now
      int mainLoop();
};

