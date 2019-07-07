#include "model.h"
#include "config.h"
#include "fileRegistry.h"

using namespace std;
using namespace humon;
using namespace overground;


void Model::setFileInfo(FileReference * newFileInfo)
{ 
  fileInfo = newFileInfo;
  fileInfo->addRef();
}


void Model::loadFromHumon(HuNode const & src)
{
  auto & configSrc = src.asDict();

  if (src % "meshName")
  {
    auto & val = src / "meshName";
    meshName = string(val);
  }

  if (src % "materialName")
  {
    auto & val = configSrc / "materialName";
    materialName = string(val);
  }
}

