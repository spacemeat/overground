#include "utils.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>


namespace overground
{
  inline uint32_t makeVulkanVersion(version_t const & rhs)
  {
    return VK_MAKE_VERSION(
      rhs[0], rhs[1], rhs[2]
    );
  }

  vk::Format formatFromString(std::string const & strFormat);

  vk::ColorSpaceKHR colorSpaceFromString(std::string const & strColorSpace);

  vk::PresentModeKHR presentModeFromString(std::string const & strPresentMode);

  vk::SurfaceTransformFlagBitsKHR pretransformFromString(std::string const & strPretransform);

  vk::CompositeAlphaFlagBitsKHR compositeAlphaFromString(std::string const & strCompositeAlpha);
}
