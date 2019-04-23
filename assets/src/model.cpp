#include "model.h"
#include "config.h"

using namespace std;
using namespace humon;
using namespace overground;


Model::Model()
{
}


void Model::loadFromHumon(HuNode const & src)
{
  auto & configSrc = src.asDict();

  if (configSrc.hasKey("meshName"))
  {
    auto & val = configSrc.at<HuValue>("meshName");
    meshName = val.getString();
  }

  if (configSrc.hasKey("materialName"))
  {
    auto & val = configSrc.at<HuValue>("materialName");
    materialName = val.getString();
  }
}


ObjectMap<Model> overground::Models;

