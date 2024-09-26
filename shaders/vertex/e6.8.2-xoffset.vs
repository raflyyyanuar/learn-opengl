#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 myColor;

uniform float xOffset;

void main() {
    gl_Position = vec4(pos.x + xOffset, pos.yz, 1.0);
    myColor = col;
}