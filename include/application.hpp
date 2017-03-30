#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
public:
  Application();
  void                run();

private:
  void                processInputs();
  void                update(sf::Time elapsedTime);
  void                updateStatistics(sf::Time elapsedTime);
  void                render();

private:
  static const int DISPLAY_WIDTH = 1024;
  static const int DISPLAY_HEIGHT = 768;
  static const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

  sf::RenderWindow    m_window;

  sf::Text            m_statisticsText;
  sf::Time            m_statisticsUpdateTime;
  std::size_t	      m_statisticsNumFrames;
};

#endif // APPLICATION_H
