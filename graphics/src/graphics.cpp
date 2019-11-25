#include <iostream>

#include "graphics.h"
#include "engine.h"

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


/*
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
*/


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


void Graphics::setNewAllocDesc(AllocDesc newDesc)
{
  static size_t currAdIdx = 0;
  currAdIdx = 1 - currAdIdx;

  currAllocDesc = & allocDescs[currAdIdx];  
  workAllocDesc = & allocDescs[1 - currAdIdx];

  * workAllocDesc = move(newDesc);
}


void Graphics::ensureDeviceAllocSize()
{
  auto neededSize = workAllocDesc->getAllocSize();
  auto hystericalNeededSize = neededSize + neededSize / 4;

  bool stagingAlloc = forceAllocStaging; // TODO: || snoop this

  if (stagingAlloc)
  {
    // if we need to create or inflate the alloc,
    if (neededSize > bufferImageAllocSize)
    {
      // make a new host-visible (and maybe device-visible) alloc at size + 25%, or 0%
      auto newAlloc = createNewAlloc(vk::MemoryPropertyFlagBits::eHostVisible, hystericalNeededSize);
      // use currAllocDesc and bufferImageAlloc_hostOrShared as src, and workAllocDesc and the new alloc as dst, blt all assets that are up to date.
      // These are host-visible to host-visible moves, and will be done with memcpy instead of transfers.
      copyAssetAllocs_h2h(currAllocDesc, bufferImageAlloc_hostOrShared, workAllocDesc, newAlloc);

      // bufferImageAlloc_hostOrShared = new alloc
      bufferImageAlloc_hostOrShared = newAlloc;

      // deallocate bufferImageAlloc_device
      if (bufferImageAlloc_device)
      {
        assetMan->destroyAllBuffersAndImages();
        vulkanDevice.freeMemory(bufferImageAlloc_device);
        bufferImageAlloc_device = nullptr;

        bufferImageAllocSize = hystericalNeededSize;
        // make a new device-visible alloc.
        vk::DeviceMemory newAlloc = createNewAlloc(vk::MemoryPropertyFlagBits::eHostVisible, bufferImageAllocSize);

        // These are host-visible to device-visible moves, and will be done with scheduled transfers.
        copyAssetAllocs_h2d(workAllocDesc, bufferImageAlloc_hostOrShared, workAllocDesc, bufferImageAlloc_device);
      }
    }
    else
    { // not growing the buffer, just potentially moving things about
      // use currAllocDesc and bufferImageAlloc_hostOrShared as src, and workAllocDesc and bufferImageAlloc_hostOrShared as dst, blt all assets that are up to date but need to be moved.
      copyAssetAllocs_h2h(currAllocDesc, bufferImageAlloc_hostOrShared, workAllocDesc, bufferImageAlloc_hostOrShared);

      copyAssetAllocs_d2d(currAllocDesc, bufferImageAlloc_device, workAllocDesc, bufferImageAlloc_device);
    }
  }
  else
  { // AGP, so no staging. Where we put shit is where it go.
    // if we need to create or inflate the alloc,
    if (neededSize > bufferImageAllocSize)
    {
      // make a new host-visible (and maybe device-visible) alloc at size + 25%, or 0%
      auto newAlloc = createNewAlloc(vk::MemoryPropertyFlagBits::eHostVisible, hystericalNeededSize);
      // use currAllocDesc and bufferImageAlloc_hostOrShared as src, and workAllocDesc and the new alloc as dst, blt all assets that are up to date.
      copyAssetAllocs(currAllocDesc, bufferImageAlloc_hostOrShared, workAllocDesc, newAlloc);

      // bufferImageAlloc_hostOrShared = new alloc
      bufferImageAlloc_hostOrShared = newAlloc;
    }
    else
    {
      // use currAllocDesc and bufferImageAlloc_hostOrShared as src, and workAllocDesc and bufferImageAlloc_hostOrShared as dst, blt all assets that are up to date but need to be moved.
      copyAssetAllocs(currAllocDesc, bufferImageAlloc_hostOrShared, workAllocDesc, bufferImageAlloc_hostOrShared);
    }
  }
}

// operates on bufferImageAlloc_hostOrShared, natrually
void Graphics::syncAllocs_s2s(AllocDesc * fr, AllocDesc * to)
{
  auto & frBufferDesc = fr->getBufferDesc();
  auto & toBufferDesc = to->getBufferDesc();

  for (auto & frAde : frBufferDesc.vect())
  {
    Asset * asset = assetMan->getAsset(frAde.assetName);
    asset->setIsInAlloc(false);
    // TODO: if not in to, destroy ro
  }

  for (auto & toAde : toBufferDesc.vect())
  {
    Asset * asset = assetMan->getAsset(toAde.assetName);

    // If the asset is in the old alloc too,
    if (frBufferDesc.hasKey(toAde.assetName))
    {
      auto & frAde = frBufferDesc[toAde.assetName];
      if (frAde.size == toAde.size)
      {
        if (frAde.offset == toAde.offset)
        {
          // Restore the save-me bit. Otherwise leave it alone since it's not moving.
          asset->setIsInAlloc(true);
          asset->setIsReady(true);
        }
        else  // same size, let's just move it
        {
          asset->makeNewWorkingResourceObject();
          asset->recordTransfer_s2s(commandBuffer);
        }
      }
      else  // different size.
      {
        asset->load();
      }
    }
    else
    {
      asset->load();
    }
  }

  assetMan->destroyAssetsThatGotMoved();  // work -> curr
  assetMan->destroyAssetsThatAreNotInAlloc();
}




optional<Graphics> graphics;
