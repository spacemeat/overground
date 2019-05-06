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
    CheckForFileUpdates = 0,
    CheckForAssetUpdates = 1,
  };

  class Engine
  {
  public:
    using systemTimeDuration = std::chrono::high_resolution_clock::duration;
    using systemTimePoint = std::chrono::high_resolution_clock::time_point;
    
//    std::chrono::time_point<std::chrono::high_resolution_clock, systemTimeDuration>;

    using engineTimerType = double;
    using engineTimeDuration = std::chrono::duration<engineTimerType, std::micro>;
    using engineTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock, engineTimeDuration>;

    Engine();
    ~Engine();

    void init(int argc, char ** argv);

    // private

    // process steps
    void resetVulkanInstance();
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

    Graphics graphics;

    JobManager jobManager;

    systemTimePoint systemTime;
    systemTimePoint previousSystemTime;
    systemTimePoint startTime;
    
    engineTimeDuration frameTime_us;
    engineTimePoint currentTime_us;

    std::vector<engineTimeDuration> eventPeriods;
    std::vector<engineTimePoint> lastEventTimes;
  };
}

#endif // #ifndef ENGINE_H
