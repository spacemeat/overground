#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <stack>
#include <mutex>
#include <chrono>
#include <functional>
#include "asset.h"
#include "graphics.h"
#include "fileReference.h"
#include "jobManager.h"
#include "resourceManager.h"

#include "configAsset.h"
#include "config-gen.h"
#include "renderPassAsset.h"
#include "renderPass-gen.h"
#include "framePlanAsset.h"
#include "framePlan-gen.h"
#include "framePlan.h"


namespace overground
{
  enum class ScheduledEvents : size_t
  {
    CheckForFileUpdates = 0,
  };

  class JobScheduler;

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

    ResourceManager & getResourceManager() { return resMan; }
    FramePlan & getFramePlan() { return framePlan; }
    Graphics & getGraphics() { return graphics; }

    DataObjectKindFlags & getUpdatedObjectKinds()
      { return updatedObjectKinds; }
    
    config_t const & getConfig()
      { return config; }
    Config::Deltas & getConfigDiffs()
      { return configDiffs; }      

    void registerAssetProvider(
      std::string_view assetKind,
      makeAssetFn_t const & fn);

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

    // On death's door:
    void iterateLoop();

    void runFrameMaintenance();
    void updateTimer();
    void performScheduledEvents(JobScheduler & sched);
    // timed events
    void checkForFileUpdates(JobScheduler & sched);
    void checkForAssetUpdates(JobScheduler & sched);

    void checkForDataUpdates();
    void checkForConfigUpdates();
    void checkForFramePlanUpdates();
    void assignSpecialPhaseJobs(FramePhase & phase);

    // external updates (say from file changes)
    void updateConfig(config_t newConfig);
    void updateFramePlan(framePlan_t newFramePlan);

    // assets
    std::string getBaseAssetDir()
      { return "res"; }
      
    std::unique_ptr<Asset> makeAsset(
      std::string_view assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor
    );
  
  private:
    std::thread * limiter;

    std::string workingDir = "res";
    std::string configFile = "config.hu";

    ResourceManager resMan;

    config_t config;
    Config::Deltas configDiffs;
    std::mutex mx_config;       // TODO: Need?

    framePlan_t framePlanDesc;
    bool framePlanUpdated = true;
    FramePlan framePlan;

    Graphics graphics;

    systemTimePoint systemTime;
    systemTimePoint previousSystemTime;
    systemTimePoint startTime;
    
    engineTimeDuration frameTime_us;
    engineTimePoint currentTime_us;

    std::vector<engineTimeDuration> eventPeriods;
    std::vector<engineTimePoint> lastEventTimes;

    DataObjectKindFlags updatedObjectKinds = 
      DataObjectKindFlags::none;
  };

  extern Engine * engine;
}

#endif // #ifndef ENGINE_H
