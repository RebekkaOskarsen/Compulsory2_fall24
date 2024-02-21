#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 camMatrix;

void main() {
    gl_Position = camMatrix * vec4(position.x, position.y, 0.0, 1.0);
}
