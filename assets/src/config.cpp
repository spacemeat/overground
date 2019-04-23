#include "config.h"

using namespace std;
using namespace humon;
using namespace overground;


Config::Config()
{
}


void Config::loadFromHumon(HuNode const & src)
{
  auto & configSrc = src.asDict();

  if (configSrc.hasKey("general"))
  {
    auto & generalSrc = configSrc.at<HuDict>("general");
    if (generalSrc.hasKey("numWorkerThreads"))
    {
      general.numWorkerThreads = generalSrc.at<HuValue>("numWorkerThreads").getLong();
    }
  }

  if (configSrc.hasKey("graphics"))
  {
    auto & graphicsSrc = configSrc.at<HuDict>("graphics");
    if (graphicsSrc.hasKey("windowedMode"))
    {
      graphics.windowedMode = graphicsSrc.at<HuValue>("windowedMode").getBool();
    }

    if (graphicsSrc.hasKey("width"))
    {
      graphics.width = graphicsSrc.at<HuValue>("width").getLong();
    }

    if (graphicsSrc.hasKey("height"))
    {
      graphics.height = graphicsSrc.at<HuValue>("height").getLong();
    }
    
    if (graphicsSrc.hasKey("extensions"))
    {
      auto & listSrc = graphicsSrc.at<HuList>("extensions");
      for (size_t i = 0; i < listSrc.size(); ++i)
      {
        graphics.extensions.push_back(listSrc.at<HuValue>(0).getString());
      }
    }

    if (graphicsSrc.hasKey("debugging"))
    {
      graphics.debugging = graphicsSrc.at<HuValue>("debugging").getBool();
    }
    
    if (graphicsSrc.hasKey("numGraphicsThreads"))
    {
      graphics.numGraphicsThreads = graphicsSrc.at<HuValue>("numGraphicsThreads").getLong();
    }
  }
}


Config overground::appConfig;
