#include "window.h"

/* Set up the glfw window */

// create and set glfwWindow and make it current context
GLFWwindow* TerminalWindow::createTermWindow(s_WindowBuf &winBuf, s_WindowValues &winVal) {
   WindowBuffers windowBuffers;

   windowBuffers.createGlfwWindow(winBuf, winVal);

   // update glfwwindow to the one we just created
   this->glfwWindow = winBuf.buf.back();

   GLCall(glfwMakeContextCurrent(glfwWindow));

   return glfwWindow;
}

int TerminalWindow::termLoop(s_WindowBuf &winBuf, s_WindowValues &winVal) {
    GLFWwindow* firstWindow = createTermWindow(winBuf, winVal);
    winBuf.count += 1;

    while (!glfwWindowShouldClose(firstWindow)) {

        // Clear the current context with first color
        glfwMakeContextCurrent(firstWindow);
        GLCall(glClearColor(1.0f, 0.4f, 0.6f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        glfwSwapBuffers(firstWindow);

        // Switch back to the last window
        firstWindow = winBuf.buf.back();

        glfwPollEvents();

       // if (glfwGetKey(firstWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
       //    GLFWwindow* _ = createTermWindow(winBuf, winVal);
       //    winBuf.count++;
       // }
    }

    glfwTerminate();
    return 0;
}

// create another gtk window and update window buffer
void WindowBuffers::createGlfwWindow(s_WindowBuf &winBuf,
      s_WindowValues &winVal) {

   GLFWwindow *window = glfwCreateWindow(winVal.Width, winVal.Height,
         winVal.Title, nullptr, nullptr);

   if (!window) {
      std::cerr << "glfwWindow failed to initialize: LINE: " << __LINE__
         << " FILE: " << __FILE__ << std::endl;
      glfwTerminate();
   }

   winBuf.buf.push_back(window);

   glfwMakeContextCurrent(window);
}
