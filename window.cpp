#include "window.h"

/* Set up the glfw window */

int TerminalWindow::initTermWindow() {

   if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW\n";
      return -1;
   }


   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
   GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
   GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

   GLCall(glfwWindow = glfwCreateWindow(
         values.Width,
         values.Height,
         values.Title,
         nullptr,
         nullptr));

   if (!glfwWindow) {
      std::cerr << "glfwWindow failed to initialize: LINE: " << __LINE__ <<
         " FILE: " << __FILE__ << std::endl;
      glfwTerminate();
      return -1;
   }

   GLCall(glfwMakeContextCurrent(glfwWindow));

   return 0;
}

int TerminalWindow::init() {
   while (!glfwWindowShouldClose(glfwWindow)) {

      GLCall(glClearColor(0.0f, 0.4f, 0.6f, 1.0f));
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      glfwSwapBuffers(glfwWindow);
      glfwPollEvents();
   }

   glfwTerminate();

   return 0;
}

//int Window::createWindow() {
//   GLFWwindow* window = glfwCreateWindow(winValues.Width, winValues.Height,
//         winValues.Title, nullptr, nullptr);
//
//   if (!window) {
//      std::cerr << "Failed to create window\n";
//      glfwTerminate();
//      return -1;
//   }
//
//   glewExperimental = GL_TRUE;
//   if (glewInit() != GLEW_OK) {
//      std::cerr << "Failed to initialize GLEW: " << __LINE__ << std::endl;
//   }
//
//   glfwMakeContextCurrent(window);
//   return 0;
//}
//
//
//
//int Window::createShaders() {
//   float positions[] = {
//      -1.0f, -1.0f, // 0
//      1.0f, -1.0,   // 1
//      1.0f, 1.0,    // 2
//      -1.0f, 1.0    // 3
//   };
//
//   unsigned int indicies[] = {
//      0, 1, 2,
//      2, 3, 0
//   };
//
//   // VAO
//   unsigned int vao;
//   GLCall(glGenVertexArrays(1, &vao));
//   GLCall(glBindVertexArray(vao));
//
//   // VBO
//   unsigned int vbo;
//   GLCall(glGenBuffers(1, &vbo));
//   GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//   GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));
//
//   // always make sure to enable the vertex attribute array
//   GLCall(glEnableVertexAttribArray(0));
//   GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
//
//   // create the Index Buffer Object
//   unsigned int ibo;
//   GLCall(glGenBuffers(1, &ibo));
//   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//   GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));
//
//   ShaderProgramSource source = ParseShader("res/shaders/opengl.shader");
//   unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
//
//   GLCall(glUseProgram(shader));
//
//   GLCall(int location = glGetUniformLocation(shader, "u_Color"));
//   ASSERT(location != -1);
//   GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
//
//   GLCall(glBindVertexArray(0));
//   GLCall(glUseProgram(0));
//   GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
//   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//
//   return 0;
//}
