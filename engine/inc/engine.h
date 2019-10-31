#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <stack>
#include <mutex>
#include <chrono>
#include <functional>
#include "graphics.h"
#include "fileReference.h"
#include "jobManager.h"
#include "assembly-gen.h"

#include "assetManager.h"
#include "featureManager.h"
#include "objectManager.h"
#include "tableauManager.h"


namespace overground
{
  enum class ScheduledEvents : size_t
  {
    checkForUpdatedFiles = 0,
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

    Graphics & getGraphics() { return graphics; }

    // DataObjectKindFlags & getUpdatedObjectKinds()
    //   { return updatedObjectKinds; }
    
//    Config::Deltas & getConfigDiffs()
//      { return configDiffs; }      

    void init(int argc, char ** argv);
    void shutDown();

//    void enqueueJob(Job * job);
//    void enqueueJobs(std::stack<Job *> & jobs);

    void onAssemblyChanged(
      assembly::assembly_t const & oldAssembly, 
      assembly::assembly_t & newAssembly, 
      assembly::assemblyDiffs_t const & diffs);

    // private: ?

    // process steps
    void resetVulkanInstance();
    //void loadScene();
    //void latchSceneDelta();
    void enterEventLoop();

    void runLoopIteration();

    void runFrameMaintenance();
    void updateTimer();
    void performScheduledEvents(JobScheduler & sched);
    // timed events
    void checkForUpdatedFiles();
    void checkForUpdatedAssembly();

    //void checkForDataUpdates();
    //void checkForConfigUpdates();
    //void checkForFramePlanUpdates();
    //void assignSpecialPhaseJobs(FramePhase & phase);

    // external updates (say from file changes)
    //void updateConfig(config_t newConfig);
    //void updateFramePlan(framePlan_t newFramePlan);

    // assets
    std::string getBaseAssetDir()
      { return "res"; }
      
    // std::unique_ptr<Asset> makeAsset(
    //   std::string_view assetName,
    //   FileReference * assetDescFile, 
    //   humon::HuNode & descFromFile,
    //   bool cache, bool compress,
    //   bool monitor
    // );
  
  private:
    std::thread * limiter;

    std::string workingDir = "res";
    std::string configFile = "config.hu";

    Graphics graphics;

    systemTimePoint systemTime;
    systemTimePoint previousSystemTime;
    systemTimePoint startTime;
    
    engineTimeDuration frameTime_us;
    engineTimePoint currentTime_us;

    std::vector<engineTimeDuration> eventPeriods;
    std::vector<engineTimePoint> lastEventTimes;

//    DataObjectKindFlags updatedObjectKinds = 
//      DataObjectKindFlags::none;
  };

//  extern Engine * engine;
  static inline std::optional<Engine> engine;
}

#endif // #ifndef ENGINE_H
