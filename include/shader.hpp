#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "transform.hpp"
#include "camera.hpp"

class Shader
{
public:
  Shader(const std::string& filename);
  void Bind();
  void Update(const Transform& transform, const Camera& camera);

  virtual ~Shader();

protected:
private:
  static const unsigned int NUM_SHADERS = 2;
  static const unsigned int NUM_UNIFORMS = 3;
  Shader (const Shader& other) = default;
  Shader& operator=(const Shader& other) = default;
  
  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_HPP
