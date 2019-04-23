#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace overground
{
  class Shader
  {
  public:
    Shader();

    void setName(std::string const & name)
      { this->name = name; }

  private:
    std::string name;
  };

  extern ObjectMap<Mesh> Meshes;
}

#endif // #ifndef SHADER_H
