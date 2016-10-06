#version 410

uniform float u_globalTime;
out vec4 fragColor;

void main()
{
  fragColor = vec4(vec3(sin(u_globalTime)), 1.0);
}
