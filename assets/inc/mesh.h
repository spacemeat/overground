#ifndef MESH_H
#define MESH_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include<vulkan/vulkan.hpp>

#include <string>
#include <vector>
#include "humon.h"
#include "pool.h"

namespace overground
{
  struct Submesh
  {
    unsigned int indexBits = 16;
    VkPrimitiveTopology topology = 
      VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    std::vector<unsigned int> numIndices;
    unsigned int indicesMemSize = 0;
  };


  class Mesh
  {
  public:
    Mesh();

    void loadFromHumon(humon::HuNode const & src);

    void setName(std::string const & name)
      { this->name = name; }

  private:
    std::string name;
    std::vector<int8_t> binaryData;

    unsigned int numVertices = 0;
    unsigned int positionSize = 0;
    unsigned int normalSize = 0;
    std::vector<unsigned int> texSizes = { 0 };

    std::vector<Submesh> submeshes;

    unsigned int bytesPerVertex = 0;
    unsigned int verticesMemSize = 0;
    unsigned int indicesMemSize = 0;
  };

  extern ObjectMap<Mesh> Meshes;
}

#endif // #ifndef MESH_H

