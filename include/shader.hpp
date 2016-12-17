#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

class Shader
{
public:
  Shader(const std::string& filename);
  void Bind();

  virtual ~Shader();

protected:
private:
  static const unsigned int NUM_SHADERS = 2;
  Shader (const Shader& other) = default;
  Shader& operator=(const Shader& other) = default;
  
  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
};

#endif // SHADER_HPP
