#include "graphics.h"
#include <algorithm>
#include <set>

using namespace std;
using namespace overground;


void Graphics::resetPhysicalDevice()
{
  logFn();

  graphicsQueueFamilyIndex = -1;
  computeQueueFamilyIndex = -1;
  transferQueueFamilyIndex = -1;
  presentationQueueFamilyIndex = -1;
  
  deviceExtensions = set<string>(
    config->graphics.deviceExtensions.begin(), 
    config->graphics.deviceExtensions.end());
  if (config->graphics.headless == false)
    { deviceExtensions.insert(VK_KHR_SWAPCHAIN_EXTENSION_NAME); }
  
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

  for (size_t devIdx = 0; devIdx < devices.size(); ++ devIdx)
  {
    auto & device = devices[devIdx];
    auto & pdf = physicalDeviceFitness.emplace_back();

    auto && qfps = device.getQueueFamilyProperties();
    for (size_t qfIdx = 0; qfIdx < qfps.size(); ++ qfIdx)
    {
      auto & qfp = qfps[qfIdx];
      if (qfp.queueCount == 0)
        { continue; }

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
        qca.t = 1;

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

    auto && deps = device.enumerateDeviceExtensionProperties();
    for (auto & devExt : deviceExtensions)
    {
      auto it = find_if(deps.begin(), deps.end(),
        [&](auto ext) { return ext.extensionName == devExt; });
      if (it == deps.end())
        { pdf.featureScore = 0; }
    }

    auto surfaceFormats = device.getSurfaceFormatsKHR(surface);
    auto presentModes = device.getSurfacePresentModesKHR(surface);

    if (surfaceFormats.empty())
      { pdf.featureScore = 0; }

    if (presentModes.empty())
      { pdf.featureScore = 0; }

    if (computePhysicalDeviceFeatures(device, pdf) == false)
      { pdf.featureScore = 0; }
    
    pdf.finalDeviceScore = dqf.g * dqf.c * dqf.t * dqf.p * pdf.featureScore;

    reportPhysicalDevice(device, pdf);
  }

  auto selectedPhysDev = max_element(
    physicalDeviceFitness.begin(), physicalDeviceFitness.end(),
    [](auto & lhs, auto & rhs)
      { return lhs.finalDeviceScore < rhs.finalDeviceScore; });

  physicalDeviceIndex = distance(physicalDeviceFitness.begin(), selectedPhysDev);
  if ((size_t) physicalDeviceIndex == physicalDeviceFitness.size())
    { throw runtime_error("Unable to find a suiteable physical device."); }
  
  if (selectedPhysDev->finalDeviceScore == 0)
    { throw runtime_error("Unable to find a suiteable physical device."); }

  physicalDevice = devices[physicalDeviceIndex];
  auto & fitness = physicalDeviceFitness[physicalDeviceIndex];
  graphicsQueueFamilyIndex = fitness.bestQueueIndices.g;
  computeQueueFamilyIndex = fitness.bestQueueIndices.c;
  transferQueueFamilyIndex = fitness.bestQueueIndices.t;
  presentationQueueFamilyIndex = fitness.bestQueueIndices.p;

  swapchainSurfaceCaps = physicalDevice.getSurfaceCapabilitiesKHR(surface);
  swapchainSurfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);
  swapchainPresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

  log(thId, fmt::format("using device #{}.\n"
    "validation layers: {}\n"
    "extensions: {}\n"
    "device extensions: {}", physicalDeviceIndex,
    join(validationLayers, ", "),
    join(extensions, ", "), 
    join(deviceExtensions, ", ")));
}


void Graphics::reportPhysicalDevice(vk::PhysicalDevice device, 
  deviceFitness_t const & fitness)
{
  auto const & props = device.getProperties();

  auto && qfps = device.getQueueFamilyProperties();

  auto fams = vector<string>(qfps.size());
  stringstream families;
  for (size_t qfIdx = 0; qfIdx < qfps.size(); ++ qfIdx)
  {
    auto & qfp = qfps[qfIdx];
    bool delim = false;
    families << "    ";
    if (qfp.queueFlags & vk::QueueFlagBits::eGraphics)
      { families << "graphics"; delim = true; }
    if (qfp.queueFlags & vk::QueueFlagBits::eCompute)
      { families << fmt::format("{}compute",
      (delim ? " | " : "")); delim = true; }
    if (qfp.queueFlags & vk::QueueFlagBits::eTransfer)
      { families <<  fmt::format("{}transfer",
      (delim ? " | " : "")); delim = true; }
    if (qfp.queueFlags & vk::QueueFlagBits::eSparseBinding)
      { families <<  fmt::format("{}sparseBinding",
      (delim ? " | " : "")); }

    auto canPresent = device.getSurfaceSupportKHR(qfIdx, surface) &&
      config->graphics.headless == false;
    auto & fit = fitness.queueFamilyFitness[qfIdx];

    families << fmt::format(
      " ({} queue(s))\n"
      "      can present: {}\n"
      "      fitness scores: g = {}; c = {}; t = {}; p = {}\n"
      "      feature score: {}",
      qfp.queueCount, canPresent ? "yes" : "no", fit.g, fit.c,
      fit.t, fit.p, fitness.featureScore);
  }

  auto & df = fitness.deviceQueueFitness;

  auto report = fmt::format(
    "physical device: \n"
    "  name:           {}\n"
    "  vendorId:       {:#x}\n"
    "  deviceId:       {:#x}\n"
    "  type:           {}\n"
    "  cache uuid:     0x{}\n"
    "  queue families:\n"
    "{}\n"
    "  unmet feature requirements:\n"
    "    {}\n"
    "  unmet feature desirements:\n"
    "    {}\n"
    "  device fitness score: g = {}; c = {}; t = {}; p = {}\n"
    "  device feature score: {}\n"
    "  device total score: {}",
    props.deviceName, 
    props.vendorID, 
    props.deviceID, 
    vk::to_string(props.deviceType),
    join(props.pipelineCacheUUID, "", "{:x}"),
    families.str(), 
    join(fitness.unsupportedMinFeatures, ", ", "{}", "(none)"), 
    join(fitness.unsupportedDesiredFeatures, ", ", "{}", "(none)"),
    df.g, df.c, df.t, df.p, 
    fitness.featureScore, 
    fitness.finalDeviceScore,
    nullptr   // WTF? Bug in fmt
  );

  log(thId, report);
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
  stringstream ss;
  auto supportedFeatures = device.getFeatures();
  ss << "Checking required features:\n";
  for (auto & feature : config->graphics.minDeviceFeatures)
  {
    ss << "  " << feature << ": ";
#define FEATURE(feat)                                     \
    if (feature == #feat)                                 \
    {                                                       \
      if (supportedFeatures. feat)                           \
      {                                                     \
        usedFeatures. feat = true;                          \
        ss << ansi::lightGreen << "yes" << ansi::off << endl; \
      }                                                     \
      else                                                  \
      {                                                     \
        pdf.unsupportedMinFeatures.push_back(feature);    \
        ss << ansi::lightRed << "no" << ansi::off << endl;  \
      }                                                   \
    }
#include "features.hmb"
#undef FEATURE
  }

  log(thId, ss.str());
  ss = stringstream();

  ss << "Checking desired features:\n";
  for (auto & feature : config->graphics.desiredDeviceFeatures)
  {
    ss << "  " << feature << ": ";
#define FEATURE(feat)                                     \
    if (feature == #feat)                               \
    {                                                     \
      if (supportedFeatures. feat)                           \
      {                                                     \
        usedFeatures.feat = true;                           \
        ss << ansi::lightGreen << "yes" << ansi::off << endl; \
      }                                                     \
      else                                                  \
      {                                                       \
        pdf.unsupportedDesiredFeatures.push_back(feature);  \
        ss << ansi::lightYellow << "no" << ansi::off << endl; \
      }                                                      \
    }
#include "features.hmb"
#undef FEATURE
  }

  log(thId, ss.str());

  return pdf.unsupportedMinFeatures.size() == 0;
}
