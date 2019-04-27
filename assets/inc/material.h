#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "pool.h"


namespace overground
{
  class Material
  {
  public:
    Material() {}

    void setName(std::string const & name)
      { this->name = name; }

  private:
    std::string name;
  };

  extern ObjectMap<Material> Materials;
}

#endif // #ifndef MATERIAL_H
