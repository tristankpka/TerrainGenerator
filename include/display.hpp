#ifndef DISPLAY_INCLUDED_HPP
#define DISPLAY_INCLUDED_HPP

#include <string>

#include <GL/glew.h>
#include <SFML/Window.hpp>

class Display {
public:
    Display(int width, int height, const std::string &title);

    void Clear(float r, float g, float b, float a);

    void Show();

    bool PollEvent(sf::Event &event);

    void Close();

    bool IsOpen();

    virtual ~Display();

protected:
private:
    static const unsigned int DEPTH_BITS = 24;
    static const unsigned int STENCIL_BITS = 8;
    static const unsigned int ALIASING_LEVEL = 4;
    static const unsigned int MAJOR_VERSION = 3;
    static const unsigned int MINOR_VERSION = 24;

    Display &operator=(const Display &display) = default;

    Display(const Display &display) = default;

    sf::Window m_window;
};

#endif
