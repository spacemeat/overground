#include <unordered_set>
#include "framePlan.h"
#include "jobBoard.h"


using namespace std;
using namespace overground;


FramePhase::FramePhase(string_view name)
: name(name), jobBoard(name), phaseArg({""})
{
}


void FramePhase::update(framePhase_t const & desc)
{
  logFn();

  kind = desc.kind;
  switch(kind)
  {
  case FramePhaseKinds::beginComputePass:
    if (desc.computePassName) 
      { phaseArg = * desc.computePassName; }
    break;

  case FramePhaseKinds::beginRenderPass:
    if (desc.renderPassName) 
      { phaseArg = * desc.renderPassName; }
    break;
  
  case FramePhaseKinds::beginSubpass:
    if (desc.subpass)
      { phaseArg = * desc.subpass; }
    break;

  case FramePhaseKinds::maintenance:
  case FramePhaseKinds::top:
  case FramePhaseKinds::endComputePass:
  case FramePhaseKinds::endRenderPass:
  case FramePhaseKinds::submitCommands:
  case FramePhaseKinds::present:
  case FramePhaseKinds::jobQueue:
  default:
    break;
  }
}


void FramePhase::postJob(Job * job, bool recurring)
{
  jobBoard.postJob(job, recurring);
}


// --- FramePlan

FramePlan::FramePlan()
{
  phases.emplace_back("maintenance");
  phaseIdxs.insert({"maintenance", 0});
}


void FramePlan::update(framePlan_t const & desc)
{
  logFn();

  vector<bool> visiteds(phases.size());

  std::unordered_map<std::string, size_t> newPhaseIdxs;
  std::vector<FramePhase> newPhases;

  name = desc.name;
  for (auto & phaseDesc : desc.phases)
  {
    if (auto it = phaseIdxs.find(phaseDesc.name);
        it != phaseIdxs.end())
    {
      auto & phase = phases[it->second];
      phase.update(phaseDesc);
      newPhases.emplace_back(move(phase));
      newPhaseIdxs.insert({phaseDesc.name, newPhases.size() - 1});
    }
    else
    {
      auto & phase = newPhases.emplace_back(phaseDesc.name);
      phase.update(phaseDesc);
      newPhaseIdxs.insert({phaseDesc.name, newPhases.size() - 1});
    }
  }

  phaseIdxs = move(newPhaseIdxs);
  phases = move(newPhases);
}


void FramePlan::postJob(string_view phase, Job * job, bool recurring)
{
  // TODO: In C++20, remove the (string) temp
  if (auto it = phaseIdxs.find((string) phase); 
      it != phaseIdxs.end())
  {
    auto & phase = phases[it->second];
    phase.postJob(job, recurring);
  }
}
