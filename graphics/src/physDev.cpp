#include "graphics.h"
#include <algorithm>
#include <set>

using namespace std;
using namespace overground;


void Graphics::resetPhysicalDevice()
{
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

  sout ss {};
  for (size_t devIdx = 0; devIdx < devices.size(); ++ devIdx)
  {
    auto & device = devices[devIdx];
    auto & pdf = physicalDeviceFitness.emplace_back();

    size_t tqCount = 0;

    auto && qfps = device.getQueueFamilyProperties();
    for (size_t qfIdx = 0; qfIdx < qfps.size(); ++ qfIdx)
    {
      auto & qfp = qfps[qfIdx];
      auto & fit = pdf.queueFamilyFitness.emplace_back();
      auto & qca = pdf.queueCountsAllowed.emplace_back();

      // get presentation ability
      bool canPresent = device.getSurfaceSupportKHR(qfIdx, surface);

      // graphics
      if (qfp.queueFlags & vk::QueueFlagBits::eGraphics)
      {
        if (qfp.queueCount >= config->graphics.minGraphicsQueues)
        {
          qca.g = min(qfp.queueCount, config->graphics.desiredGraphicsQueues);
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
          qca.c = min(qfp.queueCount, config->graphics.desiredComputeQueues);
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
          qca.t = min(qfp.queueCount, config->graphics.desiredTransferQueues);  // these are available, but used only after those from dedicated transfer queues.
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
        qca.t = min(qfp.queueCount, config->graphics.desiredTransferQueues);

        if (canPresent)
          { fit.p = max(fit.p, 70); }
      }
    }

    auto & qff = pdf.queueFamilyFitness;
    auto & qca = pdf.queueCountsAllowed;
    auto & dqf = pdf.deviceQueueFitness;
    auto & bqi = pdf.bestQueueIndices;

    auto bestG = max_element(qff.begin(), qff.end(), 
      [](auto lhs, auto rhs) { return lhs.g < rhs.g; });
    auto bestC = max_element(qff.begin(), qff.end(),
      [](auto lhs, auto rhs) { return lhs.c < rhs.c; });
    auto bestT = max_element(qff.begin(), qff.end(),
      [](auto lhs, auto rhs) { return lhs.t < rhs.t; });
    auto bestP = max_element(qff.begin(), qff.end(),
      [](auto lhs, auto rhs) { return lhs.p < rhs.p; });
    dqf.g = bestG->g;
    dqf.c = bestC->c;
    dqf.t = bestT->t;
    dqf.p = bestP->p;

    bool usingGraphics = config->graphics.desiredGraphicsQueues > 0;
    bool usingCompute = config->graphics.desiredComputeQueues > 0;
    bool usingTransfer = config->graphics.desiredTransferQueues > 0;
    bool usingPresentation = config->graphics.headless == false;

    if (usingGraphics)
      { bqi.g = distance(qff.begin(), bestG); }
    if (usingCompute)
      { bqi.c = distance(qff.begin(), bestC); }
    if (usingTransfer)
      { bqi.t = distance(qff.begin(), bestT); }
    if (usingPresentation)
      { bqi.p = distance(qff.begin(), bestP); }

    dqf.g = max(dqf.g, usingGraphics ? 0 : 1);
    dqf.c = max(dqf.c, usingCompute ? 0 : 1);
    dqf.t = max(dqf.t, usingTransfer ? 0 : 1);
    dqf.p = max(dqf.p, usingPresentation ? 0 : 1);

    pdf.queueCounts.g = qca[bqi.g].g;
    pdf.queueCounts.c = qca[bqi.c].c;
    pdf.queueCounts.t = qca[bqi.t].t;
    pdf.queueCounts.p = 1;

    if (tqCount < config->graphics.minTransferQueues)
      { dqf.t = 0; }

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
        { pdf.featureScore = 0; }
    }

    swapChainSurfaceCaps = device.getSurfaceCapabilitiesKHR(surface);
    swapChainSurfaceFormats = device.getSurfaceFormatsKHR(surface);
    swapChainPresentModes = device.getSurfacePresentModesKHR(surface);

    if (swapChainSurfaceFormats.empty())
      { pdf.featureScore = 0; }

    if (swapChainPresentModes.empty())
      { pdf.featureScore = 0; }

    // TODO: supported features can be checked here.
    // auto supportedFeatures = device.getFeatures();
    if (computePhysicalDeviceFeatures(device, pdf) == false)
      { pdf.featureScore = 0; }
    
    pdf.finalDeviceScore = dqf.g * dqf.c * dqf.t * dqf.p * pdf.featureScore;

    reportPhysicalDevice(device, pdf, ss);
  }

  auto selectedPhysDev = max_element(
    physicalDeviceFitness.begin(), physicalDeviceFitness.end(),
    [](auto & lhs, auto & rhs)
      { return lhs.finalDeviceScore < rhs.finalDeviceScore; });

  physicalDeviceIndex = distance(physicalDeviceFitness.begin(), selectedPhysDev);
  if ((size_t) physicalDeviceIndex == physicalDeviceFitness.size())
    { throw runtime_error("Unabled to find a suiteable physical devicd."); }
  
  if (selectedPhysDev->finalDeviceScore == 0)
    { throw runtime_error("Unabled to find a suiteable physical devicd."); }

  physicalDevice = devices[physicalDeviceIndex];
  auto & fitness = physicalDeviceFitness[physicalDeviceIndex];
  graphicsQueueFamilyIndex = fitness.bestQueueIndices.g;
  computeQueueFamilyIndex = fitness.bestQueueIndices.c;
  transferQueueFamilyIndex = fitness.bestQueueIndices.t;
  presentationQueueFamilyIndex = fitness.bestQueueIndices.p;
}


void Graphics::reportPhysicalDevice(vk::PhysicalDevice device, 
  deviceFitness_t const & fitness, std::ostream & out)
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
      { out << "      can present" << endl; }

    auto & fit = fitness.queueFamilyFitness[qfIdx];
    out << "      fitness scores: g = " << fit.g 
        << "; c = " << fit.c << "; t = " << fit.t 
        << "; p = " << fit.p << "" << endl
        << "      feature score: " << fitness.featureScore << endl;
  }

  out << "  unmet feature requirements: ";
  if (fitness.unsupportedMinFeatures.size() > 0)
  {
    bool delim = false;
    for (auto feature : fitness.unsupportedMinFeatures)
      { out << (delim ? ", " : "") << feature; delim = true; }    
  }
  else
    { out << " (none)"; }

  out << endl 
      << "  unmet feature desirements: ";
  if (fitness.unsupportedDesiredFeatures.size() > 0)
  {
    bool delim = false;
    for (auto feature : fitness.unsupportedDesiredFeatures)
      { out << (delim ? ", " : "") << feature; delim = true; }
  }
  else
    { out << " (none)"; }

  auto & df = fitness.deviceQueueFitness;
  out << endl
      << "  device fitness scores: g = " << df.g << "; c = " << df.c 
      << "; t = " << df.t << "; p = " << df.p << endl
      << "  device feature score: " << fitness.featureScore << endl
      << "  device total score: " << fitness.finalDeviceScore << endl;
}


/*
    get features from physicalDevice
    for each minFeature in minFeatures,
      if features[minFeature] == true,
        useFeature[minFeature] = true
      else
        addToUnsupported(minFeature)
    
    for each desiredFeature in desiredFeatures,
      if features[desiredFeature] == true,
        useFeature[desiredFeature] = true
      else
        addToDisappointed(desiredFeature)
    
    if (unsupported.size() > 0) fail();
*/
bool Graphics::computePhysicalDeviceFeatures(vk::PhysicalDevice device, deviceFitness_t & pdf)
{
  sout ss {};
  auto supportedFeatures = device.getFeatures();
  for (auto & feature : config->graphics.minDeviceFeatures)
  {
    ss << "Checking required feature " << feature << ": ";
#define FEATURE(feat)                                     \
    if (feature == #feat)                                 \
    {                                                       \
      if (supportedFeatures. feat)                           \
        { usedFeatures. feat = true; ss << "yes" << endl; } \
      else                                                  \
        { pdf.unsupportedMinFeatures.push_back(feature); ss << "no" << endl; }  \
    }
#include "features.hmb"
#undef FEATURE
  }

  for (auto & feature : config->graphics.desiredDeviceFeatures)
  {
    ss << "Checking desired feature " << feature << ": ";
#define FEATURE(feat)                                     \
    if (feature == #feat)                               \
    {                                                     \
      if (supportedFeatures. feat)                           \
        { usedFeatures. feat = true; ss << "yes" << endl; }  \
      else                                                  \
        { pdf.unsupportedDesiredFeatures.push_back(feature); ss << "no" << endl; } \
    }
#include "features.hmb"
#undef FEATURE
  }

  return pdf.unsupportedMinFeatures.size() == 0;
}
