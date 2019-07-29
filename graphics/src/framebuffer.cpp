#include "engine.h"
#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::resetFramebuffer(RenderPassThing & renderPassThing)
{
  logFn();

  for (auto & swapchainThing: swapchainThings)
  {
    if (swapchainThing.framebuffers.size() > renderPassThing.idx && 
        (bool) swapchainThing.framebuffers[renderPassThing.idx] != false)
      { destroyFramebuffer(renderPassThing.idx); }
    
    vector<vk::ImageView> attachments = { 
        swapchainThing.imageView };
    // TODO: Add other image views here, somehow?
    
    swapchainThing.framebuffers[renderPassThing.idx] = 
      vulkanDevice.createFramebuffer(vk::FramebufferCreateInfo{
        (vk::FramebufferCreateFlagBits) 0, 
        swapchainThing.renderPasses[renderPassThing.idx], 
        (uint32_t) attachments.size(), attachments.data(), 
        swapchainExtent.width, swapchainExtent.height, 
        engine->getConfig().graphics.swapchain.numViews
      });

    log(thId, fmt::format("Created {}framebuffer[{}]{}",
      ansi::lightGreen, renderPassThing.data.name, ansi::off));
  }
}


void Graphics::destroyFramebuffer(size_t framebufferIdx)
{
  logFn();

  // destroyPipelines(framebufferIdx);

  log(thId, "Graphics::destroyFramebuffer: actually do that");

  for (auto & st : swapchainThings)
  {
    if (st.framebuffers.size() > framebufferIdx &&
        (bool) st.framebuffers[framebufferIdx] != false)
    {
      log(thId, "Graphics::destroyFramebuffer: actually do that for real");
      vulkanDevice.destroyFramebuffer(st.framebuffers[framebufferIdx]);
      st.framebuffers[framebufferIdx] = nullptr;
    }
  }
}
