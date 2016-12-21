#ifndef SCENE_INCLUDED_HPP
#define SCENE_INCLUDED_HPP

#include <vector>

class Scene : public sf::Drawable
{
public:
  Scene();
  
  void addObject(Object)
  virtual ~Display();
protected:
private:
  void 
  std::vector<Object> m_objects;
  
  Scene& operator=(const Scene& scene) = default;
  Scene(const Scene& scene) = default;
};

#endif
