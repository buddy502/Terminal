#include "terminal.h"
#include "openglHandles.h"

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

   // needed to compile shaders
   GLenum err;
   glewExperimental = GL_TRUE;
   if ((err = glewInit()) != GLEW_OK) {
      std::cout << glewGetErrorString(err) << std::endl;
      glfwTerminate();
   }
}


void TerminalWindow::key_callback(GLFWwindow* window,
      int key, int scancode, int action, int mods) {

   TerminalWindow* tw =
      static_cast<TerminalWindow*>(glfwGetWindowUserPointer(window));

   if (key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER) {
      tw->memblock.updateBufferLine(tw->memline);
   }
}

void TerminalWindow::character_callback(GLFWwindow* window, unsigned int codepoint) {
   TerminalWindow* tw =
      static_cast<TerminalWindow*>(glfwGetWindowUserPointer(window));

   if (!tw || !tw->memline) return;

   tw->memblock.insertChar(tw->memline, (char)codepoint);
   std::cout << tw->memline << std::endl;
}

void TerminalWindow::OnRender() {
   fontManager.RenderText(fontID, memline->strbuf, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
}

void TerminalWindow::OnUpdate() {
   // insert character for every keypress
   glfwSetCharCallback(glfwWindow, character_callback);
   glfwSetKeyCallback(glfwWindow, key_callback);
}

void TerminalWindow::Init() {
   s_ShaderFile source = ParseShaderFile("res/fontRender.shader");
   fontID = glHandles.CreateShader(source.vertexShader, source.fragmentShader);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glDisable(GL_CULL_FACE);

   glm::mat4 projection = glm::ortho(0.0f, (float)windowBuffers.winVal.Width, 0.0f, (float)windowBuffers.winVal.Height);

   glUseProgram(fontID);
   glUniformMatrix4fv(glGetUniformLocation(fontID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

   fontManager.initFreetype("fonts/TimesNewRomanRegular/TimesNewRomanRegular.ttf");
   fontManager.initCharTextures();

   fontManager.ShaderBuffers();

   memline = new s_MemLine();
   memline->strbuf.reserve(MAX_STR_BUFFER);

   memline->cursor = new s_Cursor();
   memline->cursor->pos = 0;
}

int TerminalWindow::mainLoop() {
   glfwWindow = createTermWindow(windowBuffers.winBuf,
         windowBuffers.winVal);

   windowBuffers.winBuf.count += 1;

   glfwSetWindowUserPointer(glfwWindow, this);
   Init();

   while (!glfwWindowShouldClose(glfwWindow)) {

      glfwWindow = windowBuffers.winBuf.buf.back();

      GLCall(glClearColor(0.2f, 0.5f, 0.6f, 1.0f));
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      OnRender();

      glfwPollEvents();

      OnUpdate();

      glfwSwapBuffers(glfwWindow);
   }

   glfwTerminate();
   return 0;
}

TerminalWindow::~TerminalWindow() {
   if (memline) delete memline;
   if (memline->cursor) delete memline->cursor;
}
