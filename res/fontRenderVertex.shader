#version 330 core

layout (location = 0) in vec4 vertex; // xy = position, zw = textCoords

in vec2 textCoords;

uniform mat4 projection;

void main() {
   gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
   textCoords = vertex.zw;
}
