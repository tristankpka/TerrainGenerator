#ifndef TERRAIN_INCLUDED_HPP
#define TERRAIN_INCLUDED_HPP

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include <random>
#include <iostream>
#include <memory>
#include <string>

#include "mesh.hpp"

class Terrain
{
public:
Terrain(const std::string& heightMapFilename);  
  void Draw();

  virtual ~Terrain();
protected:
private:  
  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;
  std::unique_ptr<Mesh> m_mesh;
};

#endif
