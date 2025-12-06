#include "window.h"

int main() {
   TerminalWindow termWindow;
   WindowBuffers windowBuffers;

   termWindow.initTermWindow(windowBuffers.winBuf, termWindow.winVal);

   termWindow.termLoop();

   return 0;
}
