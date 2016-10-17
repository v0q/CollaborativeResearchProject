#version 410 core

uniform float u_GlobalTime;
uniform vec2 u_Resolution;
in vec2 o_FragCoord;
out vec4 o_FragColor;


/**
 * Signed distance field primitives
 */

// Signed distance field function for cube
float sphere(vec3 _position, float _w)
{
    return length(_position)-_w;
}

float cube(vec3 _position, float _w)
{
  vec3 pos = abs(_position);
  float dx = pos.x - _w;
  float dy = pos.y - _w;
  float dz = pos.z - _w;
  float m = max(dx, max(dy, dz));
  return m;
}

float sdTorus( vec4 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

float smin(float a, float b, float k)
{
  float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
  return mix( b, a, h ) - k*h*(1.0-h);
}

float p_union(float a, float b)
{
  return min(a, b);
}

float map(vec3 _position)
{
  float pos = 1.f;
  pos = sphere(_position, 0.6f);
  pos = p_union(pos, sdTorus(mat4x4(sin(45), cos(45), 0, 0,
                                  -cos(45), sin(45), 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1)*vec4(_position, 1.0f), vec2(3.5f, 0.5f)));
  pos = p_union(pos, smin(cube(_position + vec3(0.f, 0.f, 0.5f), 0.6f), sphere(_position + vec3(0.f, -0.5f, 0.5f), 0.6f), 0.3f));
  return pos;
//  return sphere(_position, 0.6f);
//  return sdTorus(mat4x4(sin(45), cos(45), 0, 0,
//                        -cos(45), sin(45), 0, 0,
//                        0, 0, 1, 0,
//                        0, 0, 0, 1)*vec4(_position, 1.0f), vec2(3.5f, 0.5f));
//  return smin(cube(_position + vec3(0.f, 0.f, 0.5f), 0.6f), sphere(_position + vec3(0.f, -0.5f, -0.5f), 0.6f), 0.3f);
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
  float distance = 1.f;
  float traceprecision = 0.01f;
  float position;
  int  i;
  for(i = 0; i < 60; ++i)
  {
    position = map(_ray[0] + distance * _ray[1]);
    if(position <= traceprecision) {
      break;
    }
    distance += position;
  }

  if(position <= traceprecision)
  {
    vec3 diffuse = vec3(0.8f, 0.6f, 0.f);
    return vec3(i/60.f, 1 - i/60.f, 0.f);
  }
  return vec3(1.f);
}

void main()
{
  vec3 cameraPosition = vec3(sin(u_GlobalTime/10.f)*5.f, 2.5f, cos(u_GlobalTime/10.f)*5.f);
  vec3 lookAt = vec3(0.f);
  vec3 upVector = vec3(0.f, 1.f, 0.f);
  float aspectRatio = u_Resolution.x / u_Resolution.y;

  mat2x3 ray = createRay(cameraPosition, lookAt, upVector, o_FragCoord, 90.f, aspectRatio);
  vec3 color = render(ray);
  o_FragColor = vec4(color, 1.f);
}
