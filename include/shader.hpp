#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>

class Shader
{
public:
  Shader(const std::string& filename);
  void Bind();

  virtual ~Shader();

protected:
private:
  static const unsigned int NUM_SHADERS = 2;
  Shader (const Shader& other) {}
  Shader& operator=(const Shader& other) {}
  
  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
};

#endif // SHADER_HPP
