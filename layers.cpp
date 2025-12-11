#include "layers.h"

void Layers::OnRender() {
   GLHandles glHandles;
   glHandles.CompileShader(GL_VERTEX_SHADER, glHandles.shaderFile.vertexShader);
   glHandles.CompileShader(GL_FRAGMENT_SHADER, glHandles.shaderFile.fragmentShader);

   glHandles.CreateShader(glHandles.shaderFile.vertexShader, glHandles.shaderFile.fragmentShader);
}

void Layers::OnEvent() {

}

void Layers::OnUpdate() {

}
