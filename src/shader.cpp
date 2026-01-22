#include "../include/shader.hpp"

namespace Asteroids{

Shader::Shader(const char* vertex_path, const char* fragment_path){
  std::string vertex_code   = read_from_file(vertex_path);
  std::string fragment_code = read_from_file(fragment_path);

  compile(GL_VERTEX_SHADER,   vertex_code.c_str()); 
  compile(GL_FRAGMENT_SHADER, fragment_code.c_str());
  link();

  glDeleteShader(m_vertex); 
  glDeleteShader(m_fragment);
}


const std::string Shader::read_from_file(const char* file_path){
  std::string shader_code;
  std::ifstream shader_file;

  shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    shader_file.open(file_path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();
    shader_code = shader_stream.str();
  } catch(std::ifstream::failure &e){
    std::cout << "Error: Couldn't read shader file" << std::endl;
  }
  
  return shader_code;
}

void Shader::compile(GLenum shader_kind, const char* src_code){
  unsigned int *curr_shader     { nullptr };
  unsigned int src_string_count {    1    };

  if(shader_kind == GL_VERTEX_SHADER)
    curr_shader = &m_vertex; 
  if(shader_kind == GL_FRAGMENT_SHADER)
    curr_shader = &m_fragment;
  
  *curr_shader = glCreateShader(shader_kind);
  glShaderSource(*curr_shader, src_string_count, &src_code, NULL);
  glCompileShader(*curr_shader);
  
  int success { 0 }; 
  char log [512];
  glGetShaderiv(*curr_shader, GL_COMPILE_STATUS, &success); 
  if(!success){
    glGetShaderInfoLog(*curr_shader, 512, NULL, log);
    std::cout << "Couldn't compile shader id: " << *curr_shader << std::endl               << log;
    return;
  }
  std::cout << "Compiled shader id: " << *curr_shader << std::endl;
}

void Shader::link(){
  m_id = glCreateProgram(); 
  glAttachShader(m_id, m_vertex); 
  glAttachShader(m_id, m_fragment);
  glLinkProgram(m_id);

  int success;
  char log [512];
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(m_id, 512, NULL, log);
    std::cout << "Couldn't link program id: " << m_id << std::endl 
              << log;
    return;
  }
  std::cout << "Linked program id: " << m_id << std::endl;
}

void Shader::set_mat4fv(const char* uni_name, const glm::mat4 &matrix) const{
  glUniformMatrix4fv(
    glGetUniformLocation(m_id, uni_name), 
    1, 
    GL_FALSE,
    glm::value_ptr(matrix)
  );
}


} // namespace Asteroids
