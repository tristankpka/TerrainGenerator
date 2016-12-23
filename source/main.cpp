#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "display.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"

#include <iostream>
#include <random>

static const int DISPLAY_WIDTH = 1024;
static const int DISPLAY_HEIGHT = 768;
static const int TERRAIN_SIZE = 128;
static const int TERRAIN_SAMPLE = 128;
static const float TERRAIN_TILE_SIZE = (float)TERRAIN_SIZE/(float)TERRAIN_SAMPLE;
static const int TERRAIN_VERTICES_BY_TILE = 6;
int main()
{
  std::random_device rd;
  std::mt19937 rng(rd()); 
  std::uniform_real_distribution<float> uni(0, 0.5f); // guaranteed unbiased
  
  Vertex vertices[TERRAIN_SIZE * TERRAIN_SIZE];
  for(int x = 0; x < TERRAIN_SIZE; x++)
      for(int y = 0; y < TERRAIN_SIZE; y++)
  	  vertices[x * TERRAIN_SIZE + y] = Vertex(glm::vec3(x * TERRAIN_TILE_SIZE, y * TERRAIN_TILE_SIZE, uni(rng)), glm::vec2(0, 0), glm::vec3(0, 0, 0));
 
  unsigned int indices[TERRAIN_SIZE * TERRAIN_SIZE * TERRAIN_VERTICES_BY_TILE];
  int index = 0;
  for(int x = 0; x < TERRAIN_SIZE-1; x++)
    {
      for(int y = 0; y < TERRAIN_SIZE-1; y++)
  	{
  	  int offset = x * TERRAIN_SIZE + y;
  	  indices[index] = (offset + 0);
  	  indices[index + 1] = (offset + 1);
  	  indices[index + 2] = (offset + TERRAIN_SIZE);
  	  indices[index + 3] = (offset + 1);
  	  indices[index + 4] = (offset + TERRAIN_SIZE + 1);
  	  indices[index + 5] = (offset + TERRAIN_SIZE);
	  
  	  index += TERRAIN_VERTICES_BY_TILE;
  	}
    }
  
  for(int i = 0; i < TERRAIN_SIZE * TERRAIN_SIZE * TERRAIN_VERTICES_BY_TILE; i = i+3)
    {
      glm::vec3 v0 = *(vertices[indices[i]].GetPos());
      glm::vec3 v1 = *(vertices[indices[i + 1]].GetPos());
      glm::vec3 v2 = *(vertices[indices[i + 2]].GetPos());
      glm::vec3 u = v1 - v0;
      glm::vec3 v = v2 - v0;
      glm::vec3 n = glm::cross(u, v);
      *(vertices[indices[i]].GetNormal()) = glm::normalize(n + *(vertices[indices[i]].GetNormal()));
      *(vertices[indices[i + 1]].GetNormal()) = glm::normalize(n + *(vertices[indices[i+1]].GetNormal()));
      *(vertices[indices[i + 2]].GetNormal()) = glm::normalize(n + *(vertices[indices[i+2]].GetNormal()));
    }


  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator");
  Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
  Shader shader("../resource/wireframeShader");
  Texture texture("../resource/bricks2.jpg");
  Camera camera(glm::vec3(TERRAIN_SIZE/2.0f, TERRAIN_SIZE/2.0f, -8.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);  
  Transform transform;
  Light light(glm::vec3(TERRAIN_SIZE/2.0f, TERRAIN_SIZE/2.0f, -8.0f));
  bool isRunning = true;
  while(isRunning)
    {
      sf::Event event;
      while(display.PollEvent(event))
	{
	  if(event.type == sf::Event::Closed)
	    isRunning = false;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    camera.MoveForward(0.5f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    camera.MoveBackward(0.5f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	    camera.MoveRight(0.5f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    camera.MoveLeft(0.5f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	    camera.Pitch(-0.5f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	    camera.Pitch(0.5f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	    camera.RotateZ(-0.8f);
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	    camera.RotateZ(0.8f);
	}
      

      display.Clear(0, 0, 0, 1.0f);
      
      shader.Bind();
      texture.Bind();
     
      shader.Update(transform, camera, light);
      
      mesh.Draw();
      
      display.Show();
    }

  return EXIT_SUCCESS;
}
