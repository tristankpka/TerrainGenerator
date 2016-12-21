#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "display.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main()
{
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator");
  
  Vertex vertices[] =
    {
      Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
      Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
      Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
      Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

      Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
      Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
      Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
      Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

      Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
      Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
      Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
      Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

      Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
      Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
      Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
      Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

      Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
      Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
      Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
      Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

      Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
      Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
      Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
      Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
    };

  unsigned int indices[] = {0, 1, 2,
			    0, 2, 3,

			    6, 5, 4,
			    7, 6, 4,

			    10, 9, 8,
			    11, 10, 8,

			    12, 13, 14,
			    12, 14, 15,

			    16, 17, 18,
			    16, 18, 19,

			    22, 21, 20,
			    23, 22, 20
  };


  Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
  Shader shader("../resource/wireframeShader");
  Texture texture("../resource/bricks2.jpg");
  Transform transform;
  Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);  
  
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

      
      display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
      
      shader.Bind();
      texture.Bind();
      
      transform.GetRot()->x = counter * 80;
      transform.GetRot()->y = counter * 100;
      transform.GetRot()->z = counter * 110;
      
      counter += 0.01f;
      shader.Update(transform, camera);
      
      mesh.Draw();
      
      display.Show();
    }

  return EXIT_SUCCESS;
}
