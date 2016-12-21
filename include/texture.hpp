#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>

class Texture
{
public:
  Texture(const std::string& fileName);
  
  void Bind();
  
  virtual ~Texture();
protected:
private:
  Texture(const Texture& texture) = default;
  Texture& operator=(const Texture& texture) = default;

  GLuint m_texture;
};

#endif
