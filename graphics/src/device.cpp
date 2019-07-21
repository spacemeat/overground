#include "graphics.h"
#include <set>
#include <numeric>

using namespace std;
using namespace overground;


void Graphics::resetLogicalDevice()
{
  logFn();

  if (vulkanDevice)
    { destroyLogicalDevice(); }

  auto & pdf = physicalDeviceFitness[physicalDeviceIndex];

  uniqueFamilyIndices = {
    static_cast<uint32_t>(graphicsQueueFamilyIndex),
    static_cast<uint32_t>(computeQueueFamilyIndex),
    static_cast<uint32_t>(transferQueueFamilyIndex),
    static_cast<uint32_t>(presentationQueueFamilyIndex)
  };

  vector<int> queueCounts;

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

    queueCounts.push_back(queueCount);
  }

  queuePriorities.reserve(accumulate(
    begin(queueCounts), end(queueCounts), 0, 
    [](auto a, auto b){ return a + b; }));

  for (auto qfi : uniqueFamilyIndices)
  {
    auto queueCount = queueCounts[queuePriorityStarts.size()];
    for (auto i = 0; i < queueCount; ++i)
      { queuePriorities.push_back(0.0f); }
    
    auto startIdx = queuePriorities.size();
    queuePriorityStarts.push_back(startIdx);

    queueCreateInfos.emplace_back(
      vk::DeviceQueueCreateFlags(),
      qfi, queueCount, queuePriorities.data() + startIdx
    );
  }

  vector<char const *> deviceExtensionsInC { deviceExtensions.size() };
  transform(deviceExtensions.begin(), deviceExtensions.end(), 
    deviceExtensionsInC.begin(), [](auto & ex){ return ex.c_str(); });

  vector<char const *> layersInC { validationLayers.size() };
  transform(validationLayers.begin(), validationLayers.end(), 
    layersInC.begin(), [](auto & ex){ return ex.c_str(); });

  auto dci = vk::DeviceCreateInfo();
  dci.queueCreateInfoCount = queueCreateInfos.size();
  dci.pQueueCreateInfos = queueCreateInfos.data();
  if (config->config.graphics.vulkanValidationEnabled)
  {
    dci.enabledLayerCount = layersInC.size();
    dci.ppEnabledLayerNames = layersInC.data();
  }
  else
    { dci.enabledLayerCount = 0; }

  dci.enabledExtensionCount = deviceExtensionsInC.size();
  dci.ppEnabledExtensionNames = deviceExtensionsInC.data();
  dci.pEnabledFeatures = & usedFeatures;

  vulkanDevice = physicalDevice.createDevice(dci);

  prepareQueues();
}


void Graphics::destroyLogicalDevice()
{
  logFn();

  if ((bool) vulkanDevice == false)
    { return; }

  // TODO: destroy everythig device makes

  destroySwapchain();

  log(thId, "Graphics::destroyLogicalDevice(): actually do that");

  vulkanDevice.destroy();
  vulkanDevice = nullptr;

  gQueues.clear();
  cQueues.clear();

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
    }

    if ((int) qci.queueFamilyIndex == transferQueueFamilyIndex)
      { tQueue = & thisQueue.front(); }

    if ((int) qci.queueFamilyIndex == presentationQueueFamilyIndex)
      { pQueue = & thisQueue.front(); }
  }
}
