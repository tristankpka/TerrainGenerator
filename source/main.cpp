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

#include <random>

static const int DISPLAY_WIDTH = 1024;
static const int DISPLAY_HEIGHT = 768;
static const int TERRAIN_SIZE = 16;
static const float TERRAIN_SCALE = 0.30f;

int main()
{
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator");
  
  Vertex vertices[TERRAIN_SIZE * TERRAIN_SIZE];
  std::random_device rd;
  std::mt19937 rng(rd()); 
  std::uniform_real_distribution<float> uni(0,2); // guaranteed unbiased
  for(int x = 0; x < TERRAIN_SIZE; x++)
    {
      for(int y = 0; y < TERRAIN_SIZE; y++)
	{
	  vertices[x * TERRAIN_SIZE + y] = Vertex(glm::vec3(x * TERRAIN_SCALE, y * TERRAIN_SCALE, uni(rng) * TERRAIN_SCALE), glm::vec2(0, 0), glm::vec3(0, 0, -1));
	}
    }
 
  unsigned int indices[TERRAIN_SIZE * TERRAIN_SIZE * 6];
  int index = 0;
  for(int x = 0; x < TERRAIN_SIZE; x++)
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
	  index += 6;
	}
    }

  Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
  Shader shader("../resource/wireframeShader");
  Texture texture("../resource/bricks2.jpg");
  Transform transform;
  transform.GetRot()->x = 40;
  Camera camera(glm::vec3(2.0f, 2.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);  
  
  float counter = 0.0f;
  bool isRunning = true;
  while(isRunning)
    {
      sf::Event event;
      while(display.PollEvent(event))
	{
	  if(event.type == sf::Event::Closed)
	    isRunning = false;
	}

      display.Clear(0, 0, 0, 1.0f);
      
      shader.Bind();
      texture.Bind();
      
      counter += 0.01f;
      shader.Update(transform, camera);
      
      mesh.Draw();
      
      display.Show();
    }

  return EXIT_SUCCESS;
}
