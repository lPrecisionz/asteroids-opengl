#include "shader.hpp"

namespace Asteroids{

struct shader_data {
  const char* vertex_path;
  const char* fragment_path;
};

class Renderer{
public:
    Shader m_shader;

public:
  Renderer(shader_data sd) : m_shader(sd.vertex_path, sd.fragment_path){}
};

};
