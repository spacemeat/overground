#include "engine.h"
#include "graphics.h"
#include <algorithm>
#include "graphicsUtils.h"

using namespace std;
using namespace overground;


void Graphics::resetSwapchain()
{
  logFn();

  auto const & config = engine->getConfig();
  auto & diffs = engine->getConfigDiffs();

  // NOTE: Not destroying the old'n, because we want to use the old'n when making the new'n. We'll destroy at the end.

  if ((bool) swapchain != false)
    { vulkanDevice.waitIdle(); }
  
  if (swapchainThings.size() > 0)
    { destroySwapchainImageViews(); }
  
  auto oldSurfaceFormat = swapchainSurfaceFormat;
  auto oldImageCount = swapchainImageCount;
  auto oldExtent = swapchainExtent;

  chooseSurfaceFormat();
  choosePresentMode();
  getExtent();

  if (oldSurfaceFormat != swapchainSurfaceFormat)
    { diffs |= Config::Deltas::RenderPasses; }
  
  if (oldImageCount != swapchainImageCount)
    { diffs |= Config::Deltas::NumConcurrentFrames; }

  if (oldExtent != swapchainExtent)
  {
    if ((diffs & Config::Deltas::WindowExtents) == 0)
    {
      log(thId, logTags::err, "Window extent delta caught later than is useful.");
      throw runtime_error("SHOULD NOT HAPPEN");
    }

    diffs |= Config::Deltas::WindowExtents;
  }

  // TODO: HRK
  auto imageUsages = vk::ImageUsageFlagBits::eColorAttachment;

  auto imageSharingMode = config.graphics.swapchain.imageSharing ? 
    vk::SharingMode::eConcurrent : vk::SharingMode::eExclusive;
  
  vector<uint32_t> uqfis(uniqueFamilyIndices.begin(), uniqueFamilyIndices.end());

  auto pretransform = config.graphics.swapchain.pretransform;

  auto compositeAlpha = config.graphics.swapchain.windowAlpha;

  auto sci = vk::SwapchainCreateInfoKHR(
    vk::SwapchainCreateFlagsKHR(), surface, 
    swapchainImageCount, swapchainSurfaceFormat.format, 
    swapchainSurfaceFormat.colorSpace, swapchainExtent, 
    config.graphics.swapchain.numViews, imageUsages, 
    imageSharingMode, uqfis.size(), uqfis.data(), 
    pretransform, compositeAlpha, swapchainPresentMode, 
    config.graphics.swapchain.clipped, swapchain);
  
  auto oldSwapchain = swapchain;
  swapchain = vulkanDevice.createSwapchainKHR(sci);

  auto swapchainImages = vulkanDevice.getSwapchainImagesKHR(swapchain);
  swapchainThings.resize(swapchainImages.size());
  
  for (size_t i = 0; i < swapchainImages.size(); ++i)
    { swapchainThings[i].image = swapchainImages[i]; }

  if ((bool) oldSwapchain == true)
    { vulkanDevice.destroySwapchainKHR(oldSwapchain); }

  createSwapchainImageViews();
}


void Graphics::destroySwapchain()
{
  logFn();

  if ((bool) swapchain == false)
    { return; }
  
  for (auto & [_, rpt] : renderPassThings)
    { destroyRenderPass(rpt.idx); }

  destroySwapchainImageViews();

  log(thId, "Graphics::destroySwapchain(): actually do that");

  vulkanDevice.destroySwapchainKHR(swapchain);
  swapchainThings.clear();
  swapchain = nullptr;
}


void Graphics::chooseSurfaceFormat()
{
  auto const & config = engine->getConfig();

  auto & desiredFormats = config.graphics.swapchain.formatPriorities;
  
  if (swapchainSurfaceFormats.size() == 1 &&
    swapchainSurfaceFormats[0].format == vk::Format::eUndefined)
  {
    swapchainSurfaceFormat =
    { desiredFormats[0].first,
      desiredFormats[0].second };
      log(thId, "No format restrictions.");
  }
  else
  {
    auto bestFormat = swapchainSurfaceFormats[0];
    size_t bestFormatIdx = desiredFormats.size();
    for (auto & format : swapchainSurfaceFormats)
    {
      auto pair = make_pair(
        format.format, 
        format.colorSpace);
      if (auto f = find(
        desiredFormats.begin(), desiredFormats.end(), pair);
        f != desiredFormats.end())
      {
        size_t idx = distance(desiredFormats.begin(), f);
        if (idx < bestFormatIdx)
        {
          bestFormatIdx = idx;
          bestFormat = format;
        }
      }
    }

    swapchainSurfaceFormat = bestFormat;

    if (bestFormatIdx == desiredFormats.size())
      { log(thId, "No requested formats found."); }
  }

  log(thId, fmt::format("Usingg swapchain format: {}; {}",
    to_string(swapchainSurfaceFormat.format),
    to_string(swapchainSurfaceFormat.colorSpace)));
}


void Graphics::choosePresentMode()
{
  auto const & config = engine->getConfig();
  
  auto & desiredPresentModes = config.graphics.swapchain.presentModePriorities;

  swapchainPresentMode = swapchainPresentModes.front();
  swapchainImageCount = swapchainSurfaceCaps.minImageCount;

  for (auto & pm : desiredPresentModes)
  {
    auto desiredPm = pm.first;
    if (pm.second >= swapchainSurfaceCaps.minImageCount &&
        pm.second <= swapchainSurfaceCaps.maxImageCount &&
        find(swapchainPresentModes.begin(), 
             swapchainPresentModes.end(), desiredPm) != 
          swapchainPresentModes.end())
    {
      swapchainPresentMode = desiredPm;
      swapchainImageCount = (int) pm.second;
      break;
    }
  }

  log(thId, fmt::format("Using presnet mode {} with {} images.", to_string(swapchainPresentMode), swapchainImageCount));
}


void Graphics::getExtent()
{
  if (swapchainSurfaceCaps.currentExtent.width !=
      numeric_limits<uint32_t>::max())
  {
    log(thId, fmt::format("getExtent_a: {} x {}", 
      swapchainSurfaceCaps.currentExtent.width,
      swapchainSurfaceCaps.currentExtent.height));
    swapchainExtent = swapchainSurfaceCaps.currentExtent;
  }
  else
  {
    int w, h;
    glfwGetFramebufferSize(mainWindow, &w, &h);
    swapchainExtent = vk::Extent2D {
      std::max(swapchainSurfaceCaps.minImageExtent.width, 
        std::min(swapchainSurfaceCaps.maxImageExtent.width, 
        static_cast<uint32_t>(w))),
      std::max(swapchainSurfaceCaps.minImageExtent.width, 
        std::min(swapchainSurfaceCaps.maxImageExtent.width,
        static_cast<uint32_t>(w)))
    };
  }

  log(thId, fmt::format("Using extent {{ {}, {} }}",
    swapchainExtent.width, swapchainExtent.height));
}


void Graphics::createSwapchainImageViews()
{
  logFn();

  auto const & config = engine->getConfig();

  auto & imageView = config.graphics.swapchain.imageView;
  auto viewType = imageView.viewType;

  for (size_t i = 0; i < swapchainThings.size(); ++i)
  {
    auto info = vk::ImageViewCreateInfo(
      (vk::ImageViewCreateFlagBits) 0,
      swapchainThings[i].image,
      viewType, // e2D
      swapchainSurfaceFormat.format,
      vk::ComponentMapping(
        imageView.components[0],
        imageView.components[1],
        imageView.components[2],
        imageView.components[3]
      ),
      vk::ImageSubresourceRange(
        imageView.aspectMask, 0, 1, 0, 
        engine->getConfig().graphics.swapchain.numViews)
      );

      swapchainThings[i].imageView = 
        vulkanDevice.createImageView(info);
    };
}


void Graphics::destroySwapchainImageViews()
{
  logFn();

  for (auto & st : swapchainThings)
  {
    vulkanDevice.destroyImageView(st.imageView);
    st.imageView = nullptr;
  }
}
