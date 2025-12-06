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

    // Pointer to current window for rendering
    GLFWwindow* currentWindow = firstWindow;

    while (!glfwWindowShouldClose(currentWindow)) {

        // Clear the current context with first color
        glfwMakeContextCurrent(currentWindow);
        GLCall(glClearColor(1.0f, 0.4f, 0.6f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        glfwSwapBuffers(currentWindow);

        // Switch back to the last window
        currentWindow = winBuf.buf.back();

        glfwPollEvents();

        if (glfwGetKey(currentWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
           GLFWwindow* _ = createTermWindow(winBuf, winVal); // don't need return value
           winBuf.count++;
        }
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

// int Window::createWindow() {
//    GLFWwindow* window = glfwCreateWindow(winValues.Width, winValues.Height,
//          winValues.Title, nullptr, nullptr);
//
//    if (!window) {
//       std::cerr << "Failed to create window\n";
//       glfwTerminate();
//       return -1;
//    }
//
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK) {
//       std::cerr << "Failed to initialize GLEW: " << __LINE__ << std::endl;
//    }
//
//    glfwMakeContextCurrent(window);
//    return 0;
// }
//
//
//
// int Window::createShaders() {
//    float positions[] = {
//       -1.0f, -1.0f, // 0
//       1.0f, -1.0,   // 1
//       1.0f, 1.0,    // 2
//       -1.0f, 1.0    // 3
//    };
//
//    unsigned int indicies[] = {
//       0, 1, 2,
//       2, 3, 0
//    };
//
//    // VAO
//    unsigned int vao;
//    GLCall(glGenVertexArrays(1, &vao));
//    GLCall(glBindVertexArray(vao));
//
//    // VBO
//    unsigned int vbo;
//    GLCall(glGenBuffers(1, &vbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions,
//    GL_STATIC_DRAW));
//
//    // always make sure to enable the vertex attribute array
//    GLCall(glEnableVertexAttribArray(0));
//    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,
//    0));
//
//    // create the Index Buffer Object
//    unsigned int ibo;
//    GLCall(glGenBuffers(1, &ibo));
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int),
//    indicies, GL_STATIC_DRAW));
//
//    ShaderProgramSource source = ParseShader("res/shaders/opengl.shader");
//    unsigned int shader = CreateShader(source.VertexSource,
//    source.FragmentSource);
//
//    GLCall(glUseProgram(shader));
//
//    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
//    ASSERT(location != -1);
//    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
//
//    GLCall(glBindVertexArray(0));
//    GLCall(glUseProgram(0));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//
//    return 0;
// }
