#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <array>
#include <vector>
#include <stack>
#include <mutex>
#include <chrono>
#include <functional>
#include "graphics.h"
#include "fileReference.h"
#include "jobManager.h"
#include "assembly-gen.h"
#include "objectTree.h"
#include "assetManager.h"


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
    void performScheduledEvents();
    // timed events
    void checkForUpdatedFiles();

    void checkForChanges();
  private:
    void buildWorkingAssemblyObjects();
    void computeConfigDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs);
    void computeMemoryPlanDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs);
    void computeRenderPlanDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs);
    void computeAssetDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs);
    void computeMaterialDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs);
    void computeTableauDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs);
    void handleConfigChanges();
    void blessWorkingSets();

  public:
    void checkForUpdatedAssembly();

    //void checkForDataUpdates();
;
    //void assignSpecialPhaseJobs(FramePhase & phase);

    // external updates (say from file changes)
    void updateConfig(
      config::config_t & config, 
      config::configDiffs_t & configDiffs);

    void setProgramName(std::string_view name);

    void setProgramVersion(version_t version);

    
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

    std::unordered_map<std::string, ObjectTree> tableauGroups;

    systemTimePoint systemTime;
    systemTimePoint previousSystemTime;
    systemTimePoint startTime;
    
    engineTimeDuration frameTime_us;
    engineTimePoint currentTime_us;

    std::vector<engineTimeDuration> eventPeriods;
    std::vector<engineTimePoint> lastEventTimes;

    bool assemblyFilesChanged = false;
    bool assetFilesChanged = false;
    bool assemblyDescsChanged = false;
    bool configChanged = false;
    bool materialsChanged = false;
    bool adbChanged = false;
    bool memoryPlanChanged = false;
    bool objectTreeChanged = false;


//    DataObjectKindFlags updatedObjectKinds = 
//      DataObjectKindFlags::none;
  };

  inline std::optional<Engine> engine;
}

#endif // #ifndef ENGINE_H
