#version 410

in highp vec4 posAttr;
in lowp vec4 colAttr;
out lowp vec4 col;

uniform highp mat4 matrix;

void main() {
  col = colAttr;
  gl_Position = matrix * posAttr;
}
