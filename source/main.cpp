#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "display.hpp"
#include "shader.hpp"
#include "mesh.hpp"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main()
{
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator");
  
  Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
  			Vertex(glm::vec3(0, 0.5, 0)),
  			Vertex(glm::vec3(0.5, -0.5, 0)), };

  Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
  Shader shader("../resource/basicShader");  
  
  bool isRunning = true;
  while(isRunning)
    {
      sf::Event event;
      while(display.PollEvent(event))
	{
	  if(event.type == sf::Event::Closed)
	    isRunning = false;
	}
      
      display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
      
      shader.Bind();
      mesh.Draw();
      
      display.Show();
    }

  return EXIT_SUCCESS;
}
