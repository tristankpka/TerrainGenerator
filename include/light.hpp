#ifndef LIGHT_INCLUDED_HPP
#define LIGHT_INCLUDED_HPP

#include <glm/glm.hpp>

class Light
{
public:
  Light(const glm::vec3& pos)
  {
    this->pos = pos;
  }

  inline glm::vec3 GetPos() const { return pos; }
protected:
private:
  glm::vec3 pos;
};

#endif

