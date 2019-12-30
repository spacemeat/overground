#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "material.h"

namespace overground
{
  class MaterialManager
  {
  public:
    MaterialManager();
    
    Material & getMaterial(std::string_view name);
  };


  inline std::optional<MaterialManager> materialMan;
}


#endif // #ifndef MATERIALMANAGER_H
