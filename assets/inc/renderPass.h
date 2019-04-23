#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <string>

namespace overground
{
  class RenderPass
  {
  public:
    RenderPass();

    void setName(std::string const & name)
      { this->name = name; }

  private:
    std::string name;
  };

  extern ObjectMap<Mesh> Meshes;
}

#endif // #ifndef RENDERPASS_H
