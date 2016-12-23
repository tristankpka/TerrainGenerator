#include "shader.hpp"

#include <iostream>
#include <fstream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
  m_program = glCreateProgram();
  m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

  for(unsigned int i = 0; i < NUM_SHADERS; i++)
    glAttachShader(m_program, m_shaders[i]);
  
  glBindAttribLocation(m_program, 0, "vertexPosition_modelspace");
  //texture attrib location
  glBindAttribLocation(m_program, 2, "vertexNormal_modelspace");
  
  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");
  
  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

  m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
  m_uniforms[1] = glGetUniformLocation(m_program, "V");
  m_uniforms[2] = glGetUniformLocation(m_program, "M");
  m_uniforms[3] = glGetUniformLocation(m_program, "LightPosition_worldspace");
}

Shader::~Shader()
{
  for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
      glDetachShader(m_program, m_shaders[i]);
      glDeleteShader(m_shaders[i]);
    }
  glDeleteProgram(m_program);
}

void Shader::Bind()
{
  glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera, const Light& light)
{
  glm::mat4 MVP = transform.GetMVP(camera);
  glm::mat4 M  = transform.GetModel();
  glm::mat4 V  = camera.GetView();
  glm::vec3 lightPos = light.GetPos();
  glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &V[0][0]);
  glUniformMatrix4fv(m_uniforms[2], 1, GL_FALSE, &M[0][0]);
  glUniform3f(m_uniforms[3], lightPos.x, lightPos.y, lightPos.z);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);

  if(shader == 0)
    std::cerr << "Error: Shader creation failed!" << std::endl;
  
  const GLchar* shaderSourceStrings[1];
  GLint shaderSourceStringLengths[1];

  shaderSourceStrings[0] = text.c_str();
  shaderSourceStringLengths[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);

  CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");
  

  return shader;
}

static std::string LoadShader(const std::string& fileName)
{
  std::ifstream file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if(file.is_open())
    {
      while(file.good())
        {
	  getline(file, line);
	  output.append(line + "\n");
        }
    }
  else
    {
      std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

  return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if(isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if(success == GL_FALSE)
    {
      if(isProgram)
	glGetProgramInfoLog(shader, sizeof(error), NULL, error);
      else
	glGetShaderInfoLog(shader, sizeof(error), NULL, error);

      std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
