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

  vk::Format formatFromString(std::string_view strFormat);

  vk::ColorSpaceKHR colorSpaceFromString(std::string_view strColorSpace);

  vk::PresentModeKHR presentModeFromString(std::string_view strPresentMode);

  vk::SurfaceTransformFlagBitsKHR pretransformFromString(std::string_view strPretransform);

  vk::CompositeAlphaFlagBitsKHR compositeAlphaFromString(std::string_view strCompositeAlpha);
}
