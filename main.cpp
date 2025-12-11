#include "terminal.h"
#include "history.h"
#include "charBuf.h"

int main() {
   if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW\n";
      return -1;
   }

   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
   GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

   TerminalWindow termWindow;

   HistoryChannel historyChannel;

   historyChannel.addHistoryBlock(historyChannel.historyBlock);

   termWindow.mainLoop();

   return 0;
}
