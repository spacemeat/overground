#include "graphics.h"
#include "configAsset.h"
#include "engine.h"
#include "framePlan.h"
#include <iostream>

using namespace std;
using namespace overground;


Graphics::Graphics()
{

}


Graphics::~Graphics()
{
  destroyWindow();
}


void Graphics::reset()
{
  logFn();

  checkForDataUpdates();
}


void Graphics::checkForDataUpdates()
{
  logFn();

  auto & updatedObjectKinds = engine->getUpdatedObjectKinds();

  if (updatedObjectKinds == DataObjectKindFlags::none)
    { return; }

  if ((updatedObjectKinds & 
      DataObjectKindFlags::config) != 0)
    { checkForConfigUpdates(); }

  if ((updatedObjectKinds &
      DataObjectKindFlags::renderPass) != 0)
    { checkForRenderPassUpdates(); }
}


void Graphics::checkForConfigUpdates()
{
  logFn();

  auto & diffs = engine->getConfigDiffs();
  
  if (mainWindow == nullptr || 
    (diffs & 
      (Config::Deltas::Window | 
      Config::Deltas::WindowExtents)) != 0)
  {
    if (mainWindow == nullptr)
      { createWindow(); }
    else
      { updateWindow(); }
  }
    
  if ((bool) vulkanInstance == false ||
    (diffs & Config::Deltas::VulkanInstance) != 0)
    { resetVulkanInstance(); }

  if ((bool) surface == false)
    { resetSurface(); }

  if ((bool) physicalDevice == false ||
    (diffs & Config::Deltas::PhysicalDevice) != 0)
    { resetPhysicalDevice(); }

  if ((bool) vulkanDevice == false ||
    (diffs & Config::Deltas::LogicalDevice) != 0)
    { resetLogicalDevice(); }

  if ((bool) swapchain == false ||
    (diffs & Config::Deltas::Swapchain) != 0)
    { resetSwapchain(); }
}


void Graphics::checkForRenderPassUpdates()
{
  logFn();
  
  for (auto & [_, rpt] : renderPassThings)
  {
    for (auto & st : swapchainThings)
    {
      if (st.renderPasses.size() <= rpt.idx)
        { st.renderPasses.resize(
          rpt.idx + 1, nullptr); }
    }

    resetRenderPass(rpt);

    for (auto & st : swapchainThings)
    {
      if (st.framebuffers.size() <= rpt.idx)
        { st.framebuffers.resize(
          rpt.idx + 1, nullptr); }
    }

    resetFramebuffer(rpt);

    rpt.updated = false;
  }
}


void Graphics::checkForCommandListUpdates() //?
{
  logFn();

}


void Graphics::assignSpecialPhaseJobs(FramePhase & phase)
{
  switch(phase.getKind())
  {
  case FramePhaseKinds::graphicsStructure:
    phase.setBarrierJob(makeFnJob("graphicsStructurePhase", [this]
      { log(thId, logTags::phase, fmt::format("{}GSP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::acquireImage:
    phase.setBarrierJob(makeFnJob("acquireImagePhase", [this]
      { log(thId, logTags::phase, fmt::format("{}AIP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::beginComputePass:
    phase.setBarrierJob(makeFnJob("beginComputePassPhase", [this]
      { log(thId, logTags::phase, fmt::format("{}BCPP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::endComputePass:
    phase.setBarrierJob(makeFnJob("endComputePhase", [this]
      { log(thId, logTags::phase, fmt::format("{}ECP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::beginRenderPass:
    phase.setBarrierJob(makeFnJob("beginRenderPassPhase", [this]
      { log(thId, logTags::phase, fmt::format("{}BRPP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::beginSubpass:
    phase.setBarrierJob(makeFnJob("beginSubpassPhase", [this]
      { log(thId, logTags::phase, fmt::format("{}BSP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::endRenderPass:
    phase.setBarrierJob(makeFnJob("endRenderPassPhase", [this]
      { log(thId, logTags::phase, fmt::format("{}ERPP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::submitCommands:
    phase.setBarrierJob(makeFnJob("submitCommandsPhase", [this]
      { log(thId, logTags::phase, fmt::format("{}SCP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::present:
    phase.setBarrierJob(makeFnJob("presentPhase", [this]
      { log(thId, logTags::phase, fmt::format("{}PP{}", ansi::lightRed, ansi::off)); }));
    break;
  case FramePhaseKinds::barrierJobQueue:
  case FramePhaseKinds::nonBarrierJobQueue:
  default:
    break;
  }
}


void Graphics::shutDown()
{
  logFn();
  destroyVulkanInstance();
}


void Graphics::presentFrame()
{
  // present frame n-1
}


void Graphics::drawFrame()
{
  if (manageInvalidDevice() == false)
    { return; }

  // draw calls frame n
}


void Graphics::waitForGraphicsOps()
{
  vulkanDevice.waitIdle();
}


bool Graphics::manageInvalidDevice()
{
  if (isLogicalDeviceLost)
  {
//    destroySwapchain();
//    destroyLogicalDevice();
//    createDevice();
  }

  if (isLogicalDeviceLost || isSwapchainStale)
  {
//    createSwapchain();
    if (isLogicalDeviceLost)
    {
//      loadScene(); ??
    }
  }

  isLogicalDeviceLost = false;
  isSwapchainStale = false;

  return true;
}
