#version 410 core

uniform float u_GlobalTime;
uniform vec2 u_Resolution;
in vec2 o_FragCoord;
out vec4 fragColor;

void main()
{
  fragColor = vec4(sin(u_GlobalTime), u_Resolution.xy/1280, 1.0);
}
