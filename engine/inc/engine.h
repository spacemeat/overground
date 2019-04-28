#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "config.h"
#include "graphics.h"

namespace overground
{
  class Engine
  {
  public:
    Engine();
    ~Engine();

    void init(int argc, char ** argv);

    // process steps
    void loadConfig();
    void createGraphics();
    void loadScene();
    void latchSceneDelta();
    void enterEventLoop();
    void iterateGameLoop();

    std::string workingDir = "res";
    std::string configFile = "config.hu";

    Graphics g;

    Config config;
  };
}

#endif // #ifndef ENGINE_H

