static const char *v = 
  "#version 410 core\n"
  "layout(location = 0) in vec2 p;\n"
  "uniform float ar;\n"
  "uniform float x_pos;\n"
  "uniform float y_pos;\n"
  "uniform float height;\n"
  "out vec2 pos;\n"
  "void main()\n"
  "{\n"
  "  pos = vec2(p.x / ar * height + x_pos, p.y * height + y_pos);\n"
  "  gl_Position = vec4(p, 0.0f, 1.0f);\n"
  "}\n";

static const char *g =
  "";

static const char *f = 
  "#version 410 core\n"
  "in vec2 pos;\n"
  "uniform int bound;\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "  color = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
  "  vec2 C = pos;\n" 
  "  vec2 Z = pos;\n"
  "  for (int i = 1; i <= bound; i++) {\n"
  "    if (dot(Z, Z) > 4) {\n"
  "      float m = 3.0f*float(i)/float(bound);\n"
  "      color = vec4(m, m-1.0f, m-2.0f, 1.0f);\n"
  "      break;\n"
  "    }\n"
  "    Z = vec2(Z.x*Z.x-Z.y*Z.y+C.x, 2*Z.x*Z.y+C.y);\n"
  //"    Z = vec2(pow(Z.x, 3.0f)-3.0f*Z.x*Z.y*Z.y+C.x, 3.0f*Z.x*Z.x*Z.y-pow(Z.y, 3.0f)+C.y);\n"
  //"    Z = vec2(Z.x*Z.x-Z.y*Z.y+Z.x, 2*Z.x*Z.y+Z.y);\n"
  "  }\n"
  "}\n";

static const char *shaders[3];

const char **get_shaders()
{
  shaders[0] = v;
  shaders[1] = g;
  shaders[2] = f;
  return shaders;
}
