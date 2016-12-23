#ifndef CAMERA_INCLUDED_HPP
#define CAMERA_INCLUDED_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
  Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
  {
    this->pos = pos;
    this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fov = fov;
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
  }
  
  inline glm::mat4 GetView() const
  {
    return glm::lookAt(pos, pos + forward, up);
  }
  
  inline glm::mat4 GetProjection() const
  {
    return projection; //glm::perspective(fov, aspect, zNear, zFar);
  }
  
  inline glm::mat4 GetViewProjection() const
  {
    return GetProjection() * GetView();
  }

  inline void MoveForward(float amt)
  {
    pos += forward * amt;
  }
  
  inline void MoveBackward(float amt)
  {
    pos -= forward * amt;
  }

  inline void MoveRight(float amt)
  {
    pos += glm::cross(up, forward) * amt;
  }
  
  inline void MoveLeft(float amt)
  {
    pos -= glm::cross(up, forward) * amt;
  }
  
  inline void Pitch(float angle)
  {
    glm::vec3 right = glm::normalize(glm::cross(up, forward));

    forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
    up = glm::normalize(glm::cross(forward, right));
  }

 inline void RotateY(float angle)
  {
    static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

    glm::mat4 rotation = glm::rotate(angle, UP);
    
    forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
    up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
  }

  inline void RotateZ(float angle)
  {
    static const glm::vec3 FRONT(0.0f, 0.0f, 1.0f);
    
    glm::mat4 rotation = glm::rotate(angle, FRONT);
    
    forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
    up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
  }

protected:
private:
  glm::mat4 projection;
  glm::vec3 pos;
  glm::vec3 forward;
  glm::vec3 up;
  float fov;
};

#endif
