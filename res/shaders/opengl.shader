#shader fragment
#version 330 core

location(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
   u_Color = color;
};
