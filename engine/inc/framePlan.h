#ifndef FRAMEPLAN_H
#define FRAMEPLAN_H

#include <vector>
#include <queue>
#include <variant>
#include "utils.h"
#include "jobBoard.h"
#include "framePlan-gen.h"

namespace overground
{
  struct PhaseKindTraits
  {
    FramePhaseKinds kind;
    bool hasBarrier;
    bool hasBarrierJob;
    bool skipBarrierIfEmpty;
    bool skipBarrierJobIfEmpty;
  };

  constexpr
  PhaseKindTraits phaseKindTraits[] = {
    { FramePhaseKinds::frameMaintenance,    true,   true,   false,  false },
    { FramePhaseKinds::graphicsStructure,   true,   true,   false,  true },
    { FramePhaseKinds::acquireImage,        true,   true,   false,  false },
    { FramePhaseKinds::beginComputePass,    true,   true,   true,  false },
    { FramePhaseKinds::endComputePass,      true,   true,   false,  false },
    { FramePhaseKinds::beginRenderPass,     true,   true,   true,  false },
    { FramePhaseKinds::beginSubpass,        true,   true,   true,  false },
    { FramePhaseKinds::endRenderPass,       true,   true,   false,  false },
    { FramePhaseKinds::submitCommands,      true,   true,   false,  false },
    { FramePhaseKinds::present,             true,   true,   false,  false },
    { FramePhaseKinds::nonBarrierJobQueue,  false,  false,  false,  false },
    { FramePhaseKinds::barrierJobQueue,     true,   false,  false,  false },
  };
  

  class FramePhase
  {
  public:
    FramePhase(std::string_view name);

    std::string const & getName() const
      { return name; }
    FramePhaseKinds getKind() const
      { return kind; }
    
    JobBoard const & getJobBoard() const
      { return jobBoard; }

    void update(framePhase_t const & desc);
    void postJob(Job * job, bool recurring);

    bool hasBarrierJob() const
      { return barrierJob != nullptr; }

    template <typename T>
    void forEachJob(T fn);

    Job * getBarrierJob() const
      { return barrierJob; }
    void setBarrierJob(Job * job)
      { barrierJob = job; }

  private:
    std::string name;
    FramePhaseKinds kind;
    JobBoard jobBoard;
    std::optional<std::variant<std::string, int>> phaseArg;
    Job * barrierJob = nullptr;
  };


  template <typename T>
  void FramePhase::forEachJob(T fn)
  {
    jobBoard.forEachJob(fn);
  }


  class FramePlan
  {
  public:
    FramePlan();

    void update(framePlan_t const & desc);
    void postJob(std::string_view phase, Job * job, bool recurring);
    
    std::vector<FramePhase> & getPhases()
      { return phases; }
    
    bool hasBarrierJob(size_t phaseidx) const;

    template <typename T>
    void forEachJob(size_t phaseIdx, T fn);

    template <typename T>
    void forEachPhase(T fn);

  private:
    std::string name;
    std::unordered_map<std::string, size_t, std::hash<std::string>> phaseIdxs;
    std::vector<FramePhase> phases;
  };


  template <typename T>
  void FramePlan::forEachJob(size_t phaseIdx, T fn)
  {
    phases[phaseIdx % phases.size()].forEachJob(fn);
  }  


  template <typename T>
  void FramePlan::forEachPhase(T fn)
  {
    for_each (phases.begin(), phases.end(), fn);
  }  
}

#endif // #ifndef FRAMEPLAN_H
