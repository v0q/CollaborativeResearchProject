#version 410 core

in vec2 a_Position;
in vec2 a_fragCoord;
out vec2 o_fragCoord;

void main() {
  o_fragCoord = a_fragCoord;
  gl_Position = vec4(a_Position, 0.0, 1.0);
}
