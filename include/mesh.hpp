#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include "obj_loader.hpp"

class Vertex
{
public:
  Vertex()
  {
    this->pos = glm::vec3(0, 0, 0);
    this->texCoord = glm::vec2(0, 0);
    this->normal = glm::vec3(0, 0, 0);	

  }
  Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
  {
    this->pos = pos;
    this->texCoord = texCoord;
    this->normal = normal;	
  }
  // return by ptrs not mandatory
  inline glm::vec3 GetPos() const { return pos; }
  inline glm::vec2 GetTexCoord() const { return texCoord; }
  inline glm::vec3 GetNormal() const { return normal; }
  inline void SetNormal(const glm::vec3& n) { normal = n; }
  inline void SetTexCoord(const glm::vec2& tc) { texCoord = tc; }
protected:
private:
  glm::vec3 pos;
  glm::vec2 texCoord;
  glm::vec3 normal;
};

class Mesh
{
public:
  Mesh(std::vector<Vertex> vertices, unsigned int numVertices, std::vector<unsigned int> indices, unsigned numIndices);
  void Draw();

  virtual ~Mesh();
protected:
private:
  Mesh(const Mesh& other) = default;
  Mesh& operator=(const Mesh& other) = default;
  
  enum
    {
      POSITION_VB,
      TEXCOORD_VB,
      NORMAL_VB,
      INDEX_VB,
      NUM_BUFFERS
    };

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_drawCount; 
};


#endif //MESH_HPP
