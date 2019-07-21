#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

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

  template<class EnumType>
  EnumType fromString(std::string_view rhs);

  template<>
  vk::Format fromString<vk::Format>(std::string_view rhs);

  template<>
  vk::ColorSpaceKHR fromString<vk::ColorSpaceKHR>(std::string_view rhs);

  template<>
  vk::PresentModeKHR fromString<vk::PresentModeKHR>(std::string_view rhs);

  template<>
  vk::SurfaceTransformFlagBitsKHR fromString<vk::SurfaceTransformFlagBitsKHR>(std::string_view rhs);

  template<>
  vk::CompositeAlphaFlagBitsKHR fromString<vk::CompositeAlphaFlagBitsKHR>(std::string_view rhs);
}

#endif // #ifndef GRAPHICSUTILS_H
