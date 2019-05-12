#include "graphics.h"
#include <set>

using namespace std;
using namespace overground;


void Graphics::resetLogicalDevice()
{
  if (vulkanDevice)
    { destroyLogicalDevice(); }

  auto & pdf = physicalDeviceFitness[physicalDeviceIndex];

  uniqueFamilyIndices = {
    static_cast<uint32_t>(graphicsQueueFamilyIndex),
    static_cast<uint32_t>(computeQueueFamilyIndex),
    static_cast<uint32_t>(transferQueueFamilyIndex),
    static_cast<uint32_t>(presentationQueueFamilyIndex)
  };

  queueCreateInfos.clear();
  for (auto qfi : uniqueFamilyIndices)
  {
    // get queue count
    int queueCount = 0;
    if (static_cast<int>(qfi) == graphicsQueueFamilyIndex)
    { queueCount = max(queueCount, static_cast<int>(pdf.queueCounts.g)); }

    if (static_cast<int>(qfi) == computeQueueFamilyIndex)
    { queueCount = max(queueCount, static_cast<int>(pdf.queueCounts.c)); }

    if (static_cast<int>(qfi) == transferQueueFamilyIndex)
    { queueCount = max(queueCount, static_cast<int>(pdf.queueCounts.t)); }

    if (static_cast<int>(qfi) == presentationQueueFamilyIndex)
    { queueCount = max(queueCount, static_cast<int>(pdf.queueCounts.p)); }

    queueCreateInfos.emplace_back(
      vk::DeviceQueueCreateFlags(),
      qfi, queueCount, nullptr      // TODO: handle queue priorities
    );
  }

  auto dci = vk::DeviceCreateInfo();
  dci.queueCreateInfoCount = queueCreateInfos.size();
  dci.pQueueCreateInfos = queueCreateInfos.data();
  if (config->graphics.vulkanValidationEnabled)
  {
    dci.enabledLayerCount = validationLayers.size();
    dci.ppEnabledLayerNames = validationLayers.data();
  }
  else
    { dci.enabledLayerCount = 0; }
  dci.enabledExtensionCount = deviceExtensions.size();
  dci.ppEnabledExtensionNames = deviceExtensions.data();
  dci.pEnabledFeatures = & usedFeatures;

  vulkanDevice = physicalDevice.createDevice(dci);

  prepareQueues();
}


void Graphics::destroyLogicalDevice()
{
  if ((bool) vulkanDevice == false)
    { return; }

  // TODO: destroy everythig device makes
  // That's a lotta stuff

  vulkanDevice.destroy();
  gQueues.clear();
  cQueues.clear();
  tQueues.clear();

  uniqueFamilyIndices.clear();
}


void Graphics::prepareQueues()
{
  auto & pdf = physicalDeviceFitness[ physicalDeviceIndex ];

  for (auto & qci : queueCreateInfos)
  {
    auto & thisQueue = queues.emplace_back();
    for (size_t i = 0; i < qci.queueCount; ++i)
    {
      thisQueue.push_back(vulkanDevice.getQueue(qci.queueFamilyIndex, i));
      auto & addedQueue = thisQueue.back();
      if ((int) qci.queueFamilyIndex == graphicsQueueFamilyIndex &&
          (int) gQueues.size() < pdf.queueCounts.g)
        { gQueues.push_back(& addedQueue); }

      if ((int) qci.queueFamilyIndex == computeQueueFamilyIndex &&
          (int) cQueues.size() < pdf.queueCounts.c)
        { cQueues.push_back(& addedQueue); }

      if ((int) qci.queueFamilyIndex == transferQueueFamilyIndex &&
          (int) tQueues.size() < pdf.queueCounts.t)
        { tQueues.push_back(& addedQueue); }
    }

    // TODO: Distribute additional transfer queues through g and c on different qfis. I don't really care about it at the moment. Do we ever need more than one t queue?

    if ((int) qci.queueFamilyIndex == presentationQueueFamilyIndex)
      { pQueue = & thisQueue.front(); }
  }
}
