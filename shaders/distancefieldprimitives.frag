#version 410 core

uniform float u_GlobalTime;
uniform vec2 u_Resolution;
in vec2 o_FragCoord;
out vec4 o_FragColor;


/**
 * Signed distance field primitives
 */

// Signed distance field function for cube
vec4 cube(vec3 _position, float _w)
{
  vec3 pos = abs(_position);
  float dx = pos.x - _w;
  float dy = pos.y - _w;
  float dz = pos.z - _w;
  float m = max(dx, max(dy, dz));
  return vec4(m, dx, dy, dz);
}

vec3 normal(vec3 _position)
{
  vec3 epsilon = vec3(0.01f, 0.0f, 0.0f);
  vec3 normal = vec3(
    cube(_position + epsilon.xyy, 0.6f).x - cube(_position - epsilon.xyy, 0.6f).x,
    cube(_position + epsilon.yxy, 0.6f).x - cube(_position - epsilon.yxy, 0.6f).x,
    cube(_position + epsilon.yyx, 0.6f).x - cube(_position - epsilon.yyx, 0.6f).x
  );
  return normalize(normal);
}

// Ray for tracing
mat2x3 createRay(vec3 _origin, vec3 _lookAt, vec3 _upV, vec2 _uv, float _fov, float _aspect)
{
  mat2x3 ray;
  vec3 direction, rayUpV, rightV;
  vec2 uv;
  float fieldOfViewRad;

  ray[0] = _origin;
  direction = normalize(_lookAt - _origin);
  rayUpV = normalize( _upV - direction * dot(direction, _upV));
  rightV = cross(direction, rayUpV);
  uv = _uv * 2 - vec2(1.);
  fieldOfViewRad = _fov * 3.1415 / 180;

  ray[1] = direction + tan(fieldOfViewRad / 2.f) * rightV * uv.x + tan(fieldOfViewRad / 2.f) / _aspect * rayUpV * uv.y;
  ray[1] = normalize(ray[1]);

  return ray;
}

// Rendering function
vec3 render(mat2x3 _ray)
{
  float distance = 0.f;
  vec3 position;
  for(int i = 0; i < 60; ++i)
  {
    position = _ray[0] + distance * _ray[1];
    distance += cube(position, 0.6f).x;
  }

  vec4 m = cube(position, 0.6f);

  if(m.x < 0.01)
  {
    vec3 n = normal(position);
    vec3 l = normalize(vec3(1.f, 2.f, 5.f));
    vec3 diffuse = clamp(dot(n, l), 0.f, 1.f)*vec3(1.);
    vec3 r = reflect(_ray[1], n);
    float dx = m.y;
    float dy = m.z;
    float dz = m.w;
    float start = 0.0f;
    float end = 0.05f;
    float f = smoothstep(start, end, abs(dx-dy));
    f *= smoothstep(start, end, abs(dx-dz));
    f *= smoothstep(start, end, abs(dz-dy));
    f = 1.f - f;
    float rf = 1.f - abs(dot(_ray[1], n));
    rf = pow(rf, 3.f);
    return diffuse * (1.f - rf) * 0.8f;
  }
  return vec3(0.f);
}

void main()
{
  vec3 cameraPosition = vec3(sin(u_GlobalTime/10.f)*5.f, 5.f, cos(u_GlobalTime/10.f)*5.f);
  vec3 lookAt = vec3(0.f);
  vec3 upVector = vec3(0.f, 1.f, 0.f);
  float aspectRatio = u_Resolution.x / u_Resolution.y;

  mat2x3 ray = createRay(cameraPosition, lookAt, upVector, o_FragCoord, 90.f, aspectRatio);
  vec3 color = render(ray);
  o_FragColor = vec4(color, 1.f);
}
