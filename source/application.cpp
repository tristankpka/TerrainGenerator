#include "application.hpp"

#include "texture.hpp"
#include "shader.hpp"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Application::Application():
    m_display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator"),
    m_camera(glm::vec3(256.0f/2.0f, 256.0f/2.0f, -8.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 500.0f),
    m_terrain("../resource/terrain_heightmap.png"),
    m_texture("../resource/debug.jpg"),
    m_shader("../resource/basicShader")

{}

void Application::processInputs()
{
    sf::Event event;
    while(m_display.PollEvent(event))
    {

        if(event.type == sf::Event::Closed)
            m_display.Close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			m_camera.MoveForward(0.5f);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			m_camera.MoveBackward(0.5f);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			m_camera.MoveRight(0.5f);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			m_camera.MoveLeft(0.5f);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			m_camera.Pitch(-0.5f);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_camera.Pitch(0.5f);
	   	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			m_camera.RotateZ(-0.8f);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_camera.RotateZ(0.8f);
    }
}

void Application::update(sf::Time elapsedTime)
{
    Transform transform;
    Light light(glm::vec3(256.0f/2.0f, 256.0f/2.0f, 10.0f));

    m_shader.Update(transform, m_camera, light);
}

void Application::render()
{
    m_display.Clear(0, 0, 0, 1.0f);

	//terrain
	m_texture.Bind();
	m_shader.Bind();
	m_terrain.Draw();

	// display
    m_display.Show();
}


void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(m_display.IsOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processInputs();
            update(TIME_PER_FRAME);
        }

        render();
    }
}

