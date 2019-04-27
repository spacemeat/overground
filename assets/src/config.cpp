#include "config.h"
#include "utils.h"

using namespace std;
using namespace humon;
using namespace overground;


void Config::loadFromHumon(HuNode const & src)
{
  if (src % "general")
  {
    auto & generalSrc = src / "general";
    if (generalSrc % "numWorkerThreads")
    {
      general.numWorkerThreads = generalSrc / "numWorkerThreads";
    }
  }

  if (src % "graphics")
  {
    auto & graphicsSrc = src / "graphics";
    if (graphicsSrc % "windowedMode")
    {
      graphics.windowedMode = graphicsSrc / "windowedMode";
    }

    if (graphicsSrc % "width")
    {
      graphics.width = graphicsSrc / "width";
    }

    if (graphicsSrc % "height")
    {
      graphics.height = graphicsSrc / "height";
    }
    
    if (graphicsSrc % "extensions")
    {
      auto & listSrc = graphicsSrc / "extensions";
      for (size_t i = 0; i < listSrc.size(); ++i)
      {
        graphics.extensions.push_back(listSrc / i);
      }
    }

    if (graphicsSrc % "debugging")
    {
      graphics.debugging = graphicsSrc / "debugging";
    }
  }
}

template <class T>
Config::Deltas set(T & lhs, T & rhs, Config::Deltas kind)
{
  if (lhs != rhs)
  {
    lhs = rhs;
    return kind;
  }
  return Config::Deltas::None;
}

Config::Deltas Config::integrate(Config & rhs)
{
  Config::Deltas deltas = Config::Deltas::None;

  deltas |= set(general.numWorkerThreads, rhs.general.numWorkerThreads, Config::Deltas::JobManagement);
  deltas |= set(graphics.windowedMode, rhs.graphics.windowedMode, Config::Deltas::Window);
  deltas |= set(graphics.width, rhs.graphics.width, Config::Deltas::Window);
  deltas |= set(graphics.height, rhs.graphics.height, Config::Deltas::Window);
  deltas |= set(graphics.extensions, rhs.graphics.extensions, Config::Deltas::Device);
  deltas |= set(graphics.debugging, rhs.graphics.debugging, Config::Deltas::Device);

  return deltas;
}


void Config::print(std::ostream & sout) const
{
  sout << "Config:" << endl
       << "  general:" << endl
       << "    numWorkerThreads: " << general.numWorkerThreads << endl
       << "  graphics:" << endl
       << "    windowedMode: " << (graphics.windowedMode ? "true" : "false") << endl
       << "    width: " << graphics.width << endl
       << "    height " << graphics.height << endl
       << "    extensions: ";
  for (auto & ext : graphics.extensions)
    { sout << " " << ext; }
  sout << endl 
       << "    debugging: " << (graphics.debugging ? "true" : "false") << endl;
}


std::ostream & overground::operator << (std::ostream & stream, Config const & rhs)
{
  rhs.print(stream);
  return stream;
}
