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
  class FramePhase
  {
  public:
    FramePhase(std::string_view name);

    void update(framePhase_t const & desc);
    void postJob(Job * job, bool recurring);

  private:
    std::string name;
    FramePhaseKinds kind;
    JobBoard jobBoard;
    std::optional<std::variant<std::string, int>> phaseArg;
  };


  class FramePlan
  {
  public:
    FramePlan();

    void update(framePlan_t const & desc);
    void postJob(std::string_view phase, Job * job, bool recurring);

  private:
    std::string name;
    std::unordered_map<std::string, size_t, std::hash<std::string>> phaseIdxs;
    std::vector<FramePhase> phases;
  };
}

#endif // #ifndef FRAMEPLAN_H
