#ifndef MODEL_H
#define MODEL_H

#include "pool.h"
#include "humon.h"

namespace overground
{
  class FileReference;

  class Model
  {
  public:
    void setFileInfo(FileReference * newFileInfo);
    FileReference * getFileInfo() { return fileInfo; }

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
    FileReference * fileInfo;

    std::string name;
    std::string meshName;
    std::string materialName;
  };
}

#endif // #ifndef MODEL_H
