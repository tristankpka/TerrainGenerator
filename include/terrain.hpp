#ifndef TERRAIN_INCLUDED_HPP
#define TERRAIN_INCLUDED_HPP

#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

#include <random>
#include <iostream>
#include <memory>
#include <string>

#include "mesh.hpp"

static const int TERRAIN_SIZE = 256;
static const int TERRAIN_VERTICES_BY_TILE = 6;
static const int TERRAIN_SAMPLE = 256;
static const float TERRAIN_TILE_SIZE = (float)TERRAIN_SIZE/(float)TERRAIN_SAMPLE;
static const float TERRAIN_HEIGHT_SCALING = 0.25f;

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
