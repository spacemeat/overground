#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <stack>
#include <mutex>
#include <chrono>
#include <functional>
#include "config.h"
#include "asset.h"
#include "graphics.h"
#include "fileReference.h"
#include "jobManager.h"
#include "resourceManager.h"

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
    void shutDown();

    void enqueueJob(Job * job);
    void enqueueJobs(std::stack<Job *> & jobs);
    // private

    // process steps
    void resetVulkanInstance();
    void loadScene();
    void latchSceneDelta();
    void enterEventLoop();
    void iterateGameLoop();

    void updateTimer();
    void performScheduledEvents();
    void checkForConfigUpdates();

    // timed events
    void checkForFileUpdates(bool synchronous);
    void checkForAssetUpdates(bool synchronous);

    // external updates (say from file changes)
    void updateConfig(ConfigData const & newConfig);


    // assets
    std::unique_ptr<Asset> makeAsset(
      ResourceManager * resMan,
      std::string const & assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor
    );

    using makeAssetFn_t = std::function<
      std::unique_ptr<Asset>(
        ResourceManager * resMan,
        std::string const & assetName,
        FileReference * assetDescFile, 
        humon::HuNode & descFromFile,
        bool cache, bool compress,
        bool monitor
    )>;

    void registerAssetProvider(
      std::string const & assetKind,
      makeAssetFn_t const & fn);

    std::map<std::string, makeAssetFn_t> assetProviders;
    
    std::string workingDir = "res";
    std::string configFile = "config.hu";

    ResourceManager resMan;

    ConfigData config;
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
