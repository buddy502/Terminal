#include "window.h"
#include "history.h"

int main() {
   if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW\n";
      return -1;
   }

   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
   GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

   TerminalWindow termWindow;
   WindowBuffers windowBuffers;

   HistoryChannel historyChannel;

   historyChannel.addHistoryBlock(historyChannel.historyBlock);

   termWindow.termLoop(windowBuffers.winBuf, termWindow.winVal);

   return 0;
}
