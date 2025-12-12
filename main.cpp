#include "terminal.h"
#include "history.h"

int main() {
   if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW\n";
      return -1;
   }

   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4));
   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1));
   GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

   TerminalWindow termWindow;

   HistoryChannel historyChannel;

   // up/down arrow
   //historyChannel.addHistoryBlock(historyChannel.historyBlock);

   termWindow.mainLoop();

   return 0;
}
