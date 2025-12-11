#include "terminal.h"

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

void TerminalWindow::Init() {
   fontID = glHandles.CreateShader(glHandles.shaderFile.vertexShader,
         glHandles.shaderFile.fragmentShader);

   fontManager.initFreetype("fonts/TimesNewRomanRegular/TimesNewRomanRegular.ttf");
   fontManager.initCharTextures();
}

void TerminalWindow::OnRender() {
   fontManager.RenderText(fontID, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
   fontManager.RenderText(fontID, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
}

void TerminalWindow::OnUpdate() {

}

int TerminalWindow::mainLoop() {
   GLFWwindow* firstWindow = createTermWindow(winBuf, winVal);
   winBuf.count += 1;

   Init();

   while (!glfwWindowShouldClose(firstWindow)) {

      glfwMakeContextCurrent(firstWindow);
      firstWindow = winBuf.buf.back();

      GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      OnRender();

      glfwPollEvents();

      glfwSwapBuffers(firstWindow);
   }

   glfwTerminate();
   return 0;
}
