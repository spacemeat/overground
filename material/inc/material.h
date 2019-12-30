#ifndef MATERIAL_H
#define MATERIAL_H

#include <optional>
#include <unordered_map>
#include "graphicsUtils.h"
#include "material-gen.h"

namespace overground
{
  struct MaterialResource   // Something like a descriptor.
  {
    vk::DescriptorType descType;
    std::optional<std::string> assetName;
  };


  class Material
  {
  public:
    Material(material::material_t const & data);

    std::unordered_map<std::string, MaterialResource> const & getRequiredResources() const { return descriptors; }

    std::optional<MaterialResource> const & getDescriptor(std::string_view name) const;

  private:
    std::unordered_map<std::string, MaterialResource> descriptors;
  };


  std::optional<MaterialResource> const & Material::getDescriptor(std::string_view name)
  {
    if (auto it = descriptors.find(string(name));
        it != descriptors.end())
      { return it->second; }
    else
      { return {}; }
  }
}

#endif // #ifndef MATERIAL_h
