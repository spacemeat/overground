#include "graphics.h"
#include <algorithm>
#include <set>

using namespace std;
using namespace overground;


void Graphics::resetPhysicalDevice()
{
  if (physicalDevice)
    { destroyPhysicalDevice(); }

  graphicsQueueFamilyIndex = -1;
  computeQueueFamilyIndex = -1;
  transferQueueFamilyIndex = -1;
  presentationQueueFamilyIndex = -1;
  
  auto && devices = vulkanInstance.enumeratePhysicalDevices();
  if (devices.size() == 0)
    { throw runtime_error("No physical devices found."); }

  /*
    If I need just graphics queues, find them. If I need just compute queues, find them.
    if I need graphics queues and compute queues, prefer separate queues for concurrency (asynchronous compute). Prefer separate transfer queue, and then either graphics or compute, whichever is primarily used. Prefer graphics queue for presentation. (I think. I mean, I can always test it out.)

    for each device (index di)
      tqcount = 0
      for each queue family (index qfi)
        qt[di][qfi].g = 0, .c = 0, .t = 0
        if qf &= graphics,
          if q-count >= minGraphicsQueues,
            qt[di][qfi].g = 100
            if q-count < desiredGraphicsQueues,
              qt[di][qfi].g -= max(desiredGraphicsQueues - q-count, 50)
        if qf &= compute,
          if q-count >= minComputeQueues,
            qt[di][qfi].c = 100
            if q-count < desiredComputeQueues,
              qt[di][qfi].c -= max(desiredComputeQueues - q-count, 50)
        if qf &= graphics || qf &= compute,
          qt[di][qfi].t = 90
          if q-count < desiredTransferQueues,
            qt[di][qfi].t -= max(desiredTransferQueues - q-count, 50)
          tqcount += q-count
        if qf &= graphics | compute,
          qt[di][qfi].g -= 10
          qt[di][qfi].c -= 10
          qt[di][qfi].t -= 10
        if qf &= transfer only,
          qt[di][qfi].t = 100
          tqcount += q-count
      
      dt[di].g = max( qt[di][*].g, using-g?1:0 )
      dt[di].c = max( qt[di][*].c, using-c?1:0 )
      dt[di].t = max( qt[di][*].c, using-t?1:0 )
      if tqcount < minTransferQueues,
        dt[di].t = 0

      dt[di].final = .g * .c * .t

    select device with best .final    
  */

  vector<vector<fitness_t>> qff;  // queue family fitness
  vector<fitness_t> df;           // device fitness
  vector<fitness_t> bests;        // doesn't store scores, but indices
  vector<int> featureScores;
  vector<int> finalDeviceScores;

  sout ss {};
  for (size_t devIdx = 0; devIdx < devices.size(); ++ devIdx)
  {
    auto & device = devices[devIdx];
    qff.emplace_back();
    df.emplace_back();
    bests.emplace_back(fitness_t {-1, -1, -1, -1});
    featureScores.emplace_back(1);
    size_t tqCount = 0;

    auto && qfps = device.getQueueFamilyProperties();
    for (size_t qfIdx = 0; qfIdx < qfps.size(); ++ qfIdx)
    {
      auto & qfp = qfps[qfIdx];
      auto & fit = qff.back().emplace_back();

      // get presentation ability
      bool canPresent = device.getSurfaceSupportKHR(qfIdx, surface);

      // graphics
      if (qfp.queueFlags & vk::QueueFlagBits::eGraphics)
      {
        if (qfp.queueCount >= config->graphics.minGraphicsQueues)
        {
          fit.g = 100;
          if (qfp.queueCount < config->graphics.desiredGraphicsQueues)
          {
            fit.g -= min(config->graphics.desiredGraphicsQueues - qfp.queueCount, 50u);
          }
        }

        if (canPresent)
          { fit.p = 90; }
      }

      // compute
      if (qfp.queueFlags & vk::QueueFlagBits::eCompute)
      {
        if (qfp.queueCount >= config->graphics.minComputeQueues)
        {
          fit.c = 100;
          if (qfp.queueCount < config->graphics.desiredComputeQueues)
          {
            fit.c -= min(config->graphics.desiredComputeQueues - qfp.queueCount, 50u);
          }
        }

        if (canPresent)
          { fit.p = max(fit.p, 80); }
      }

      // either
      if ((qfp.queueFlags & vk::QueueFlagBits::eGraphics) ||
          (qfp.queueFlags & vk::QueueFlagBits::eCompute))
      {
        fit.t = 90;
        if (qfp.queueCount < config->graphics.desiredTransferQueues)
        {
          fit.t -= min(config->graphics.desiredTransferQueues - qfp.queueCount, 50u);
        }

        tqCount += qfp.queueCount;
      }

      // both
      if ((qfp.queueFlags & vk::QueueFlagBits::eGraphics) &&
          (qfp.queueFlags & vk::QueueFlagBits::eCompute))
      {
        fit.g -= 10;
        fit.c -= 10;
        fit.t -= 10;
      }

      // transfer only
      if ((qfp.queueFlags & ~ vk::QueueFlagBits::eTransfer) ==
        (vk::QueueFlags) 0)
      {
        fit.t = 100;
        tqCount += qfp.queueCount;

        if (canPresent)
          { fit.p = max(fit.p, 70); }
      }
    }

    auto bestG = max_element(qff[devIdx].begin(), qff[devIdx].end(), 
      [](auto lhs, auto rhs) { return lhs.g < rhs.g; });
    auto bestC = max_element(qff[devIdx].begin(), qff[devIdx].end(),
      [](auto lhs, auto rhs) { return lhs.c < rhs.c; });
    auto bestT = max_element(qff[devIdx].begin(), qff[devIdx].end(),
      [](auto lhs, auto rhs) { return lhs.t < rhs.t; });
    auto bestP = max_element(qff[devIdx].begin(), qff[devIdx].end(),
      [](auto lhs, auto rhs) { return lhs.p < rhs.p; });
    df[devIdx].g = bestG->g;
    df[devIdx].c = bestC->c;
    df[devIdx].t = bestT->t;
    df[devIdx].p = bestP->p;

    bool usingGraphics = config->graphics.desiredGraphicsQueues > 0;
    bool usingCompute = config->graphics.desiredComputeQueues > 0;
    bool usingTransfer = config->graphics.desiredTransferQueues > 0;
    bool usingPresentation = config->graphics.headless == false;

    if (usingGraphics)
      { bests[devIdx].g = distance(qff[devIdx].begin(), bestG); }
    if (usingCompute)
      { bests[devIdx].c = distance(qff[devIdx].begin(), bestC); }
    if (usingTransfer)
      { bests[devIdx].t = distance(qff[devIdx].begin(), bestT); }
    if (usingPresentation)
      { bests[devIdx].p = distance(qff[devIdx].begin(), bestP); }

    df[devIdx].g = max(df[devIdx].g, usingGraphics ? 0 : 1);
    df[devIdx].c = max(df[devIdx].c, usingCompute ? 0 : 1);
    df[devIdx].t = max(df[devIdx].t, usingTransfer ? 0 : 1);
    df[devIdx].p = max(df[devIdx].p, usingPresentation ? 0 : 1);

    if (tqCount < config->graphics.minTransferQueues)
      { df[devIdx].t = 0; }

    // TODO: next scores: device extension support, swap chain stuff, required features
    auto deviceExtensions = set<string>(config->graphics.deviceExtensions.begin(), config->graphics.deviceExtensions.end());
    if (config->graphics.headless == false)
      { deviceExtensions.insert(VK_KHR_SWAPCHAIN_EXTENSION_NAME); }
    
    auto && deps = device.enumerateDeviceExtensionProperties();
    for (auto & devExt : deviceExtensions)
    {
      auto it = find_if(deps.begin(), deps.end(),
        [&](auto ext) { return ext.extensionName == devExt; });
      if (it == deps.end())
        { featureScores[devIdx] = 0; }
    }

    swapChainSurfaceCaps = device.getSurfaceCapabilitiesKHR(surface);
    swapChainSurfaceFormats = device.getSurfaceFormatsKHR(surface);
    swapChainPresentModes = device.getSurfacePresentModesKHR(surface);

    if (swapChainSurfaceFormats.empty())
      { featureScores[devIdx] = 0; }

    if (swapChainPresentModes.empty())
      { featureScores[devIdx] = 0; }

    // TODO: supported features can be checked here.
    // auto supportedFeatures = device.getFeatures();
    
    finalDeviceScores.push_back(df[devIdx].g * df[devIdx].c * df[devIdx].t * df[devIdx].p * featureScores[devIdx]);

    reportPhysicalDevice(device, qff[devIdx], df[devIdx], featureScores[devIdx], finalDeviceScores[devIdx], ss);
  }

  auto selectedPhysDev = max_element(
    finalDeviceScores.begin(), finalDeviceScores.end());

  auto deviceIdx = distance(finalDeviceScores.begin(), selectedPhysDev);
  physicalDevice = devices[deviceIdx];
  graphicsQueueFamilyIndex = bests[deviceIdx].g;
  computeQueueFamilyIndex = bests[deviceIdx].c;
  transferQueueFamilyIndex = bests[deviceIdx].t;
  presentationQueueFamilyIndex = bests[deviceIdx].p;
}


void Graphics::reportPhysicalDevice(
  vk::PhysicalDevice const & device,
  vector<fitness_t> const & qff, 
  fitness_t const & df, 
  int featureScore,
  int deviceScore, 
  ostream & out)
{
  auto const & props = device.getProperties();
  out << "physical device:" << endl
      << "  name:           " << props.deviceName << endl
      << "  vendorId:       " << props.vendorID << endl
      << "  deviceId:       " << props.deviceID << endl
      << "  type:           " << vk::to_string(props.deviceType) << endl
      << "  cache uuid:     " << std::hex;
  for (auto ch : props.pipelineCacheUUID)
    { out << (int) ch; }
  out << std::dec << endl << "  families:" << endl;

  auto && qfps = device.getQueueFamilyProperties();
  for (size_t qfIdx = 0; qfIdx < qfps.size(); ++ qfIdx)
  {
    auto & qfp = qfps[qfIdx];
    bool delim = false;
    out << "    ";
    if (qfp.queueFlags & vk::QueueFlagBits::eGraphics)
      { out << "graphics"; delim = true; }
    if (qfp.queueFlags & vk::QueueFlagBits::eCompute)
      { out << (delim ? " | " : "") << "compute"; delim = true; }
    if (qfp.queueFlags & vk::QueueFlagBits::eTransfer)
      { out << (delim ? " | " : "") << "transfer"; delim = true; }
    if (qfp.queueFlags & vk::QueueFlagBits::eSparseBinding)
      { out << (delim ? " | " : "") << "sparseBinding"; }

    out << " (" << qfp.queueCount << " queue(s))" << endl;
    if (device.getSurfaceSupportKHR(qfIdx, surface) &&
      config->graphics.headless == false)
      { out << "      (can present)" << endl; }

    out << "      fitness scores: g = " << qff[qfIdx].g 
        << "; c = " << qff[qfIdx].c << "; t = " << qff[qfIdx].t 
        << "; p = " << qff[qfIdx].p << "" << endl
        << "      feature score: " << featureScore << endl;
  }

  out << "  device scores: g = " << df.g << "; c = " << df.c 
      << "; t = " << df.t << "; p = " << df.p << endl
      << "  device total score: " << deviceScore << endl;
}
