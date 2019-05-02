#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <mutex>
#include <chrono>
#include "config.h"
#include "graphics.h"
#include "fileRegistry.h"
#include "jobManager.h"

namespace overground
{  
  enum class ScheduledEvents : size_t
  {
    CheckForFileUpdates = 0
  };

  class Engine
  {
  public:
    using timeType = float;
    using timeDuration = std::chrono::duration<timeType, std::milli>;
    using timePoint = std::chrono::time_point<std::chrono::high_resolution_clock, timeDuration>;

    Engine();
    ~Engine();

    void init(int argc, char ** argv);

    // private

    // process steps
    void loadConfig();
    void createGraphics();
    void loadScene();
    void latchSceneDelta();
    void enterEventLoop();
    void iterateGameLoop();

    void updateTimer();
    void performScheduledEvents();

    // timed events
    void checkForFileUpdates(bool synchronous);
    void checkForAssetUpdates(bool synchronous);

    // hot-update assets
    void updateConfig(Config const & newConfig);
    void updateModel(Model const & model);
    void updateMesh(Mesh const & mesh);
    void updateMaterial(Material const & material);
    void updateShader(Shader const & shader);

    std::string workingDir = "res";
    std::string configFile = "config.hu";

    FileRegistry files;

    Config config;
    std::mutex mx_config;

    Graphics g;

    JobManager jobManager;

    timePoint previousTime;
    timePoint currentTime;
    timeDuration frameTime_ms;

    std::vector<timeDuration> eventPeriods;
    std::vector<timePoint> lastEventTimes;
  };
}

#endif // #ifndef ENGINE_H
