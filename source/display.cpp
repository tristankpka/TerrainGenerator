#include "display.hpp"
#include <iostream>

Display::Display(int width, int height, const std::string& title):
  m_window(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24, 8, 4, 3, 0))
{
  m_window.setVerticalSyncEnabled(true);

  GLenum res = glewInit();
  if(res != GLEW_OK)
    {
      std::cerr << "Glew failed to initialize!" << std::endl;
    }

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  // WIREFRAME
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

Display::~Display()
{

}

void Display::Clear(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Show()
{
  m_window.display();
}

bool Display::PollEvent(sf::Event& event)
{
  return m_window.pollEvent(event);
}

void Display::Close()
{
  m_window.close();
}

bool Display::IsOpen()
{
  return m_window.isOpen();
}
