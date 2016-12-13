#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
  Vertex(const glm::vec3& pos)
  {
    m_pos = pos;
  }
protected:
private:
  glm::vec3 m_pos;
};

class Mesh
{
public:
  Mesh(Vertex* vertices, unsigned int numVertices);
  void Draw();

  virtual ~Mesh();
protected:
private:
  Mesh(const Mesh& other);
  Mesh& operator=(const Mesh& other);
  
  enum
    {
      POSITION_VB,
      
      NUM_BUFFERS
    };

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_drawCount; 
};


#endif //MESH_HPP
