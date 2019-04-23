#ifndef MODEL_H
#define MODEL_H

#include "pool.h"
#include "humon.h"

namespace overground
{
  class Model
  {
  public:
    Model();

    void loadFromHumon(humon::HuNode const & src);

    void setName(std::string const & name)
      { this->name = name; }
    void setMeshName(std::string const & meshName)
      { this->meshName = meshName; }
    void setMaterialName(std::string const & materialName)
      { this->materialName = materialName; }

    std::string const & getName() const { return name; }
    std::string const & getMeshName() const { return meshName; }
    std::string const & getMaterialName() const { return materialName; }

  private:
    std::string name;
    std::string meshName;
    std::string materialName;
  };


  extern ObjectMap<Model> Models;
}

#endif // #ifndef MODEL_H
