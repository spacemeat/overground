#include "utils.h"
#include "engine.h"
#include "graphics.h"
#include "renderPass-gen.h"


using namespace std;
using namespace overground;


void Graphics::updateRenderPass(renderPass_t newRenderPass)
{
  logFn();

  log(thId, logTags::asset, fmt::format(
    "new render pass:\n"
    "{}\n", print(newRenderPass)));

  renderPassThings.insert_or_assign(newRenderPass.name,
    RenderPassThing { newRenderPass, renderPassThings.size(), true });

  engine->getUpdatedObjectKinds() |= DataObjectKindFlags::renderPass;
}


void Graphics::resetRenderPass(Graphics::RenderPassThing & renderPassThing)
{
  logFn();

  for (auto & swapchainThing: swapchainThings)
  {
    if (swapchainThing.framebuffers.size() > renderPassThing.idx && 
        (bool) swapchainThing.framebuffers[renderPassThing.idx] != false)
      { destroyFramebuffer(renderPassThing.idx); }

    if (swapchainThing.renderPasses.size() > renderPassThing.idx && 
        (bool) swapchainThing.renderPasses[renderPassThing.idx] != false)
      { destroyRenderPass(renderPassThing.idx); }
    
    vector<vk::AttachmentDescription> attDescs;
    unordered_map<string, size_t> attachmentIdxs;
    size_t idx = 0;
    for (auto & ad : renderPassThing.data.attachments)
    {
      attDescs.emplace_back(
        ad.flags,
        swapchainSurfaceFormat.format,
        ad.numSamples, ad.loadOp, ad.storeOp, 
        ad.stencilLoadOp, ad.stencilStoreOp, 
        ad.initialLayout, ad.finalLayout);
      attachmentIdxs.insert({ad.name, idx ++});
    }

    struct SubpassObj {
      vector<vk::AttachmentReference> inpAtts;
      vector<vk::AttachmentReference> colAtts;
      vector<vk::AttachmentReference> resAtts;
      optional<vk::AttachmentReference> depAtt;
      vector<unsigned int> preAtts;
    };
    vector<SubpassObj> subpassObjs;
    vector<vk::SubpassDescription> subpasses;

    for (auto & sd : renderPassThing.data.subpasses)
    {
      subpassObjs.emplace_back();
      auto & subObj = subpassObjs.back();
      for (auto & ar : sd.inputAttachments)
      {
        subObj.inpAtts.emplace_back(
          attachmentIdxs[ar.attachment], ar.layout);
      }
      for (auto & ar : sd.colorAttachments)
      {
        subObj.colAtts.emplace_back(
          attachmentIdxs[ar.attachment], ar.layout);
      }
      for (auto & ar : sd.resolveAttachments)
      {
        subObj.resAtts.emplace_back(
          attachmentIdxs[ar.attachment], ar.layout);
      }
      if ((bool) sd.depthStencilAttachment)
      {
        auto & dsa = (* sd.depthStencilAttachment);
        subObj.depAtt.emplace(attachmentIdxs[dsa.attachment], dsa.layout);
      }
      for (auto & ar : sd.preserveAttachments)
      {
        subObj.preAtts.push_back(ar);
      }

      subpasses.emplace_back(
        sd.flags, sd.bindPoint, 
        (uint32_t) subObj.inpAtts.size(), subObj.inpAtts.data(),
        (uint32_t) subObj.colAtts.size(), subObj.colAtts.data(),
        subObj.resAtts.data(),
        subObj.depAtt ? (& (* subObj.depAtt)) : nullptr,
        (uint32_t) subObj.preAtts.size(), subObj.preAtts.data());
    }

    vector<vk::SubpassDependency> subpassDeps;
    for (auto & sdep : renderPassThing.data.dependencies)
    {
      subpassDeps.emplace_back(
        sdep.srcSubpass, sdep.dstSubpass,
        sdep.srcStageMask, sdep.dstStageMask, 
        sdep.srcAccessMask, sdep.dstAccessMask
      );
    }

    swapchainThing.renderPasses[renderPassThing.idx] = 
      vulkanDevice.createRenderPass({
        (vk::RenderPassCreateFlags) 0,
        (uint32_t) attDescs.size(), attDescs.data(),
        (uint32_t) subpasses.size(), subpasses.data(),
        (uint32_t) subpassDeps.size(), subpassDeps.data()
    });
    
    log(thId, fmt::format("Created {}renderPass[{}]{}",
      ansi::lightGreen, renderPassThing.data.name, ansi::off));
  }
}


void Graphics::destroyRenderPass(size_t renderPassIdx)
{
  logFn();

  destroyFramebuffer(renderPassIdx);

  log(thId, "Graphics::destroyRenderPass: actually do that");
  for (auto & st : swapchainThings)
  {
    if (st.renderPasses.size() > renderPassIdx &&
        (bool) st.renderPasses[renderPassIdx] != false)
    {
      log(thId, "Graphics::destroyRenderPass: actually do that for real");
      vulkanDevice.destroyRenderPass(st.renderPasses[renderPassIdx]);
      st.renderPasses[renderPassIdx] = nullptr;
    }
  }
}
