#version 410 core

in vec2 a_Position;
in vec2 a_FragCoord;
out vec2 o_FragCoord;

void main() {
  o_FragCoord = a_FragCoord;
  gl_Position = vec4(a_Position, 0.0, 1.0);
}
