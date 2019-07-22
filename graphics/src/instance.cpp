#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::resetVulkanInstance(Config::Deltas & diffs)
{
  logFn();

  if ((bool) vulkanInstance == true)
    { destroyVulkanInstance(); }

  auto appInfo = vk::ApplicationInfo();
  appInfo.pApplicationName = config->general.programName.c_str();
  appInfo.applicationVersion = makeVulkanVersion(config->general.version);
  appInfo.pEngineName = engineName;
  appInfo.engineVersion = makeVulkanVersion(engineVersion);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  uint32_t glfwExtensionCount = 0;
  extensions.clear();
  validationLayers.clear();

  log(thId, "Graphics::resetVulkanInstance(): Making Vulkan instance:");

  if (config->graphics.isConfigured)
  {
    const char ** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(
      & glfwExtensionCount);

    extensions.insert(extensions.end(),
      glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (config->graphics.vulkanValidationEnabled)
      { extensions.push_back("VK_EXT_debug_report"); }
  }

  for (auto & ext : extensions)
    { log(thId, fmt::format(" Requesting extension {}", ext)); }
  
  if (config->graphics.vulkanValidationEnabled)
  {
    for (auto & val : config->graphics.vulkanValidationLayers)
    {
      log(thId, fmt::format(" Requesting layer {}", val));
      validationLayers.push_back(val.c_str());
    }
  }

  if (checkVulkanExtensionSupport())
  {
    vector<char const *> extensionsInC { extensions.size() };
    transform(extensions.begin(), extensions.end(), 
      extensionsInC.begin(), [](auto & ex){ return ex.c_str(); });

    vector<char const *> layersInC { validationLayers.size() };
    transform(validationLayers.begin(), validationLayers.end(), 
      layersInC.begin(), [](auto & la){ return la.c_str(); });

    bool validating = config->graphics.vulkanValidationEnabled;
    if (validating == false || 
        checkVulkanValidationLayerSupport())
    {
      auto instInfo = vk::InstanceCreateInfo();

      instInfo.pApplicationInfo = & appInfo;
      instInfo.enabledExtensionCount = extensionsInC.size();
      instInfo.ppEnabledExtensionNames = extensionsInC.data();
      if (validating)
      {
        instInfo.enabledLayerCount = layersInC.size();
        instInfo.ppEnabledLayerNames = layersInC.data();
      }
      else
      {
        instInfo.enabledLayerCount = 0;
        instInfo.ppEnabledLayerNames = nullptr;
      }

      CHK(vk::createInstance(& instInfo, nullptr,
        & vulkanInstance));
      log(thId, "Graphics::resetVulkanInstance(): Instance made.");

      // TODO: If using multiple devices, call
//      VkInstance inst = vulkanInstance;
      //vkExtInitInstance(inst);
      // else, if using one device, call
//      vkExtInitDevice(device); when we make the device. But does that mean we have to defer the debug reporter creation until then?
      // endif

      resetVulkanDebugReporter();
    }
  }
}


VKAPI_ATTR VkBool32 VKAPI_CALL validationReportCallackFn(
  VkDebugReportFlagsEXT flags,
  VkDebugReportObjectTypeEXT objType,
  uint64_t obj,
  size_t location,
  int32_t code,
  char const * layerPrefix,
  char const * msg,
  void * userData)
{
  char const * titleColor;
  char const * msgColor;
  int logTags = 0;
  if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
  {
    titleColor = ansi::lightMagenta;
    msgColor = ansi::darkMagenta;
    logTags |= logTags::verb;
  }
  if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
  {
    titleColor = ansi::lightBlue;
    msgColor = ansi::darkBlue;
    logTags |= logTags::dbg;
  }
  if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT ||
      flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
  {
    titleColor = ansi::lightYellow;
    msgColor = ansi::darkYellow;
    logTags |= logTags::warn;
  }
  if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
  {
    titleColor = ansi::lightRed;
    msgColor = ansi::darkRed;
    logTags |= logTags::err;
  }

  log(thId, logTags, fmt::format("{}{}: {}{}{}",
    titleColor, layerPrefix, 
    msgColor, msg, ansi::off));

  return VK_FALSE;
}


void Graphics::destroyVulkanInstance()
{
  logFn();

  if ((bool) vulkanInstance == false)
    { return; }

  destroyLogicalDevice();

  destroyVulkanDebugReporter();

  log(thId, "Graphics::destroyVulkanInstance(): actually do that");

  vulkanInstance.destroy(nullptr);
  vulkanInstance = nullptr;
}


void Graphics::resetVulkanDebugReporter()
{
  logFn();

  if (debugCallback != nullptr)
  {
    destroyVulkanDebugReporter();
  }

  if (config->graphics.vulkanValidationEnabled)
  {
    vk::DebugReportFlagsEXT flags = 
      (vk::DebugReportFlagBitsEXT) 0;
    for (auto report : config->graphics.vulkanValidationReports)
    {
      if (report == "info")
        { flags |= vk::DebugReportFlagBitsEXT::eInformation; }
      if (report == "warning")
        { flags |= vk::DebugReportFlagBitsEXT::eWarning; }
      if (report == "perfWarning")
        { flags |= vk::DebugReportFlagBitsEXT::ePerformanceWarning; }
      if (report == "error")
        { flags |= vk::DebugReportFlagBitsEXT::eError; }
      if (report == "debug")
        { flags |= vk::DebugReportFlagBitsEXT::eDebug; }
    }

    vk::DebugReportCallbackCreateInfoEXT cbi;
    cbi.flags = flags;
    cbi.pfnCallback = validationReportCallackFn;

    auto callbackMaker =
      (PFN_vkCreateDebugReportCallbackEXT)
      vkGetInstanceProcAddr(vulkanInstance, 
        "vkCreateDebugReportCallbackEXT");

    if (callbackMaker)
    {
      callbackMaker(vulkanInstance, 
        reinterpret_cast<const 
          VkDebugReportCallbackCreateInfoEXT *>
        (& cbi), nullptr, & debugCallback);
    }
  }
}


void Graphics::destroyVulkanDebugReporter()
{
  logFn();

  if (debugCallback == nullptr)
  { return; }

  auto callbackKiller = 
    (PFN_vkDestroyDebugReportCallbackEXT)
    vkGetInstanceProcAddr(vulkanInstance, 
      "vkDestroyDebugReportCallbackEXT");

  if (callbackKiller)
  {
    callbackKiller(vulkanInstance, 
      debugCallback, nullptr);
  }

  debugCallback = nullptr;
}


bool Graphics::checkVulkanExtensionSupport()
{
  auto && availableExtensionProps = vk::enumerateInstanceExtensionProperties();

  bool allGood = true;
  for (auto const & ext : extensions)
  {
    bool found = false;
    for (auto const & aeProp : availableExtensionProps)
    {
      if (strcmp(aeProp.extensionName, ext.c_str()) == 0)
      {
        log(thId, fmt::format("Extension {} available.", ext));
        found = true;
        break;
      }
    }

    if (found == false)
    {
        log(thId, fmt::format("Extension {} unavailable.", ext));
      allGood = false;
    }
  }

  return allGood;
}


bool Graphics::checkVulkanValidationLayerSupport()
{
  auto && availableLayerProps = vk::enumerateInstanceLayerProperties();

  bool allGood = true;
  for (auto const & layer : validationLayers)
  {
    bool found = false;
    for (auto const & alProp : availableLayerProps)
    {
      if (strcmp(alProp.layerName, layer.c_str()) == 0)
      {
        log(thId, fmt::format("  Validation layer {} available.", layer));
        found = true;
        break;
      }
    }

    if (found == false)
    {
        log(thId, fmt::format("  Validation layer {} unavailable.", layer));
      allGood = false;
    }
  }

  return allGood;
}
