#ifndef TERRAIN_INCLUDED_HPP
#define TERRAIN_INCLUDED_HPP

#include <random>
#include <iostream>
#include <memory>
#include <glm/glm.hpp>

#include "mesh.hpp"

static const int TERRAIN_SIZE = 128;
static const int TERRAIN_VERTICES_BY_TILE = 6;
static const int TERRAIN_SAMPLE = 128;
static const float TERRAIN_TILE_SIZE = (float)TERRAIN_SIZE/(float)TERRAIN_SAMPLE;

class Terrain
{
public:
  Terrain();  
  void Draw();

  virtual ~Terrain();
protected:
private:  
  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;
  std::unique_ptr<Mesh> m_mesh;
};

#endif
