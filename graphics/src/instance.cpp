#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::createVulkanInstance()
{
  if ((bool) vulkanInstance == true)
  {
    destroyVulkanInstance();
  }

  auto appInfo = vk::ApplicationInfo();
  appInfo.pApplicationName = config->general.programName.c_str();
  appInfo.applicationVersion = makeVulkanVersion(config->general.version);
  appInfo.pEngineName = engineName;
  appInfo.engineVersion = makeVulkanVersion(engineVersion);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  uint32_t glfwExtensionCount = 0;
  const char ** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(& glfwExtensionCount);

  extensions.insert(extensions.end(),
  glfwExtensions, glfwExtensions + glfwExtensionCount);

  if (config->graphics.validationEnabled)
  {
    extensions.push_back("VK_EXT_debug_repot");
    validationLayers.push_back("VK_LAYER_LUNARG_standard_validation");
  }

  if (checkExtensionSupport() &&
      checkValidationLayerSupport())
  {
    auto instInfo = vk::InstanceCreateInfo();
    instInfo.pApplicationInfo = & appInfo;
    instInfo.enabledExtensionCount = extensions.size();
    instInfo.ppEnabledExtensionNames = extensions.data();
    instInfo.enabledLayerCount = validationLayers.size();
    instInfo.ppEnabledLayerNames = validationLayers.data();

    CHK(vk::createInstance(& instInfo, nullptr,
      & vulkanInstance));
  }
}


void Graphics::destroyVulkanInstance()
{
  if ((bool) vulkanInstance == true)
    { vulkanInstance.destroy(nullptr); }
}


bool Graphics::checkExtensionSupport()
{
  auto && availableExtensionProps = vk::enumerateInstanceExtensionProperties();

  bool allGood = true;
  for (auto const & ext : extensions)
  {
    bool found = false;
    for (auto const & aeProp : availableExtensionProps)
    {
      if (strcmp(aeProp.extensionName, ext) == 0)
      {
        sout {} << "Extension " << ext << " available." << endl;
        found = true;
        break;
      }
    }

    if (found == false)
    {
      sout {} << "Extension " << ext << " unavailable." << endl;
      allGood = false;
    }
  }

  return allGood;
}


bool Graphics::checkValidationLayerSupport()
{
  auto && availableLayerProps = vk::enumerateInstanceLayerProperties();

  bool allGood = true;
  for (auto const & layer : validationLayers)
  {
    bool found = false;
    for (auto const & alProp : availableLayerProps)
    {
      if (strcmp(alProp.layerName, layer) == 0)
      {
        sout {} << "Validation layer " << layer << " available." << endl;
        found = true;
        break;
      }
    }

    if (found == false)
    {
      sout {} << "Extension " << layer << " unavailable." << endl;
      allGood = false;
    }
  }

  return allGood;
}
