#include "enumParsers.h"

using namespace std;
using namespace overground;

template<>
vk::AccessFlagBits overground::fromString<vk::AccessFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::AccessFlagBits> il = {
    vk::AccessFlagBits::eIndirectCommandRead,
    vk::AccessFlagBits::eIndexRead,
    vk::AccessFlagBits::eVertexAttributeRead,
    vk::AccessFlagBits::eUniformRead,
    vk::AccessFlagBits::eInputAttachmentRead,
    vk::AccessFlagBits::eShaderRead,
    vk::AccessFlagBits::eShaderWrite,
    vk::AccessFlagBits::eColorAttachmentRead,
    vk::AccessFlagBits::eColorAttachmentWrite,
    vk::AccessFlagBits::eDepthStencilAttachmentRead,
    vk::AccessFlagBits::eDepthStencilAttachmentWrite,
    vk::AccessFlagBits::eTransferRead,
    vk::AccessFlagBits::eTransferWrite,
    vk::AccessFlagBits::eHostRead,
    vk::AccessFlagBits::eHostWrite,
    vk::AccessFlagBits::eMemoryRead,
    vk::AccessFlagBits::eMemoryWrite,
    vk::AccessFlagBits::eCommandProcessReadNVX,
    vk::AccessFlagBits::eCommandProcessWriteNVX,
    vk::AccessFlagBits::eColorAttachmentReadNoncoherentEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}AccessFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::AttachmentDescriptionFlagBits overground::fromString<vk::AttachmentDescriptionFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::AttachmentDescriptionFlagBits> il = {
    vk::AttachmentDescriptionFlagBits::eMayAlias,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}AttachmentDescriptionFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::AttachmentLoadOp overground::fromString<vk::AttachmentLoadOp>(std::string_view rhs)
{
  static initializer_list<vk::AttachmentLoadOp> il = {
    vk::AttachmentLoadOp::eLoad,
    vk::AttachmentLoadOp::eClear,
    vk::AttachmentLoadOp::eDontCare,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}AttachmentLoadOp{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::AttachmentStoreOp overground::fromString<vk::AttachmentStoreOp>(std::string_view rhs)
{
  static initializer_list<vk::AttachmentStoreOp> il = {
    vk::AttachmentStoreOp::eStore,
    vk::AttachmentStoreOp::eDontCare,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}AttachmentStoreOp{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::BlendFactor overground::fromString<vk::BlendFactor>(std::string_view rhs)
{
  static initializer_list<vk::BlendFactor> il = {
    vk::BlendFactor::eZero,
    vk::BlendFactor::eOne,
    vk::BlendFactor::eSrcColor,
    vk::BlendFactor::eOneMinusSrcColor,
    vk::BlendFactor::eDstColor,
    vk::BlendFactor::eOneMinusDstColor,
    vk::BlendFactor::eSrcAlpha,
    vk::BlendFactor::eOneMinusSrcAlpha,
    vk::BlendFactor::eDstAlpha,
    vk::BlendFactor::eOneMinusDstAlpha,
    vk::BlendFactor::eConstantColor,
    vk::BlendFactor::eOneMinusConstantColor,
    vk::BlendFactor::eConstantAlpha,
    vk::BlendFactor::eOneMinusConstantAlpha,
    vk::BlendFactor::eSrcAlphaSaturate,
    vk::BlendFactor::eSrc1Color,
    vk::BlendFactor::eOneMinusSrc1Color,
    vk::BlendFactor::eSrc1Alpha,
    vk::BlendFactor::eOneMinusSrc1Alpha,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BlendFactor{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::BlendOp overground::fromString<vk::BlendOp>(std::string_view rhs)
{
  static initializer_list<vk::BlendOp> il = {
    vk::BlendOp::eAdd,
    vk::BlendOp::eSubtract,
    vk::BlendOp::eReverseSubtract,
    vk::BlendOp::eMin,
    vk::BlendOp::eMax,
    vk::BlendOp::eZeroEXT,
    vk::BlendOp::eSrcEXT,
    vk::BlendOp::eDstEXT,
    vk::BlendOp::eSrcOverEXT,
    vk::BlendOp::eDstOverEXT,
    vk::BlendOp::eSrcInEXT,
    vk::BlendOp::eDstInEXT,
    vk::BlendOp::eSrcOutEXT,
    vk::BlendOp::eDstOutEXT,
    vk::BlendOp::eSrcAtopEXT,
    vk::BlendOp::eDstAtopEXT,
    vk::BlendOp::eXorEXT,
    vk::BlendOp::eMultiplyEXT,
    vk::BlendOp::eScreenEXT,
    vk::BlendOp::eOverlayEXT,
    vk::BlendOp::eDarkenEXT,
    vk::BlendOp::eLightenEXT,
    vk::BlendOp::eColordodgeEXT,
    vk::BlendOp::eColorburnEXT,
    vk::BlendOp::eHardlightEXT,
    vk::BlendOp::eSoftlightEXT,
    vk::BlendOp::eDifferenceEXT,
    vk::BlendOp::eExclusionEXT,
    vk::BlendOp::eInvertEXT,
    vk::BlendOp::eInvertRgbEXT,
    vk::BlendOp::eLineardodgeEXT,
    vk::BlendOp::eLinearburnEXT,
    vk::BlendOp::eVividlightEXT,
    vk::BlendOp::eLinearlightEXT,
    vk::BlendOp::ePinlightEXT,
    vk::BlendOp::eHardmixEXT,
    vk::BlendOp::eHslHueEXT,
    vk::BlendOp::eHslSaturationEXT,
    vk::BlendOp::eHslColorEXT,
    vk::BlendOp::eHslLuminosityEXT,
    vk::BlendOp::ePlusEXT,
    vk::BlendOp::ePlusClampedEXT,
    vk::BlendOp::ePlusClampedAlphaEXT,
    vk::BlendOp::ePlusDarkerEXT,
    vk::BlendOp::eMinusEXT,
    vk::BlendOp::eMinusClampedEXT,
    vk::BlendOp::eContrastEXT,
    vk::BlendOp::eInvertOvgEXT,
    vk::BlendOp::eRedEXT,
    vk::BlendOp::eGreenEXT,
    vk::BlendOp::eBlueEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BlendOp{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::BlendOverlapEXT overground::fromString<vk::BlendOverlapEXT>(std::string_view rhs)
{
  static initializer_list<vk::BlendOverlapEXT> il = {
    vk::BlendOverlapEXT::eUncorrelated,
    vk::BlendOverlapEXT::eDisjoint,
    vk::BlendOverlapEXT::eConjoint,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BlendOverlapEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::BorderColor overground::fromString<vk::BorderColor>(std::string_view rhs)
{
  static initializer_list<vk::BorderColor> il = {
    vk::BorderColor::eFloatTransparentBlack,
    vk::BorderColor::eIntTransparentBlack,
    vk::BorderColor::eFloatOpaqueBlack,
    vk::BorderColor::eIntOpaqueBlack,
    vk::BorderColor::eFloatOpaqueWhite,
    vk::BorderColor::eIntOpaqueWhite,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BorderColor{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::BufferCreateFlagBits overground::fromString<vk::BufferCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::BufferCreateFlagBits> il = {
    vk::BufferCreateFlagBits::eSparseBinding,
    vk::BufferCreateFlagBits::eSparseResidency,
    vk::BufferCreateFlagBits::eSparseAliased,
    vk::BufferCreateFlagBits::eProtected,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BufferCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::BufferUsageFlagBits overground::fromString<vk::BufferUsageFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::BufferUsageFlagBits> il = {
    vk::BufferUsageFlagBits::eTransferSrc,
    vk::BufferUsageFlagBits::eTransferDst,
    vk::BufferUsageFlagBits::eUniformTexelBuffer,
    vk::BufferUsageFlagBits::eStorageTexelBuffer,
    vk::BufferUsageFlagBits::eUniformBuffer,
    vk::BufferUsageFlagBits::eStorageBuffer,
    vk::BufferUsageFlagBits::eIndexBuffer,
    vk::BufferUsageFlagBits::eVertexBuffer,
    vk::BufferUsageFlagBits::eIndirectBuffer,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BufferUsageFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ChromaLocation overground::fromString<vk::ChromaLocation>(std::string_view rhs)
{
  static initializer_list<vk::ChromaLocation> il = {
    vk::ChromaLocation::eCositedEven,
    vk::ChromaLocation::eMidpoint,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ChromaLocation{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ColorComponentFlagBits overground::fromString<vk::ColorComponentFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ColorComponentFlagBits> il = {
    vk::ColorComponentFlagBits::eR,
    vk::ColorComponentFlagBits::eG,
    vk::ColorComponentFlagBits::eB,
    vk::ColorComponentFlagBits::eA,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ColorComponentFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ColorSpaceKHR overground::fromString<vk::ColorSpaceKHR>(std::string_view rhs)
{
  static initializer_list<vk::ColorSpaceKHR> il = {
    vk::ColorSpaceKHR::eSrgbNonlinear,
    vk::ColorSpaceKHR::eDisplayP3NonlinearEXT,
    vk::ColorSpaceKHR::eExtendedSrgbLinearEXT,
    vk::ColorSpaceKHR::eDciP3LinearEXT,
    vk::ColorSpaceKHR::eDciP3NonlinearEXT,
    vk::ColorSpaceKHR::eBt709LinearEXT,
    vk::ColorSpaceKHR::eBt709NonlinearEXT,
    vk::ColorSpaceKHR::eBt2020LinearEXT,
    vk::ColorSpaceKHR::eHdr10St2084EXT,
    vk::ColorSpaceKHR::eDolbyvisionEXT,
    vk::ColorSpaceKHR::eHdr10HlgEXT,
    vk::ColorSpaceKHR::eAdobergbLinearEXT,
    vk::ColorSpaceKHR::eAdobergbNonlinearEXT,
    vk::ColorSpaceKHR::ePassThroughEXT,
    vk::ColorSpaceKHR::eExtendedSrgbNonlinearEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ColorSpaceKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CommandBufferLevel overground::fromString<vk::CommandBufferLevel>(std::string_view rhs)
{
  static initializer_list<vk::CommandBufferLevel> il = {
    vk::CommandBufferLevel::ePrimary,
    vk::CommandBufferLevel::eSecondary,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CommandBufferLevel{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CommandBufferResetFlagBits overground::fromString<vk::CommandBufferResetFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::CommandBufferResetFlagBits> il = {
    vk::CommandBufferResetFlagBits::eReleaseResources,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CommandBufferResetFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CommandBufferUsageFlagBits overground::fromString<vk::CommandBufferUsageFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::CommandBufferUsageFlagBits> il = {
    vk::CommandBufferUsageFlagBits::eOneTimeSubmit,
    vk::CommandBufferUsageFlagBits::eRenderPassContinue,
    vk::CommandBufferUsageFlagBits::eSimultaneousUse,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CommandBufferUsageFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CommandPoolCreateFlagBits overground::fromString<vk::CommandPoolCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::CommandPoolCreateFlagBits> il = {
    vk::CommandPoolCreateFlagBits::eTransient,
    vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
    vk::CommandPoolCreateFlagBits::eProtected,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CommandPoolCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CommandPoolResetFlagBits overground::fromString<vk::CommandPoolResetFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::CommandPoolResetFlagBits> il = {
    vk::CommandPoolResetFlagBits::eReleaseResources,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CommandPoolResetFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CompareOp overground::fromString<vk::CompareOp>(std::string_view rhs)
{
  static initializer_list<vk::CompareOp> il = {
    vk::CompareOp::eNever,
    vk::CompareOp::eLess,
    vk::CompareOp::eEqual,
    vk::CompareOp::eLessOrEqual,
    vk::CompareOp::eGreater,
    vk::CompareOp::eNotEqual,
    vk::CompareOp::eGreaterOrEqual,
    vk::CompareOp::eAlways,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CompareOp{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ComponentSwizzle overground::fromString<vk::ComponentSwizzle>(std::string_view rhs)
{
  static initializer_list<vk::ComponentSwizzle> il = {
    vk::ComponentSwizzle::eIdentity,
    vk::ComponentSwizzle::eZero,
    vk::ComponentSwizzle::eOne,
    vk::ComponentSwizzle::eR,
    vk::ComponentSwizzle::eG,
    vk::ComponentSwizzle::eB,
    vk::ComponentSwizzle::eA,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ComponentSwizzle{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CompositeAlphaFlagBitsKHR overground::fromString<vk::CompositeAlphaFlagBitsKHR>(std::string_view rhs)
{
  static initializer_list<vk::CompositeAlphaFlagBitsKHR> il = {
    vk::CompositeAlphaFlagBitsKHR::eOpaque,
    vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
    vk::CompositeAlphaFlagBitsKHR::ePostMultiplied,
    vk::CompositeAlphaFlagBitsKHR::eInherit,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CompositeAlphaFlagBitsKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ConservativeRasterizationModeEXT overground::fromString<vk::ConservativeRasterizationModeEXT>(std::string_view rhs)
{
  static initializer_list<vk::ConservativeRasterizationModeEXT> il = {
    vk::ConservativeRasterizationModeEXT::eDisabled,
    vk::ConservativeRasterizationModeEXT::eOverestimate,
    vk::ConservativeRasterizationModeEXT::eUnderestimate,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ConservativeRasterizationModeEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CoverageModulationModeNV overground::fromString<vk::CoverageModulationModeNV>(std::string_view rhs)
{
  static initializer_list<vk::CoverageModulationModeNV> il = {
    vk::CoverageModulationModeNV::eNone,
    vk::CoverageModulationModeNV::eRgb,
    vk::CoverageModulationModeNV::eAlpha,
    vk::CoverageModulationModeNV::eRgba,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CoverageModulationModeNV{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::CullModeFlagBits overground::fromString<vk::CullModeFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::CullModeFlagBits> il = {
    vk::CullModeFlagBits::eNone,
    vk::CullModeFlagBits::eFront,
    vk::CullModeFlagBits::eBack,
    vk::CullModeFlagBits::eFrontAndBack,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}CullModeFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DebugReportFlagBitsEXT overground::fromString<vk::DebugReportFlagBitsEXT>(std::string_view rhs)
{
  static initializer_list<vk::DebugReportFlagBitsEXT> il = {
    vk::DebugReportFlagBitsEXT::eInformation,
    vk::DebugReportFlagBitsEXT::eWarning,
    vk::DebugReportFlagBitsEXT::ePerformanceWarning,
    vk::DebugReportFlagBitsEXT::eError,
    vk::DebugReportFlagBitsEXT::eDebug,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DebugReportFlagBitsEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DebugReportObjectTypeEXT overground::fromString<vk::DebugReportObjectTypeEXT>(std::string_view rhs)
{
  static initializer_list<vk::DebugReportObjectTypeEXT> il = {
    vk::DebugReportObjectTypeEXT::eUnknown,
    vk::DebugReportObjectTypeEXT::eInstance,
    vk::DebugReportObjectTypeEXT::ePhysicalDevice,
    vk::DebugReportObjectTypeEXT::eDevice,
    vk::DebugReportObjectTypeEXT::eQueue,
    vk::DebugReportObjectTypeEXT::eSemaphore,
    vk::DebugReportObjectTypeEXT::eCommandBuffer,
    vk::DebugReportObjectTypeEXT::eFence,
    vk::DebugReportObjectTypeEXT::eDeviceMemory,
    vk::DebugReportObjectTypeEXT::eBuffer,
    vk::DebugReportObjectTypeEXT::eImage,
    vk::DebugReportObjectTypeEXT::eEvent,
    vk::DebugReportObjectTypeEXT::eQueryPool,
    vk::DebugReportObjectTypeEXT::eBufferView,
    vk::DebugReportObjectTypeEXT::eImageView,
    vk::DebugReportObjectTypeEXT::eShaderModule,
    vk::DebugReportObjectTypeEXT::ePipelineCache,
    vk::DebugReportObjectTypeEXT::ePipelineLayout,
    vk::DebugReportObjectTypeEXT::eRenderPass,
    vk::DebugReportObjectTypeEXT::ePipeline,
    vk::DebugReportObjectTypeEXT::eDescriptorSetLayout,
    vk::DebugReportObjectTypeEXT::eSampler,
    vk::DebugReportObjectTypeEXT::eDescriptorPool,
    vk::DebugReportObjectTypeEXT::eDescriptorSet,
    vk::DebugReportObjectTypeEXT::eFramebuffer,
    vk::DebugReportObjectTypeEXT::eCommandPool,
    vk::DebugReportObjectTypeEXT::eSurfaceKhr,
    vk::DebugReportObjectTypeEXT::eSwapchainKhr,
    vk::DebugReportObjectTypeEXT::eDebugReportCallbackExt,
    vk::DebugReportObjectTypeEXT::eDisplayKhr,
    vk::DebugReportObjectTypeEXT::eDisplayModeKhr,
    vk::DebugReportObjectTypeEXT::eObjectTableNvx,
    vk::DebugReportObjectTypeEXT::eIndirectCommandsLayoutNvx,
    vk::DebugReportObjectTypeEXT::eValidationCacheExt,
    vk::DebugReportObjectTypeEXT::eSamplerYcbcrConversion,
    vk::DebugReportObjectTypeEXT::eDescriptorUpdateTemplate,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DebugReportObjectTypeEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DebugUtilsMessageSeverityFlagBitsEXT overground::fromString<vk::DebugUtilsMessageSeverityFlagBitsEXT>(std::string_view rhs)
{
  static initializer_list<vk::DebugUtilsMessageSeverityFlagBitsEXT> il = {
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DebugUtilsMessageSeverityFlagBitsEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DebugUtilsMessageTypeFlagBitsEXT overground::fromString<vk::DebugUtilsMessageTypeFlagBitsEXT>(std::string_view rhs)
{
  static initializer_list<vk::DebugUtilsMessageTypeFlagBitsEXT> il = {
    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral,
    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DebugUtilsMessageTypeFlagBitsEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DependencyFlagBits overground::fromString<vk::DependencyFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::DependencyFlagBits> il = {
    vk::DependencyFlagBits::eByRegion,
    vk::DependencyFlagBits::eDeviceGroup,
    vk::DependencyFlagBits::eViewLocal,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DependencyFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DescriptorBindingFlagBitsEXT overground::fromString<vk::DescriptorBindingFlagBitsEXT>(std::string_view rhs)
{
  static initializer_list<vk::DescriptorBindingFlagBitsEXT> il = {
    vk::DescriptorBindingFlagBitsEXT::eUpdateAfterBind,
    vk::DescriptorBindingFlagBitsEXT::eUpdateUnusedWhilePending,
    vk::DescriptorBindingFlagBitsEXT::ePartiallyBound,
    vk::DescriptorBindingFlagBitsEXT::eVariableDescriptorCount,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DescriptorBindingFlagBitsEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DescriptorPoolCreateFlagBits overground::fromString<vk::DescriptorPoolCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::DescriptorPoolCreateFlagBits> il = {
    vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
    vk::DescriptorPoolCreateFlagBits::eUpdateAfterBindEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DescriptorPoolCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DescriptorSetLayoutCreateFlagBits overground::fromString<vk::DescriptorSetLayoutCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::DescriptorSetLayoutCreateFlagBits> il = {
    vk::DescriptorSetLayoutCreateFlagBits::ePushDescriptorKHR,
    vk::DescriptorSetLayoutCreateFlagBits::eUpdateAfterBindPoolEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DescriptorSetLayoutCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DescriptorType overground::fromString<vk::DescriptorType>(std::string_view rhs)
{
  static initializer_list<vk::DescriptorType> il = {
    vk::DescriptorType::eSampler,
    vk::DescriptorType::eCombinedImageSampler,
    vk::DescriptorType::eSampledImage,
    vk::DescriptorType::eStorageImage,
    vk::DescriptorType::eUniformTexelBuffer,
    vk::DescriptorType::eStorageTexelBuffer,
    vk::DescriptorType::eUniformBuffer,
    vk::DescriptorType::eStorageBuffer,
    vk::DescriptorType::eUniformBufferDynamic,
    vk::DescriptorType::eStorageBufferDynamic,
    vk::DescriptorType::eInputAttachment,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DescriptorType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DescriptorUpdateTemplateType overground::fromString<vk::DescriptorUpdateTemplateType>(std::string_view rhs)
{
  static initializer_list<vk::DescriptorUpdateTemplateType> il = {
    vk::DescriptorUpdateTemplateType::eDescriptorSet,
    vk::DescriptorUpdateTemplateType::ePushDescriptorsKHR,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DescriptorUpdateTemplateType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DeviceEventTypeEXT overground::fromString<vk::DeviceEventTypeEXT>(std::string_view rhs)
{
  static initializer_list<vk::DeviceEventTypeEXT> il = {
    vk::DeviceEventTypeEXT::eDisplayHotplug,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DeviceEventTypeEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DeviceGroupPresentModeFlagBitsKHR overground::fromString<vk::DeviceGroupPresentModeFlagBitsKHR>(std::string_view rhs)
{
  static initializer_list<vk::DeviceGroupPresentModeFlagBitsKHR> il = {
    vk::DeviceGroupPresentModeFlagBitsKHR::eLocal,
    vk::DeviceGroupPresentModeFlagBitsKHR::eRemote,
    vk::DeviceGroupPresentModeFlagBitsKHR::eSum,
    vk::DeviceGroupPresentModeFlagBitsKHR::eLocalMultiDevice,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DeviceGroupPresentModeFlagBitsKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DeviceQueueCreateFlagBits overground::fromString<vk::DeviceQueueCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::DeviceQueueCreateFlagBits> il = {
    vk::DeviceQueueCreateFlagBits::eProtected,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DeviceQueueCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DiscardRectangleModeEXT overground::fromString<vk::DiscardRectangleModeEXT>(std::string_view rhs)
{
  static initializer_list<vk::DiscardRectangleModeEXT> il = {
    vk::DiscardRectangleModeEXT::eInclusive,
    vk::DiscardRectangleModeEXT::eExclusive,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DiscardRectangleModeEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DisplayEventTypeEXT overground::fromString<vk::DisplayEventTypeEXT>(std::string_view rhs)
{
  static initializer_list<vk::DisplayEventTypeEXT> il = {
    vk::DisplayEventTypeEXT::eFirstPixelOut,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DisplayEventTypeEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DisplayPlaneAlphaFlagBitsKHR overground::fromString<vk::DisplayPlaneAlphaFlagBitsKHR>(std::string_view rhs)
{
  static initializer_list<vk::DisplayPlaneAlphaFlagBitsKHR> il = {
    vk::DisplayPlaneAlphaFlagBitsKHR::eOpaque,
    vk::DisplayPlaneAlphaFlagBitsKHR::eGlobal,
    vk::DisplayPlaneAlphaFlagBitsKHR::ePerPixel,
    vk::DisplayPlaneAlphaFlagBitsKHR::ePerPixelPremultiplied,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DisplayPlaneAlphaFlagBitsKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DisplayPowerStateEXT overground::fromString<vk::DisplayPowerStateEXT>(std::string_view rhs)
{
  static initializer_list<vk::DisplayPowerStateEXT> il = {
    vk::DisplayPowerStateEXT::eOff,
    vk::DisplayPowerStateEXT::eSuspend,
    vk::DisplayPowerStateEXT::eOn,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DisplayPowerStateEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::DynamicState overground::fromString<vk::DynamicState>(std::string_view rhs)
{
  static initializer_list<vk::DynamicState> il = {
    vk::DynamicState::eViewport,
    vk::DynamicState::eScissor,
    vk::DynamicState::eLineWidth,
    vk::DynamicState::eDepthBias,
    vk::DynamicState::eBlendConstants,
    vk::DynamicState::eDepthBounds,
    vk::DynamicState::eStencilCompareMask,
    vk::DynamicState::eStencilWriteMask,
    vk::DynamicState::eStencilReference,
    vk::DynamicState::eViewportWScalingNV,
    vk::DynamicState::eDiscardRectangleEXT,
    vk::DynamicState::eSampleLocationsEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}DynamicState{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalFenceFeatureFlagBits overground::fromString<vk::ExternalFenceFeatureFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ExternalFenceFeatureFlagBits> il = {
    vk::ExternalFenceFeatureFlagBits::eExportable,
    vk::ExternalFenceFeatureFlagBits::eImportable,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalFenceFeatureFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalFenceHandleTypeFlagBits overground::fromString<vk::ExternalFenceHandleTypeFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ExternalFenceHandleTypeFlagBits> il = {
    vk::ExternalFenceHandleTypeFlagBits::eOpaqueFd,
    vk::ExternalFenceHandleTypeFlagBits::eOpaqueWin32,
    vk::ExternalFenceHandleTypeFlagBits::eOpaqueWin32Kmt,
    vk::ExternalFenceHandleTypeFlagBits::eSyncFd,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalFenceHandleTypeFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalMemoryFeatureFlagBits overground::fromString<vk::ExternalMemoryFeatureFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ExternalMemoryFeatureFlagBits> il = {
    vk::ExternalMemoryFeatureFlagBits::eDedicatedOnly,
    vk::ExternalMemoryFeatureFlagBits::eExportable,
    vk::ExternalMemoryFeatureFlagBits::eImportable,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalMemoryFeatureFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalMemoryFeatureFlagBitsNV overground::fromString<vk::ExternalMemoryFeatureFlagBitsNV>(std::string_view rhs)
{
  static initializer_list<vk::ExternalMemoryFeatureFlagBitsNV> il = {
    vk::ExternalMemoryFeatureFlagBitsNV::eDedicatedOnly,
    vk::ExternalMemoryFeatureFlagBitsNV::eExportable,
    vk::ExternalMemoryFeatureFlagBitsNV::eImportable,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalMemoryFeatureFlagBitsNV{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalMemoryFeatureFlagsNV overground::fromString<vk::ExternalMemoryFeatureFlagsNV>(std::string_view rhs)
{
  static initializer_list<vk::ExternalMemoryFeatureFlagsNV> il = {
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalMemoryFeatureFlagsNV{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalMemoryHandleTypeFlagBits overground::fromString<vk::ExternalMemoryHandleTypeFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ExternalMemoryHandleTypeFlagBits> il = {
    vk::ExternalMemoryHandleTypeFlagBits::eOpaqueFd,
    vk::ExternalMemoryHandleTypeFlagBits::eOpaqueWin32,
    vk::ExternalMemoryHandleTypeFlagBits::eOpaqueWin32Kmt,
    vk::ExternalMemoryHandleTypeFlagBits::eD3D11Texture,
    vk::ExternalMemoryHandleTypeFlagBits::eD3D11TextureKmt,
    vk::ExternalMemoryHandleTypeFlagBits::eD3D12Heap,
    vk::ExternalMemoryHandleTypeFlagBits::eD3D12Resource,
    vk::ExternalMemoryHandleTypeFlagBits::eDmaBufEXT,
    vk::ExternalMemoryHandleTypeFlagBits::eAndroidHardwareBufferANDROID,
    vk::ExternalMemoryHandleTypeFlagBits::eHostAllocationEXT,
    vk::ExternalMemoryHandleTypeFlagBits::eHostMappedForeignMemoryEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalMemoryHandleTypeFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalMemoryHandleTypeFlagBitsNV overground::fromString<vk::ExternalMemoryHandleTypeFlagBitsNV>(std::string_view rhs)
{
  static initializer_list<vk::ExternalMemoryHandleTypeFlagBitsNV> il = {
    vk::ExternalMemoryHandleTypeFlagBitsNV::eOpaqueWin32,
    vk::ExternalMemoryHandleTypeFlagBitsNV::eOpaqueWin32Kmt,
    vk::ExternalMemoryHandleTypeFlagBitsNV::eD3D11Image,
    vk::ExternalMemoryHandleTypeFlagBitsNV::eD3D11ImageKmt,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalMemoryHandleTypeFlagBitsNV{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalMemoryHandleTypeFlagsNV overground::fromString<vk::ExternalMemoryHandleTypeFlagsNV>(std::string_view rhs)
{
  static initializer_list<vk::ExternalMemoryHandleTypeFlagsNV> il = {
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalMemoryHandleTypeFlagsNV{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalSemaphoreFeatureFlagBits overground::fromString<vk::ExternalSemaphoreFeatureFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ExternalSemaphoreFeatureFlagBits> il = {
    vk::ExternalSemaphoreFeatureFlagBits::eExportable,
    vk::ExternalSemaphoreFeatureFlagBits::eImportable,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalSemaphoreFeatureFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ExternalSemaphoreHandleTypeFlagBits overground::fromString<vk::ExternalSemaphoreHandleTypeFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ExternalSemaphoreHandleTypeFlagBits> il = {
    vk::ExternalSemaphoreHandleTypeFlagBits::eOpaqueFd,
    vk::ExternalSemaphoreHandleTypeFlagBits::eOpaqueWin32,
    vk::ExternalSemaphoreHandleTypeFlagBits::eOpaqueWin32Kmt,
    vk::ExternalSemaphoreHandleTypeFlagBits::eD3D12Fence,
    vk::ExternalSemaphoreHandleTypeFlagBits::eSyncFd,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ExternalSemaphoreHandleTypeFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::FenceCreateFlagBits overground::fromString<vk::FenceCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::FenceCreateFlagBits> il = {
    vk::FenceCreateFlagBits::eSignaled,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}FenceCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::FenceImportFlagBits overground::fromString<vk::FenceImportFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::FenceImportFlagBits> il = {
    vk::FenceImportFlagBits::eTemporary,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}FenceImportFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::Filter overground::fromString<vk::Filter>(std::string_view rhs)
{
  static initializer_list<vk::Filter> il = {
    vk::Filter::eNearest,
    vk::Filter::eLinear,
    vk::Filter::eCubicIMG,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}Filter{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::Format overground::fromString<vk::Format>(std::string_view rhs)
{
  static initializer_list<vk::Format> il = {
    vk::Format::eUndefined,
    vk::Format::eR4G4UnormPack8,
    vk::Format::eR4G4B4A4UnormPack16,
    vk::Format::eB4G4R4A4UnormPack16,
    vk::Format::eR5G6B5UnormPack16,
    vk::Format::eB5G6R5UnormPack16,
    vk::Format::eR5G5B5A1UnormPack16,
    vk::Format::eB5G5R5A1UnormPack16,
    vk::Format::eA1R5G5B5UnormPack16,
    vk::Format::eR8Unorm,
    vk::Format::eR8Snorm,
    vk::Format::eR8Uscaled,
    vk::Format::eR8Sscaled,
    vk::Format::eR8Uint,
    vk::Format::eR8Sint,
    vk::Format::eR8Srgb,
    vk::Format::eR8G8Unorm,
    vk::Format::eR8G8Snorm,
    vk::Format::eR8G8Uscaled,
    vk::Format::eR8G8Sscaled,
    vk::Format::eR8G8Uint,
    vk::Format::eR8G8Sint,
    vk::Format::eR8G8Srgb,
    vk::Format::eR8G8B8Unorm,
    vk::Format::eR8G8B8Snorm,
    vk::Format::eR8G8B8Uscaled,
    vk::Format::eR8G8B8Sscaled,
    vk::Format::eR8G8B8Uint,
    vk::Format::eR8G8B8Sint,
    vk::Format::eR8G8B8Srgb,
    vk::Format::eB8G8R8Unorm,
    vk::Format::eB8G8R8Snorm,
    vk::Format::eB8G8R8Uscaled,
    vk::Format::eB8G8R8Sscaled,
    vk::Format::eB8G8R8Uint,
    vk::Format::eB8G8R8Sint,
    vk::Format::eB8G8R8Srgb,
    vk::Format::eR8G8B8A8Unorm,
    vk::Format::eR8G8B8A8Snorm,
    vk::Format::eR8G8B8A8Uscaled,
    vk::Format::eR8G8B8A8Sscaled,
    vk::Format::eR8G8B8A8Uint,
    vk::Format::eR8G8B8A8Sint,
    vk::Format::eR8G8B8A8Srgb,
    vk::Format::eB8G8R8A8Unorm,
    vk::Format::eB8G8R8A8Snorm,
    vk::Format::eB8G8R8A8Uscaled,
    vk::Format::eB8G8R8A8Sscaled,
    vk::Format::eB8G8R8A8Uint,
    vk::Format::eB8G8R8A8Sint,
    vk::Format::eB8G8R8A8Srgb,
    vk::Format::eA8B8G8R8UnormPack32,
    vk::Format::eA8B8G8R8SnormPack32,
    vk::Format::eA8B8G8R8UscaledPack32,
    vk::Format::eA8B8G8R8SscaledPack32,
    vk::Format::eA8B8G8R8UintPack32,
    vk::Format::eA8B8G8R8SintPack32,
    vk::Format::eA8B8G8R8SrgbPack32,
    vk::Format::eA2R10G10B10UnormPack32,
    vk::Format::eA2R10G10B10SnormPack32,
    vk::Format::eA2R10G10B10UscaledPack32,
    vk::Format::eA2R10G10B10SscaledPack32,
    vk::Format::eA2R10G10B10UintPack32,
    vk::Format::eA2R10G10B10SintPack32,
    vk::Format::eA2B10G10R10UnormPack32,
    vk::Format::eA2B10G10R10SnormPack32,
    vk::Format::eA2B10G10R10UscaledPack32,
    vk::Format::eA2B10G10R10SscaledPack32,
    vk::Format::eA2B10G10R10UintPack32,
    vk::Format::eA2B10G10R10SintPack32,
    vk::Format::eR16Unorm,
    vk::Format::eR16Snorm,
    vk::Format::eR16Uscaled,
    vk::Format::eR16Sscaled,
    vk::Format::eR16Uint,
    vk::Format::eR16Sint,
    vk::Format::eR16Sfloat,
    vk::Format::eR16G16Unorm,
    vk::Format::eR16G16Snorm,
    vk::Format::eR16G16Uscaled,
    vk::Format::eR16G16Sscaled,
    vk::Format::eR16G16Uint,
    vk::Format::eR16G16Sint,
    vk::Format::eR16G16Sfloat,
    vk::Format::eR16G16B16Unorm,
    vk::Format::eR16G16B16Snorm,
    vk::Format::eR16G16B16Uscaled,
    vk::Format::eR16G16B16Sscaled,
    vk::Format::eR16G16B16Uint,
    vk::Format::eR16G16B16Sint,
    vk::Format::eR16G16B16Sfloat,
    vk::Format::eR16G16B16A16Unorm,
    vk::Format::eR16G16B16A16Snorm,
    vk::Format::eR16G16B16A16Uscaled,
    vk::Format::eR16G16B16A16Sscaled,
    vk::Format::eR16G16B16A16Uint,
    vk::Format::eR16G16B16A16Sint,
    vk::Format::eR16G16B16A16Sfloat,
    vk::Format::eR32Uint,
    vk::Format::eR32Sint,
    vk::Format::eR32Sfloat,
    vk::Format::eR32G32Uint,
    vk::Format::eR32G32Sint,
    vk::Format::eR32G32Sfloat,
    vk::Format::eR32G32B32Uint,
    vk::Format::eR32G32B32Sint,
    vk::Format::eR32G32B32Sfloat,
    vk::Format::eR32G32B32A32Uint,
    vk::Format::eR32G32B32A32Sint,
    vk::Format::eR32G32B32A32Sfloat,
    vk::Format::eR64Uint,
    vk::Format::eR64Sint,
    vk::Format::eR64Sfloat,
    vk::Format::eR64G64Uint,
    vk::Format::eR64G64Sint,
    vk::Format::eR64G64Sfloat,
    vk::Format::eR64G64B64Uint,
    vk::Format::eR64G64B64Sint,
    vk::Format::eR64G64B64Sfloat,
    vk::Format::eR64G64B64A64Uint,
    vk::Format::eR64G64B64A64Sint,
    vk::Format::eR64G64B64A64Sfloat,
    vk::Format::eB10G11R11UfloatPack32,
    vk::Format::eE5B9G9R9UfloatPack32,
    vk::Format::eD16Unorm,
    vk::Format::eX8D24UnormPack32,
    vk::Format::eD32Sfloat,
    vk::Format::eS8Uint,
    vk::Format::eD16UnormS8Uint,
    vk::Format::eD24UnormS8Uint,
    vk::Format::eD32SfloatS8Uint,
    vk::Format::eBc1RgbUnormBlock,
    vk::Format::eBc1RgbSrgbBlock,
    vk::Format::eBc1RgbaUnormBlock,
    vk::Format::eBc1RgbaSrgbBlock,
    vk::Format::eBc2UnormBlock,
    vk::Format::eBc2SrgbBlock,
    vk::Format::eBc3UnormBlock,
    vk::Format::eBc3SrgbBlock,
    vk::Format::eBc4UnormBlock,
    vk::Format::eBc4SnormBlock,
    vk::Format::eBc5UnormBlock,
    vk::Format::eBc5SnormBlock,
    vk::Format::eBc6HUfloatBlock,
    vk::Format::eBc6HSfloatBlock,
    vk::Format::eBc7UnormBlock,
    vk::Format::eBc7SrgbBlock,
    vk::Format::eEtc2R8G8B8UnormBlock,
    vk::Format::eEtc2R8G8B8SrgbBlock,
    vk::Format::eEtc2R8G8B8A1UnormBlock,
    vk::Format::eEtc2R8G8B8A1SrgbBlock,
    vk::Format::eEtc2R8G8B8A8UnormBlock,
    vk::Format::eEtc2R8G8B8A8SrgbBlock,
    vk::Format::eEacR11UnormBlock,
    vk::Format::eEacR11SnormBlock,
    vk::Format::eEacR11G11UnormBlock,
    vk::Format::eEacR11G11SnormBlock,
    vk::Format::eAstc4x4UnormBlock,
    vk::Format::eAstc4x4SrgbBlock,
    vk::Format::eAstc5x4UnormBlock,
    vk::Format::eAstc5x4SrgbBlock,
    vk::Format::eAstc5x5UnormBlock,
    vk::Format::eAstc5x5SrgbBlock,
    vk::Format::eAstc6x5UnormBlock,
    vk::Format::eAstc6x5SrgbBlock,
    vk::Format::eAstc6x6UnormBlock,
    vk::Format::eAstc6x6SrgbBlock,
    vk::Format::eAstc8x5UnormBlock,
    vk::Format::eAstc8x5SrgbBlock,
    vk::Format::eAstc8x6UnormBlock,
    vk::Format::eAstc8x6SrgbBlock,
    vk::Format::eAstc8x8UnormBlock,
    vk::Format::eAstc8x8SrgbBlock,
    vk::Format::eAstc10x5UnormBlock,
    vk::Format::eAstc10x5SrgbBlock,
    vk::Format::eAstc10x6UnormBlock,
    vk::Format::eAstc10x6SrgbBlock,
    vk::Format::eAstc10x8UnormBlock,
    vk::Format::eAstc10x8SrgbBlock,
    vk::Format::eAstc10x10UnormBlock,
    vk::Format::eAstc10x10SrgbBlock,
    vk::Format::eAstc12x10UnormBlock,
    vk::Format::eAstc12x10SrgbBlock,
    vk::Format::eAstc12x12UnormBlock,
    vk::Format::eAstc12x12SrgbBlock,
    vk::Format::eG8B8G8R8422Unorm,
    vk::Format::eB8G8R8G8422Unorm,
    vk::Format::eG8B8R83Plane420Unorm,
    vk::Format::eG8B8R82Plane420Unorm,
    vk::Format::eG8B8R83Plane422Unorm,
    vk::Format::eG8B8R82Plane422Unorm,
    vk::Format::eG8B8R83Plane444Unorm,
    vk::Format::eR10X6UnormPack16,
    vk::Format::eR10X6G10X6Unorm2Pack16,
    vk::Format::eR10X6G10X6B10X6A10X6Unorm4Pack16,
    vk::Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16,
    vk::Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16,
    vk::Format::eG10X6B10X6R10X63Plane420Unorm3Pack16,
    vk::Format::eG10X6B10X6R10X62Plane420Unorm3Pack16,
    vk::Format::eG10X6B10X6R10X63Plane422Unorm3Pack16,
    vk::Format::eG10X6B10X6R10X62Plane422Unorm3Pack16,
    vk::Format::eG10X6B10X6R10X63Plane444Unorm3Pack16,
    vk::Format::eR12X4UnormPack16,
    vk::Format::eR12X4G12X4Unorm2Pack16,
    vk::Format::eR12X4G12X4B12X4A12X4Unorm4Pack16,
    vk::Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16,
    vk::Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16,
    vk::Format::eG12X4B12X4R12X43Plane420Unorm3Pack16,
    vk::Format::eG12X4B12X4R12X42Plane420Unorm3Pack16,
    vk::Format::eG12X4B12X4R12X43Plane422Unorm3Pack16,
    vk::Format::eG12X4B12X4R12X42Plane422Unorm3Pack16,
    vk::Format::eG12X4B12X4R12X43Plane444Unorm3Pack16,
    vk::Format::eG16B16G16R16422Unorm,
    vk::Format::eB16G16R16G16422Unorm,
    vk::Format::eG16B16R163Plane420Unorm,
    vk::Format::eG16B16R162Plane420Unorm,
    vk::Format::eG16B16R163Plane422Unorm,
    vk::Format::eG16B16R162Plane422Unorm,
    vk::Format::eG16B16R163Plane444Unorm,
    vk::Format::ePvrtc12BppUnormBlockIMG,
    vk::Format::ePvrtc14BppUnormBlockIMG,
    vk::Format::ePvrtc22BppUnormBlockIMG,
    vk::Format::ePvrtc24BppUnormBlockIMG,
    vk::Format::ePvrtc12BppSrgbBlockIMG,
    vk::Format::ePvrtc14BppSrgbBlockIMG,
    vk::Format::ePvrtc22BppSrgbBlockIMG,
    vk::Format::ePvrtc24BppSrgbBlockIMG,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}Format{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::FormatFeatureFlagBits overground::fromString<vk::FormatFeatureFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::FormatFeatureFlagBits> il = {
    vk::FormatFeatureFlagBits::eSampledImage,
    vk::FormatFeatureFlagBits::eStorageImage,
    vk::FormatFeatureFlagBits::eStorageImageAtomic,
    vk::FormatFeatureFlagBits::eUniformTexelBuffer,
    vk::FormatFeatureFlagBits::eStorageTexelBuffer,
    vk::FormatFeatureFlagBits::eStorageTexelBufferAtomic,
    vk::FormatFeatureFlagBits::eVertexBuffer,
    vk::FormatFeatureFlagBits::eColorAttachment,
    vk::FormatFeatureFlagBits::eColorAttachmentBlend,
    vk::FormatFeatureFlagBits::eDepthStencilAttachment,
    vk::FormatFeatureFlagBits::eBlitSrc,
    vk::FormatFeatureFlagBits::eBlitDst,
    vk::FormatFeatureFlagBits::eSampledImageFilterLinear,
    vk::FormatFeatureFlagBits::eTransferSrc,
    vk::FormatFeatureFlagBits::eTransferDst,
    vk::FormatFeatureFlagBits::eMidpointChromaSamples,
    vk::FormatFeatureFlagBits::eSampledImageYcbcrConversionLinearFilter,
    vk::FormatFeatureFlagBits::eSampledImageYcbcrConversionSeparateReconstructionFilter,
    vk::FormatFeatureFlagBits::eSampledImageYcbcrConversionChromaReconstructionExplicit,
    vk::FormatFeatureFlagBits::eSampledImageYcbcrConversionChromaReconstructionExplicitForceable,
    vk::FormatFeatureFlagBits::eDisjoint,
    vk::FormatFeatureFlagBits::eCositedChromaSamples,
    vk::FormatFeatureFlagBits::eSampledImageFilterCubicIMG,
    vk::FormatFeatureFlagBits::eSampledImageFilterMinmaxEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}FormatFeatureFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::FrontFace overground::fromString<vk::FrontFace>(std::string_view rhs)
{
  static initializer_list<vk::FrontFace> il = {
    vk::FrontFace::eCounterClockwise,
    vk::FrontFace::eClockwise,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}FrontFace{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageAspectFlagBits overground::fromString<vk::ImageAspectFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ImageAspectFlagBits> il = {
    vk::ImageAspectFlagBits::eColor,
    vk::ImageAspectFlagBits::eDepth,
    vk::ImageAspectFlagBits::eStencil,
    vk::ImageAspectFlagBits::eMetadata,
    vk::ImageAspectFlagBits::ePlane0,
    vk::ImageAspectFlagBits::ePlane1,
    vk::ImageAspectFlagBits::ePlane2,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageAspectFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageCreateFlagBits overground::fromString<vk::ImageCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ImageCreateFlagBits> il = {
    vk::ImageCreateFlagBits::eSparseBinding,
    vk::ImageCreateFlagBits::eSparseResidency,
    vk::ImageCreateFlagBits::eSparseAliased,
    vk::ImageCreateFlagBits::eMutableFormat,
    vk::ImageCreateFlagBits::eCubeCompatible,
    vk::ImageCreateFlagBits::eAlias,
    vk::ImageCreateFlagBits::eSplitInstanceBindRegions,
    vk::ImageCreateFlagBits::e2DArrayCompatible,
    vk::ImageCreateFlagBits::eBlockTexelViewCompatible,
    vk::ImageCreateFlagBits::eExtendedUsage,
    vk::ImageCreateFlagBits::eProtected,
    vk::ImageCreateFlagBits::eDisjoint,
    vk::ImageCreateFlagBits::eSampleLocationsCompatibleDepthEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageLayout overground::fromString<vk::ImageLayout>(std::string_view rhs)
{
  static initializer_list<vk::ImageLayout> il = {
    vk::ImageLayout::eUndefined,
    vk::ImageLayout::eGeneral,
    vk::ImageLayout::eColorAttachmentOptimal,
    vk::ImageLayout::eDepthStencilAttachmentOptimal,
    vk::ImageLayout::eDepthStencilReadOnlyOptimal,
    vk::ImageLayout::eShaderReadOnlyOptimal,
    vk::ImageLayout::eTransferSrcOptimal,
    vk::ImageLayout::eTransferDstOptimal,
    vk::ImageLayout::ePreinitialized,
    vk::ImageLayout::eDepthReadOnlyStencilAttachmentOptimal,
    vk::ImageLayout::eDepthAttachmentStencilReadOnlyOptimal,
    vk::ImageLayout::ePresentSrcKHR,
    vk::ImageLayout::eSharedPresentKHR,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageLayout{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageTiling overground::fromString<vk::ImageTiling>(std::string_view rhs)
{
  static initializer_list<vk::ImageTiling> il = {
    vk::ImageTiling::eOptimal,
    vk::ImageTiling::eLinear,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageTiling{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageType overground::fromString<vk::ImageType>(std::string_view rhs)
{
  static initializer_list<vk::ImageType> il = {
    vk::ImageType::e1D,
    vk::ImageType::e2D,
    vk::ImageType::e3D,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageUsageFlagBits overground::fromString<vk::ImageUsageFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ImageUsageFlagBits> il = {
    vk::ImageUsageFlagBits::eTransferSrc,
    vk::ImageUsageFlagBits::eTransferDst,
    vk::ImageUsageFlagBits::eSampled,
    vk::ImageUsageFlagBits::eStorage,
    vk::ImageUsageFlagBits::eColorAttachment,
    vk::ImageUsageFlagBits::eDepthStencilAttachment,
    vk::ImageUsageFlagBits::eTransientAttachment,
    vk::ImageUsageFlagBits::eInputAttachment,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageUsageFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ImageViewType overground::fromString<vk::ImageViewType>(std::string_view rhs)
{
  static initializer_list<vk::ImageViewType> il = {
    vk::ImageViewType::e1D,
    vk::ImageViewType::e2D,
    vk::ImageViewType::e3D,
    vk::ImageViewType::eCube,
    vk::ImageViewType::e1DArray,
    vk::ImageViewType::e2DArray,
    vk::ImageViewType::eCubeArray,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ImageViewType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::IndexType overground::fromString<vk::IndexType>(std::string_view rhs)
{
  static initializer_list<vk::IndexType> il = {
    vk::IndexType::eUint16,
    vk::IndexType::eUint32,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}IndexType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::IndirectCommandsLayoutUsageFlagBitsNVX overground::fromString<vk::IndirectCommandsLayoutUsageFlagBitsNVX>(std::string_view rhs)
{
  static initializer_list<vk::IndirectCommandsLayoutUsageFlagBitsNVX> il = {
    vk::IndirectCommandsLayoutUsageFlagBitsNVX::eUnorderedSequences,
    vk::IndirectCommandsLayoutUsageFlagBitsNVX::eSparseSequences,
    vk::IndirectCommandsLayoutUsageFlagBitsNVX::eEmptyExecutions,
    vk::IndirectCommandsLayoutUsageFlagBitsNVX::eIndexedSequences,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}IndirectCommandsLayoutUsageFlagBitsNVX{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::IndirectCommandsLayoutUsageFlagsNVX overground::fromString<vk::IndirectCommandsLayoutUsageFlagsNVX>(std::string_view rhs)
{
  static initializer_list<vk::IndirectCommandsLayoutUsageFlagsNVX> il = {
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}IndirectCommandsLayoutUsageFlagsNVX{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::IndirectCommandsTokenTypeNVX overground::fromString<vk::IndirectCommandsTokenTypeNVX>(std::string_view rhs)
{
  static initializer_list<vk::IndirectCommandsTokenTypeNVX> il = {
    vk::IndirectCommandsTokenTypeNVX::ePipeline,
    vk::IndirectCommandsTokenTypeNVX::eDescriptorSet,
    vk::IndirectCommandsTokenTypeNVX::eIndexBuffer,
    vk::IndirectCommandsTokenTypeNVX::eVertexBuffer,
    vk::IndirectCommandsTokenTypeNVX::ePushConstant,
    vk::IndirectCommandsTokenTypeNVX::eDrawIndexed,
    vk::IndirectCommandsTokenTypeNVX::eDraw,
    vk::IndirectCommandsTokenTypeNVX::eDispatch,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}IndirectCommandsTokenTypeNVX{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::InternalAllocationType overground::fromString<vk::InternalAllocationType>(std::string_view rhs)
{
  static initializer_list<vk::InternalAllocationType> il = {
    vk::InternalAllocationType::eExecutable,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}InternalAllocationType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::LogicOp overground::fromString<vk::LogicOp>(std::string_view rhs)
{
  static initializer_list<vk::LogicOp> il = {
    vk::LogicOp::eClear,
    vk::LogicOp::eAnd,
    vk::LogicOp::eAndReverse,
    vk::LogicOp::eCopy,
    vk::LogicOp::eAndInverted,
    vk::LogicOp::eNoOp,
    vk::LogicOp::eXor,
    vk::LogicOp::eOr,
    vk::LogicOp::eNor,
    vk::LogicOp::eEquivalent,
    vk::LogicOp::eInvert,
    vk::LogicOp::eOrReverse,
    vk::LogicOp::eCopyInverted,
    vk::LogicOp::eOrInverted,
    vk::LogicOp::eNand,
    vk::LogicOp::eSet,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}LogicOp{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::MemoryAllocateFlagBits overground::fromString<vk::MemoryAllocateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::MemoryAllocateFlagBits> il = {
    vk::MemoryAllocateFlagBits::eDeviceMask,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}MemoryAllocateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::MemoryHeapFlagBits overground::fromString<vk::MemoryHeapFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::MemoryHeapFlagBits> il = {
    vk::MemoryHeapFlagBits::eDeviceLocal,
    vk::MemoryHeapFlagBits::eMultiInstance,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}MemoryHeapFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::MemoryPropertyFlagBits overground::fromString<vk::MemoryPropertyFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::MemoryPropertyFlagBits> il = {
    vk::MemoryPropertyFlagBits::eDeviceLocal,
    vk::MemoryPropertyFlagBits::eHostVisible,
    vk::MemoryPropertyFlagBits::eHostCoherent,
    vk::MemoryPropertyFlagBits::eHostCached,
    vk::MemoryPropertyFlagBits::eLazilyAllocated,
    vk::MemoryPropertyFlagBits::eProtected,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}MemoryPropertyFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ObjectEntryTypeNVX overground::fromString<vk::ObjectEntryTypeNVX>(std::string_view rhs)
{
  static initializer_list<vk::ObjectEntryTypeNVX> il = {
    vk::ObjectEntryTypeNVX::eDescriptorSet,
    vk::ObjectEntryTypeNVX::ePipeline,
    vk::ObjectEntryTypeNVX::eIndexBuffer,
    vk::ObjectEntryTypeNVX::eVertexBuffer,
    vk::ObjectEntryTypeNVX::ePushConstant,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ObjectEntryTypeNVX{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ObjectEntryUsageFlagBitsNVX overground::fromString<vk::ObjectEntryUsageFlagBitsNVX>(std::string_view rhs)
{
  static initializer_list<vk::ObjectEntryUsageFlagBitsNVX> il = {
    vk::ObjectEntryUsageFlagBitsNVX::eGraphics,
    vk::ObjectEntryUsageFlagBitsNVX::eCompute,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ObjectEntryUsageFlagBitsNVX{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ObjectEntryUsageFlagsNVX overground::fromString<vk::ObjectEntryUsageFlagsNVX>(std::string_view rhs)
{
  static initializer_list<vk::ObjectEntryUsageFlagsNVX> il = {
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ObjectEntryUsageFlagsNVX{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ObjectType overground::fromString<vk::ObjectType>(std::string_view rhs)
{
  static initializer_list<vk::ObjectType> il = {
    vk::ObjectType::eUnknown,
    vk::ObjectType::eInstance,
    vk::ObjectType::ePhysicalDevice,
    vk::ObjectType::eDevice,
    vk::ObjectType::eQueue,
    vk::ObjectType::eSemaphore,
    vk::ObjectType::eCommandBuffer,
    vk::ObjectType::eFence,
    vk::ObjectType::eDeviceMemory,
    vk::ObjectType::eBuffer,
    vk::ObjectType::eImage,
    vk::ObjectType::eEvent,
    vk::ObjectType::eQueryPool,
    vk::ObjectType::eBufferView,
    vk::ObjectType::eImageView,
    vk::ObjectType::eShaderModule,
    vk::ObjectType::ePipelineCache,
    vk::ObjectType::ePipelineLayout,
    vk::ObjectType::eRenderPass,
    vk::ObjectType::ePipeline,
    vk::ObjectType::eDescriptorSetLayout,
    vk::ObjectType::eSampler,
    vk::ObjectType::eDescriptorPool,
    vk::ObjectType::eDescriptorSet,
    vk::ObjectType::eFramebuffer,
    vk::ObjectType::eCommandPool,
    vk::ObjectType::eSamplerYcbcrConversion,
    vk::ObjectType::eDescriptorUpdateTemplate,
    vk::ObjectType::eSurfaceKHR,
    vk::ObjectType::eSwapchainKHR,
    vk::ObjectType::eDisplayKHR,
    vk::ObjectType::eDisplayModeKHR,
    vk::ObjectType::eDebugReportCallbackEXT,
    vk::ObjectType::eObjectTableNVX,
    vk::ObjectType::eIndirectCommandsLayoutNVX,
    vk::ObjectType::eDebugUtilsMessengerEXT,
    vk::ObjectType::eValidationCacheEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ObjectType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PeerMemoryFeatureFlagBits overground::fromString<vk::PeerMemoryFeatureFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::PeerMemoryFeatureFlagBits> il = {
    vk::PeerMemoryFeatureFlagBits::eCopySrc,
    vk::PeerMemoryFeatureFlagBits::eCopyDst,
    vk::PeerMemoryFeatureFlagBits::eGenericSrc,
    vk::PeerMemoryFeatureFlagBits::eGenericDst,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PeerMemoryFeatureFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PhysicalDeviceType overground::fromString<vk::PhysicalDeviceType>(std::string_view rhs)
{
  static initializer_list<vk::PhysicalDeviceType> il = {
    vk::PhysicalDeviceType::eOther,
    vk::PhysicalDeviceType::eIntegratedGpu,
    vk::PhysicalDeviceType::eDiscreteGpu,
    vk::PhysicalDeviceType::eVirtualGpu,
    vk::PhysicalDeviceType::eCpu,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PhysicalDeviceType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PipelineBindPoint overground::fromString<vk::PipelineBindPoint>(std::string_view rhs)
{
  static initializer_list<vk::PipelineBindPoint> il = {
    vk::PipelineBindPoint::eGraphics,
    vk::PipelineBindPoint::eCompute,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PipelineBindPoint{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PipelineCacheHeaderVersion overground::fromString<vk::PipelineCacheHeaderVersion>(std::string_view rhs)
{
  static initializer_list<vk::PipelineCacheHeaderVersion> il = {
    vk::PipelineCacheHeaderVersion::eOne,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PipelineCacheHeaderVersion{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PipelineCreateFlagBits overground::fromString<vk::PipelineCreateFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::PipelineCreateFlagBits> il = {
    vk::PipelineCreateFlagBits::eDisableOptimization,
    vk::PipelineCreateFlagBits::eAllowDerivatives,
    vk::PipelineCreateFlagBits::eDerivative,
    vk::PipelineCreateFlagBits::eViewIndexFromDeviceIndex,
    vk::PipelineCreateFlagBits::eDispatchBase,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PipelineCreateFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PipelineStageFlagBits overground::fromString<vk::PipelineStageFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::PipelineStageFlagBits> il = {
    vk::PipelineStageFlagBits::eTopOfPipe,
    vk::PipelineStageFlagBits::eDrawIndirect,
    vk::PipelineStageFlagBits::eVertexInput,
    vk::PipelineStageFlagBits::eVertexShader,
    vk::PipelineStageFlagBits::eTessellationControlShader,
    vk::PipelineStageFlagBits::eTessellationEvaluationShader,
    vk::PipelineStageFlagBits::eGeometryShader,
    vk::PipelineStageFlagBits::eFragmentShader,
    vk::PipelineStageFlagBits::eEarlyFragmentTests,
    vk::PipelineStageFlagBits::eLateFragmentTests,
    vk::PipelineStageFlagBits::eColorAttachmentOutput,
    vk::PipelineStageFlagBits::eComputeShader,
    vk::PipelineStageFlagBits::eTransfer,
    vk::PipelineStageFlagBits::eBottomOfPipe,
    vk::PipelineStageFlagBits::eHost,
    vk::PipelineStageFlagBits::eAllGraphics,
    vk::PipelineStageFlagBits::eAllCommands,
    vk::PipelineStageFlagBits::eCommandProcessNVX,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PipelineStageFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PointClippingBehavior overground::fromString<vk::PointClippingBehavior>(std::string_view rhs)
{
  static initializer_list<vk::PointClippingBehavior> il = {
    vk::PointClippingBehavior::eAllClipPlanes,
    vk::PointClippingBehavior::eUserClipPlanesOnly,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PointClippingBehavior{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PolygonMode overground::fromString<vk::PolygonMode>(std::string_view rhs)
{
  static initializer_list<vk::PolygonMode> il = {
    vk::PolygonMode::eFill,
    vk::PolygonMode::eLine,
    vk::PolygonMode::ePoint,
    vk::PolygonMode::eFillRectangleNV,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PolygonMode{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PresentModeKHR overground::fromString<vk::PresentModeKHR>(std::string_view rhs)
{
  static initializer_list<vk::PresentModeKHR> il = {
    vk::PresentModeKHR::eImmediate,
    vk::PresentModeKHR::eMailbox,
    vk::PresentModeKHR::eFifo,
    vk::PresentModeKHR::eFifoRelaxed,
    vk::PresentModeKHR::eSharedDemandRefresh,
    vk::PresentModeKHR::eSharedContinuousRefresh,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PresentModeKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::PrimitiveTopology overground::fromString<vk::PrimitiveTopology>(std::string_view rhs)
{
  static initializer_list<vk::PrimitiveTopology> il = {
    vk::PrimitiveTopology::ePointList,
    vk::PrimitiveTopology::eLineList,
    vk::PrimitiveTopology::eLineStrip,
    vk::PrimitiveTopology::eTriangleList,
    vk::PrimitiveTopology::eTriangleStrip,
    vk::PrimitiveTopology::eTriangleFan,
    vk::PrimitiveTopology::eLineListWithAdjacency,
    vk::PrimitiveTopology::eLineStripWithAdjacency,
    vk::PrimitiveTopology::eTriangleListWithAdjacency,
    vk::PrimitiveTopology::eTriangleStripWithAdjacency,
    vk::PrimitiveTopology::ePatchList,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}PrimitiveTopology{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::QueryControlFlagBits overground::fromString<vk::QueryControlFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::QueryControlFlagBits> il = {
    vk::QueryControlFlagBits::ePrecise,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}QueryControlFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::QueryPipelineStatisticFlagBits overground::fromString<vk::QueryPipelineStatisticFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::QueryPipelineStatisticFlagBits> il = {
    vk::QueryPipelineStatisticFlagBits::eInputAssemblyVertices,
    vk::QueryPipelineStatisticFlagBits::eInputAssemblyPrimitives,
    vk::QueryPipelineStatisticFlagBits::eVertexShaderInvocations,
    vk::QueryPipelineStatisticFlagBits::eGeometryShaderInvocations,
    vk::QueryPipelineStatisticFlagBits::eGeometryShaderPrimitives,
    vk::QueryPipelineStatisticFlagBits::eClippingInvocations,
    vk::QueryPipelineStatisticFlagBits::eClippingPrimitives,
    vk::QueryPipelineStatisticFlagBits::eFragmentShaderInvocations,
    vk::QueryPipelineStatisticFlagBits::eTessellationControlShaderPatches,
    vk::QueryPipelineStatisticFlagBits::eTessellationEvaluationShaderInvocations,
    vk::QueryPipelineStatisticFlagBits::eComputeShaderInvocations,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}QueryPipelineStatisticFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::QueryResultFlagBits overground::fromString<vk::QueryResultFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::QueryResultFlagBits> il = {
    vk::QueryResultFlagBits::e64,
    vk::QueryResultFlagBits::eWait,
    vk::QueryResultFlagBits::eWithAvailability,
    vk::QueryResultFlagBits::ePartial,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}QueryResultFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::QueryType overground::fromString<vk::QueryType>(std::string_view rhs)
{
  static initializer_list<vk::QueryType> il = {
    vk::QueryType::eOcclusion,
    vk::QueryType::ePipelineStatistics,
    vk::QueryType::eTimestamp,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}QueryType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::QueueFlagBits overground::fromString<vk::QueueFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::QueueFlagBits> il = {
    vk::QueueFlagBits::eGraphics,
    vk::QueueFlagBits::eCompute,
    vk::QueueFlagBits::eTransfer,
    vk::QueueFlagBits::eSparseBinding,
    vk::QueueFlagBits::eProtected,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}QueueFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::QueueGlobalPriorityEXT overground::fromString<vk::QueueGlobalPriorityEXT>(std::string_view rhs)
{
  static initializer_list<vk::QueueGlobalPriorityEXT> il = {
    vk::QueueGlobalPriorityEXT::eLow,
    vk::QueueGlobalPriorityEXT::eMedium,
    vk::QueueGlobalPriorityEXT::eHigh,
    vk::QueueGlobalPriorityEXT::eRealtime,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}QueueGlobalPriorityEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::RasterizationOrderAMD overground::fromString<vk::RasterizationOrderAMD>(std::string_view rhs)
{
  static initializer_list<vk::RasterizationOrderAMD> il = {
    vk::RasterizationOrderAMD::eStrict,
    vk::RasterizationOrderAMD::eRelaxed,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}RasterizationOrderAMD{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::Result overground::fromString<vk::Result>(std::string_view rhs)
{
  static initializer_list<vk::Result> il = {
    vk::Result::eSuccess,
    vk::Result::eNotReady,
    vk::Result::eTimeout,
    vk::Result::eEventSet,
    vk::Result::eEventReset,
    vk::Result::eIncomplete,
    vk::Result::eErrorOutOfHostMemory,
    vk::Result::eErrorOutOfDeviceMemory,
    vk::Result::eErrorInitializationFailed,
    vk::Result::eErrorDeviceLost,
    vk::Result::eErrorMemoryMapFailed,
    vk::Result::eErrorLayerNotPresent,
    vk::Result::eErrorExtensionNotPresent,
    vk::Result::eErrorFeatureNotPresent,
    vk::Result::eErrorIncompatibleDriver,
    vk::Result::eErrorTooManyObjects,
    vk::Result::eErrorFormatNotSupported,
    vk::Result::eErrorFragmentedPool,
    vk::Result::eErrorOutOfPoolMemory,
    vk::Result::eErrorInvalidExternalHandle,
    vk::Result::eErrorSurfaceLostKHR,
    vk::Result::eErrorNativeWindowInUseKHR,
    vk::Result::eSuboptimalKHR,
    vk::Result::eErrorOutOfDateKHR,
    vk::Result::eErrorIncompatibleDisplayKHR,
    vk::Result::eErrorValidationFailedEXT,
    vk::Result::eErrorInvalidShaderNV,
    vk::Result::eErrorFragmentationEXT,
    vk::Result::eErrorNotPermittedEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}Result{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SampleCountFlagBits overground::fromString<vk::SampleCountFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::SampleCountFlagBits> il = {
    vk::SampleCountFlagBits::e1,
    vk::SampleCountFlagBits::e2,
    vk::SampleCountFlagBits::e4,
    vk::SampleCountFlagBits::e8,
    vk::SampleCountFlagBits::e16,
    vk::SampleCountFlagBits::e32,
    vk::SampleCountFlagBits::e64,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SampleCountFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SamplerAddressMode overground::fromString<vk::SamplerAddressMode>(std::string_view rhs)
{
  static initializer_list<vk::SamplerAddressMode> il = {
    vk::SamplerAddressMode::eRepeat,
    vk::SamplerAddressMode::eMirroredRepeat,
    vk::SamplerAddressMode::eClampToEdge,
    vk::SamplerAddressMode::eClampToBorder,
    vk::SamplerAddressMode::eMirrorClampToEdge,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SamplerAddressMode{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SamplerMipmapMode overground::fromString<vk::SamplerMipmapMode>(std::string_view rhs)
{
  static initializer_list<vk::SamplerMipmapMode> il = {
    vk::SamplerMipmapMode::eNearest,
    vk::SamplerMipmapMode::eLinear,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SamplerMipmapMode{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SamplerReductionModeEXT overground::fromString<vk::SamplerReductionModeEXT>(std::string_view rhs)
{
  static initializer_list<vk::SamplerReductionModeEXT> il = {
    vk::SamplerReductionModeEXT::eWeightedAverage,
    vk::SamplerReductionModeEXT::eMin,
    vk::SamplerReductionModeEXT::eMax,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SamplerReductionModeEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SamplerYcbcrModelConversion overground::fromString<vk::SamplerYcbcrModelConversion>(std::string_view rhs)
{
  static initializer_list<vk::SamplerYcbcrModelConversion> il = {
    vk::SamplerYcbcrModelConversion::eRgbIdentity,
    vk::SamplerYcbcrModelConversion::eYcbcrIdentity,
    vk::SamplerYcbcrModelConversion::eYcbcr709,
    vk::SamplerYcbcrModelConversion::eYcbcr601,
    vk::SamplerYcbcrModelConversion::eYcbcr2020,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SamplerYcbcrModelConversion{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SamplerYcbcrRange overground::fromString<vk::SamplerYcbcrRange>(std::string_view rhs)
{
  static initializer_list<vk::SamplerYcbcrRange> il = {
    vk::SamplerYcbcrRange::eItuFull,
    vk::SamplerYcbcrRange::eItuNarrow,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SamplerYcbcrRange{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SemaphoreImportFlagBits overground::fromString<vk::SemaphoreImportFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::SemaphoreImportFlagBits> il = {
    vk::SemaphoreImportFlagBits::eTemporary,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SemaphoreImportFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ShaderInfoTypeAMD overground::fromString<vk::ShaderInfoTypeAMD>(std::string_view rhs)
{
  static initializer_list<vk::ShaderInfoTypeAMD> il = {
    vk::ShaderInfoTypeAMD::eStatistics,
    vk::ShaderInfoTypeAMD::eBinary,
    vk::ShaderInfoTypeAMD::eDisassembly,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ShaderInfoTypeAMD{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ShaderStageFlagBits overground::fromString<vk::ShaderStageFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::ShaderStageFlagBits> il = {
    vk::ShaderStageFlagBits::eVertex,
    vk::ShaderStageFlagBits::eTessellationControl,
    vk::ShaderStageFlagBits::eTessellationEvaluation,
    vk::ShaderStageFlagBits::eGeometry,
    vk::ShaderStageFlagBits::eFragment,
    vk::ShaderStageFlagBits::eCompute,
    vk::ShaderStageFlagBits::eAllGraphics,
    vk::ShaderStageFlagBits::eAll,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ShaderStageFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SharingMode overground::fromString<vk::SharingMode>(std::string_view rhs)
{
  static initializer_list<vk::SharingMode> il = {
    vk::SharingMode::eExclusive,
    vk::SharingMode::eConcurrent,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SharingMode{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SparseImageFormatFlagBits overground::fromString<vk::SparseImageFormatFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::SparseImageFormatFlagBits> il = {
    vk::SparseImageFormatFlagBits::eSingleMiptail,
    vk::SparseImageFormatFlagBits::eAlignedMipSize,
    vk::SparseImageFormatFlagBits::eNonstandardBlockSize,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SparseImageFormatFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SparseMemoryBindFlagBits overground::fromString<vk::SparseMemoryBindFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::SparseMemoryBindFlagBits> il = {
    vk::SparseMemoryBindFlagBits::eMetadata,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SparseMemoryBindFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::StencilFaceFlagBits overground::fromString<vk::StencilFaceFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::StencilFaceFlagBits> il = {
    vk::StencilFaceFlagBits::eFront,
    vk::StencilFaceFlagBits::eBack,
    vk::StencilFaceFlagBits::eVkStencilFrontAndBack,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}StencilFaceFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::StencilOp overground::fromString<vk::StencilOp>(std::string_view rhs)
{
  static initializer_list<vk::StencilOp> il = {
    vk::StencilOp::eKeep,
    vk::StencilOp::eZero,
    vk::StencilOp::eReplace,
    vk::StencilOp::eIncrementAndClamp,
    vk::StencilOp::eDecrementAndClamp,
    vk::StencilOp::eInvert,
    vk::StencilOp::eIncrementAndWrap,
    vk::StencilOp::eDecrementAndWrap,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}StencilOp{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::StructureType overground::fromString<vk::StructureType>(std::string_view rhs)
{
  static initializer_list<vk::StructureType> il = {
    vk::StructureType::eApplicationInfo,
    vk::StructureType::eInstanceCreateInfo,
    vk::StructureType::eDeviceQueueCreateInfo,
    vk::StructureType::eDeviceCreateInfo,
    vk::StructureType::eSubmitInfo,
    vk::StructureType::eMemoryAllocateInfo,
    vk::StructureType::eMappedMemoryRange,
    vk::StructureType::eBindSparseInfo,
    vk::StructureType::eFenceCreateInfo,
    vk::StructureType::eSemaphoreCreateInfo,
    vk::StructureType::eEventCreateInfo,
    vk::StructureType::eQueryPoolCreateInfo,
    vk::StructureType::eBufferCreateInfo,
    vk::StructureType::eBufferViewCreateInfo,
    vk::StructureType::eImageCreateInfo,
    vk::StructureType::eImageViewCreateInfo,
    vk::StructureType::eShaderModuleCreateInfo,
    vk::StructureType::ePipelineCacheCreateInfo,
    vk::StructureType::ePipelineShaderStageCreateInfo,
    vk::StructureType::ePipelineVertexInputStateCreateInfo,
    vk::StructureType::ePipelineInputAssemblyStateCreateInfo,
    vk::StructureType::ePipelineTessellationStateCreateInfo,
    vk::StructureType::ePipelineViewportStateCreateInfo,
    vk::StructureType::ePipelineRasterizationStateCreateInfo,
    vk::StructureType::ePipelineMultisampleStateCreateInfo,
    vk::StructureType::ePipelineDepthStencilStateCreateInfo,
    vk::StructureType::ePipelineColorBlendStateCreateInfo,
    vk::StructureType::ePipelineDynamicStateCreateInfo,
    vk::StructureType::eGraphicsPipelineCreateInfo,
    vk::StructureType::eComputePipelineCreateInfo,
    vk::StructureType::ePipelineLayoutCreateInfo,
    vk::StructureType::eSamplerCreateInfo,
    vk::StructureType::eDescriptorSetLayoutCreateInfo,
    vk::StructureType::eDescriptorPoolCreateInfo,
    vk::StructureType::eDescriptorSetAllocateInfo,
    vk::StructureType::eWriteDescriptorSet,
    vk::StructureType::eCopyDescriptorSet,
    vk::StructureType::eFramebufferCreateInfo,
    vk::StructureType::eRenderPassCreateInfo,
    vk::StructureType::eCommandPoolCreateInfo,
    vk::StructureType::eCommandBufferAllocateInfo,
    vk::StructureType::eCommandBufferInheritanceInfo,
    vk::StructureType::eCommandBufferBeginInfo,
    vk::StructureType::eRenderPassBeginInfo,
    vk::StructureType::eBufferMemoryBarrier,
    vk::StructureType::eImageMemoryBarrier,
    vk::StructureType::eMemoryBarrier,
    vk::StructureType::eLoaderInstanceCreateInfo,
    vk::StructureType::eLoaderDeviceCreateInfo,
    vk::StructureType::ePhysicalDeviceSubgroupProperties,
    vk::StructureType::eBindBufferMemoryInfo,
    vk::StructureType::eBindImageMemoryInfo,
    vk::StructureType::ePhysicalDevice16BitStorageFeatures,
    vk::StructureType::eMemoryDedicatedRequirements,
    vk::StructureType::eMemoryDedicatedAllocateInfo,
    vk::StructureType::eMemoryAllocateFlagsInfo,
    vk::StructureType::eDeviceGroupRenderPassBeginInfo,
    vk::StructureType::eDeviceGroupCommandBufferBeginInfo,
    vk::StructureType::eDeviceGroupSubmitInfo,
    vk::StructureType::eDeviceGroupBindSparseInfo,
    vk::StructureType::eBindBufferMemoryDeviceGroupInfo,
    vk::StructureType::eBindImageMemoryDeviceGroupInfo,
    vk::StructureType::ePhysicalDeviceGroupProperties,
    vk::StructureType::eDeviceGroupDeviceCreateInfo,
    vk::StructureType::eBufferMemoryRequirementsInfo2,
    vk::StructureType::eImageMemoryRequirementsInfo2,
    vk::StructureType::eImageSparseMemoryRequirementsInfo2,
    vk::StructureType::eMemoryRequirements2,
    vk::StructureType::eSparseImageMemoryRequirements2,
    vk::StructureType::ePhysicalDeviceFeatures2,
    vk::StructureType::ePhysicalDeviceProperties2,
    vk::StructureType::eFormatProperties2,
    vk::StructureType::eImageFormatProperties2,
    vk::StructureType::ePhysicalDeviceImageFormatInfo2,
    vk::StructureType::eQueueFamilyProperties2,
    vk::StructureType::ePhysicalDeviceMemoryProperties2,
    vk::StructureType::eSparseImageFormatProperties2,
    vk::StructureType::ePhysicalDeviceSparseImageFormatInfo2,
    vk::StructureType::ePhysicalDevicePointClippingProperties,
    vk::StructureType::eRenderPassInputAttachmentAspectCreateInfo,
    vk::StructureType::eImageViewUsageCreateInfo,
    vk::StructureType::ePipelineTessellationDomainOriginStateCreateInfo,
    vk::StructureType::eRenderPassMultiviewCreateInfo,
    vk::StructureType::ePhysicalDeviceMultiviewFeatures,
    vk::StructureType::ePhysicalDeviceMultiviewProperties,
    vk::StructureType::ePhysicalDeviceVariablePointerFeatures,
    vk::StructureType::eProtectedSubmitInfo,
    vk::StructureType::ePhysicalDeviceProtectedMemoryFeatures,
    vk::StructureType::ePhysicalDeviceProtectedMemoryProperties,
    vk::StructureType::eDeviceQueueInfo2,
    vk::StructureType::eSamplerYcbcrConversionCreateInfo,
    vk::StructureType::eSamplerYcbcrConversionInfo,
    vk::StructureType::eBindImagePlaneMemoryInfo,
    vk::StructureType::eImagePlaneMemoryRequirementsInfo,
    vk::StructureType::ePhysicalDeviceSamplerYcbcrConversionFeatures,
    vk::StructureType::eSamplerYcbcrConversionImageFormatProperties,
    vk::StructureType::eDescriptorUpdateTemplateCreateInfo,
    vk::StructureType::ePhysicalDeviceExternalImageFormatInfo,
    vk::StructureType::eExternalImageFormatProperties,
    vk::StructureType::ePhysicalDeviceExternalBufferInfo,
    vk::StructureType::eExternalBufferProperties,
    vk::StructureType::ePhysicalDeviceIdProperties,
    vk::StructureType::eExternalMemoryBufferCreateInfo,
    vk::StructureType::eExternalMemoryImageCreateInfo,
    vk::StructureType::eExportMemoryAllocateInfo,
    vk::StructureType::ePhysicalDeviceExternalFenceInfo,
    vk::StructureType::eExternalFenceProperties,
    vk::StructureType::eExportFenceCreateInfo,
    vk::StructureType::eExportSemaphoreCreateInfo,
    vk::StructureType::ePhysicalDeviceExternalSemaphoreInfo,
    vk::StructureType::eExternalSemaphoreProperties,
    vk::StructureType::ePhysicalDeviceMaintenance3Properties,
    vk::StructureType::eDescriptorSetLayoutSupport,
    vk::StructureType::ePhysicalDeviceShaderDrawParameterFeatures,
    vk::StructureType::eSwapchainCreateInfoKHR,
    vk::StructureType::ePresentInfoKHR,
    vk::StructureType::eDeviceGroupPresentCapabilitiesKHR,
    vk::StructureType::eImageSwapchainCreateInfoKHR,
    vk::StructureType::eBindImageMemorySwapchainInfoKHR,
    vk::StructureType::eAcquireNextImageInfoKHR,
    vk::StructureType::eDeviceGroupPresentInfoKHR,
    vk::StructureType::eDeviceGroupSwapchainCreateInfoKHR,
    vk::StructureType::eDisplayModeCreateInfoKHR,
    vk::StructureType::eDisplaySurfaceCreateInfoKHR,
    vk::StructureType::eDisplayPresentInfoKHR,
    vk::StructureType::eXlibSurfaceCreateInfoKHR,
    vk::StructureType::eXcbSurfaceCreateInfoKHR,
    vk::StructureType::eWaylandSurfaceCreateInfoKHR,
    vk::StructureType::eMirSurfaceCreateInfoKHR,
    vk::StructureType::eAndroidSurfaceCreateInfoKHR,
    vk::StructureType::eWin32SurfaceCreateInfoKHR,
    vk::StructureType::eDebugReportCallbackCreateInfoEXT,
    vk::StructureType::ePipelineRasterizationStateRasterizationOrderAMD,
    vk::StructureType::eDebugMarkerObjectNameInfoEXT,
    vk::StructureType::eDebugMarkerObjectTagInfoEXT,
    vk::StructureType::eDebugMarkerMarkerInfoEXT,
    vk::StructureType::eDedicatedAllocationImageCreateInfoNV,
    vk::StructureType::eDedicatedAllocationBufferCreateInfoNV,
    vk::StructureType::eDedicatedAllocationMemoryAllocateInfoNV,
    vk::StructureType::eTextureLodGatherFormatPropertiesAMD,
    vk::StructureType::eExternalMemoryImageCreateInfoNV,
    vk::StructureType::eExportMemoryAllocateInfoNV,
    vk::StructureType::eImportMemoryWin32HandleInfoNV,
    vk::StructureType::eExportMemoryWin32HandleInfoNV,
    vk::StructureType::eWin32KeyedMutexAcquireReleaseInfoNV,
    vk::StructureType::eValidationFlagsEXT,
    vk::StructureType::eViSurfaceCreateInfoNN,
    vk::StructureType::eImportMemoryWin32HandleInfoKHR,
    vk::StructureType::eExportMemoryWin32HandleInfoKHR,
    vk::StructureType::eMemoryWin32HandlePropertiesKHR,
    vk::StructureType::eMemoryGetWin32HandleInfoKHR,
    vk::StructureType::eImportMemoryFdInfoKHR,
    vk::StructureType::eMemoryFdPropertiesKHR,
    vk::StructureType::eMemoryGetFdInfoKHR,
    vk::StructureType::eWin32KeyedMutexAcquireReleaseInfoKHR,
    vk::StructureType::eImportSemaphoreWin32HandleInfoKHR,
    vk::StructureType::eExportSemaphoreWin32HandleInfoKHR,
    vk::StructureType::eD3D12FenceSubmitInfoKHR,
    vk::StructureType::eSemaphoreGetWin32HandleInfoKHR,
    vk::StructureType::eImportSemaphoreFdInfoKHR,
    vk::StructureType::eSemaphoreGetFdInfoKHR,
    vk::StructureType::ePhysicalDevicePushDescriptorPropertiesKHR,
    vk::StructureType::ePresentRegionsKHR,
    vk::StructureType::eObjectTableCreateInfoNVX,
    vk::StructureType::eIndirectCommandsLayoutCreateInfoNVX,
    vk::StructureType::eCmdProcessCommandsInfoNVX,
    vk::StructureType::eCmdReserveSpaceForCommandsInfoNVX,
    vk::StructureType::eDeviceGeneratedCommandsLimitsNVX,
    vk::StructureType::eDeviceGeneratedCommandsFeaturesNVX,
    vk::StructureType::ePipelineViewportWScalingStateCreateInfoNV,
    vk::StructureType::eSurfaceCapabilities2EXT,
    vk::StructureType::eDisplayPowerInfoEXT,
    vk::StructureType::eDeviceEventInfoEXT,
    vk::StructureType::eDisplayEventInfoEXT,
    vk::StructureType::eSwapchainCounterCreateInfoEXT,
    vk::StructureType::ePresentTimesInfoGOOGLE,
    vk::StructureType::ePhysicalDeviceMultiviewPerViewAttributesPropertiesNVX,
    vk::StructureType::ePipelineViewportSwizzleStateCreateInfoNV,
    vk::StructureType::ePhysicalDeviceDiscardRectanglePropertiesEXT,
    vk::StructureType::ePipelineDiscardRectangleStateCreateInfoEXT,
    vk::StructureType::ePhysicalDeviceConservativeRasterizationPropertiesEXT,
    vk::StructureType::ePipelineRasterizationConservativeStateCreateInfoEXT,
    vk::StructureType::eHdrMetadataEXT,
    vk::StructureType::eSharedPresentSurfaceCapabilitiesKHR,
    vk::StructureType::eImportFenceWin32HandleInfoKHR,
    vk::StructureType::eExportFenceWin32HandleInfoKHR,
    vk::StructureType::eFenceGetWin32HandleInfoKHR,
    vk::StructureType::eImportFenceFdInfoKHR,
    vk::StructureType::eFenceGetFdInfoKHR,
    vk::StructureType::ePhysicalDeviceSurfaceInfo2KHR,
    vk::StructureType::eSurfaceCapabilities2KHR,
    vk::StructureType::eSurfaceFormat2KHR,
    vk::StructureType::eDisplayProperties2KHR,
    vk::StructureType::eDisplayPlaneProperties2KHR,
    vk::StructureType::eDisplayModeProperties2KHR,
    vk::StructureType::eDisplayPlaneInfo2KHR,
    vk::StructureType::eDisplayPlaneCapabilities2KHR,
    vk::StructureType::eIosSurfaceCreateInfoMVK,
    vk::StructureType::eMacosSurfaceCreateInfoMVK,
    vk::StructureType::eDebugUtilsObjectNameInfoEXT,
    vk::StructureType::eDebugUtilsObjectTagInfoEXT,
    vk::StructureType::eDebugUtilsLabelEXT,
    vk::StructureType::eDebugUtilsMessengerCallbackDataEXT,
    vk::StructureType::eDebugUtilsMessengerCreateInfoEXT,
    vk::StructureType::eAndroidHardwareBufferUsageANDROID,
    vk::StructureType::eAndroidHardwareBufferPropertiesANDROID,
    vk::StructureType::eAndroidHardwareBufferFormatPropertiesANDROID,
    vk::StructureType::eImportAndroidHardwareBufferInfoANDROID,
    vk::StructureType::eMemoryGetAndroidHardwareBufferInfoANDROID,
    vk::StructureType::eExternalFormatANDROID,
    vk::StructureType::ePhysicalDeviceSamplerFilterMinmaxPropertiesEXT,
    vk::StructureType::eSamplerReductionModeCreateInfoEXT,
    vk::StructureType::eSampleLocationsInfoEXT,
    vk::StructureType::eRenderPassSampleLocationsBeginInfoEXT,
    vk::StructureType::ePipelineSampleLocationsStateCreateInfoEXT,
    vk::StructureType::ePhysicalDeviceSampleLocationsPropertiesEXT,
    vk::StructureType::eMultisamplePropertiesEXT,
    vk::StructureType::eImageFormatListCreateInfoKHR,
    vk::StructureType::ePhysicalDeviceBlendOperationAdvancedFeaturesEXT,
    vk::StructureType::ePhysicalDeviceBlendOperationAdvancedPropertiesEXT,
    vk::StructureType::ePipelineColorBlendAdvancedStateCreateInfoEXT,
    vk::StructureType::ePipelineCoverageToColorStateCreateInfoNV,
    vk::StructureType::ePipelineCoverageModulationStateCreateInfoNV,
    vk::StructureType::eValidationCacheCreateInfoEXT,
    vk::StructureType::eShaderModuleValidationCacheCreateInfoEXT,
    vk::StructureType::eDescriptorSetLayoutBindingFlagsCreateInfoEXT,
    vk::StructureType::ePhysicalDeviceDescriptorIndexingFeaturesEXT,
    vk::StructureType::ePhysicalDeviceDescriptorIndexingPropertiesEXT,
    vk::StructureType::eDescriptorSetVariableDescriptorCountAllocateInfoEXT,
    vk::StructureType::eDescriptorSetVariableDescriptorCountLayoutSupportEXT,
    vk::StructureType::eDeviceQueueGlobalPriorityCreateInfoEXT,
    vk::StructureType::eImportMemoryHostPointerInfoEXT,
    vk::StructureType::eMemoryHostPointerPropertiesEXT,
    vk::StructureType::ePhysicalDeviceExternalMemoryHostPropertiesEXT,
    vk::StructureType::ePhysicalDeviceShaderCorePropertiesAMD,
    vk::StructureType::ePhysicalDeviceVertexAttributeDivisorPropertiesEXT,
    vk::StructureType::ePipelineVertexInputDivisorStateCreateInfoEXT,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}StructureType{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SubgroupFeatureFlagBits overground::fromString<vk::SubgroupFeatureFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::SubgroupFeatureFlagBits> il = {
    vk::SubgroupFeatureFlagBits::eBasic,
    vk::SubgroupFeatureFlagBits::eVote,
    vk::SubgroupFeatureFlagBits::eArithmetic,
    vk::SubgroupFeatureFlagBits::eBallot,
    vk::SubgroupFeatureFlagBits::eShuffle,
    vk::SubgroupFeatureFlagBits::eShuffleRelative,
    vk::SubgroupFeatureFlagBits::eClustered,
    vk::SubgroupFeatureFlagBits::eQuad,
    vk::SubgroupFeatureFlagBits::ePartitionedNV,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SubgroupFeatureFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SubpassContents overground::fromString<vk::SubpassContents>(std::string_view rhs)
{
  static initializer_list<vk::SubpassContents> il = {
    vk::SubpassContents::eInline,
    vk::SubpassContents::eSecondaryCommandBuffers,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SubpassContents{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SubpassDescriptionFlagBits overground::fromString<vk::SubpassDescriptionFlagBits>(std::string_view rhs)
{
  static initializer_list<vk::SubpassDescriptionFlagBits> il = {
    vk::SubpassDescriptionFlagBits::ePerViewAttributesNVX,
    vk::SubpassDescriptionFlagBits::ePerViewPositionXOnlyNVX,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SubpassDescriptionFlagBits{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SurfaceCounterFlagBitsEXT overground::fromString<vk::SurfaceCounterFlagBitsEXT>(std::string_view rhs)
{
  static initializer_list<vk::SurfaceCounterFlagBitsEXT> il = {
    vk::SurfaceCounterFlagBitsEXT::eVblank,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SurfaceCounterFlagBitsEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SurfaceTransformFlagBitsKHR overground::fromString<vk::SurfaceTransformFlagBitsKHR>(std::string_view rhs)
{
  static initializer_list<vk::SurfaceTransformFlagBitsKHR> il = {
    vk::SurfaceTransformFlagBitsKHR::eIdentity,
    vk::SurfaceTransformFlagBitsKHR::eRotate90,
    vk::SurfaceTransformFlagBitsKHR::eRotate180,
    vk::SurfaceTransformFlagBitsKHR::eRotate270,
    vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror,
    vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90,
    vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180,
    vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270,
    vk::SurfaceTransformFlagBitsKHR::eInherit,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SurfaceTransformFlagBitsKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SwapchainCreateFlagBitsKHR overground::fromString<vk::SwapchainCreateFlagBitsKHR>(std::string_view rhs)
{
  static initializer_list<vk::SwapchainCreateFlagBitsKHR> il = {
    vk::SwapchainCreateFlagBitsKHR::eSplitInstanceBindRegions,
    vk::SwapchainCreateFlagBitsKHR::eProtected,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SwapchainCreateFlagBitsKHR{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::SystemAllocationScope overground::fromString<vk::SystemAllocationScope>(std::string_view rhs)
{
  static initializer_list<vk::SystemAllocationScope> il = {
    vk::SystemAllocationScope::eCommand,
    vk::SystemAllocationScope::eObject,
    vk::SystemAllocationScope::eCache,
    vk::SystemAllocationScope::eDevice,
    vk::SystemAllocationScope::eInstance,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}SystemAllocationScope{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::TessellationDomainOrigin overground::fromString<vk::TessellationDomainOrigin>(std::string_view rhs)
{
  static initializer_list<vk::TessellationDomainOrigin> il = {
    vk::TessellationDomainOrigin::eUpperLeft,
    vk::TessellationDomainOrigin::eLowerLeft,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}TessellationDomainOrigin{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ValidationCacheHeaderVersionEXT overground::fromString<vk::ValidationCacheHeaderVersionEXT>(std::string_view rhs)
{
  static initializer_list<vk::ValidationCacheHeaderVersionEXT> il = {
    vk::ValidationCacheHeaderVersionEXT::eOne,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ValidationCacheHeaderVersionEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ValidationCheckEXT overground::fromString<vk::ValidationCheckEXT>(std::string_view rhs)
{
  static initializer_list<vk::ValidationCheckEXT> il = {
    vk::ValidationCheckEXT::eAll,
    vk::ValidationCheckEXT::eShaders,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ValidationCheckEXT{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::VertexInputRate overground::fromString<vk::VertexInputRate>(std::string_view rhs)
{
  static initializer_list<vk::VertexInputRate> il = {
    vk::VertexInputRate::eVertex,
    vk::VertexInputRate::eInstance,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}VertexInputRate{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

template<>
vk::ViewportCoordinateSwizzleNV overground::fromString<vk::ViewportCoordinateSwizzleNV>(std::string_view rhs)
{
  static initializer_list<vk::ViewportCoordinateSwizzleNV> il = {
    vk::ViewportCoordinateSwizzleNV::ePositiveX,
    vk::ViewportCoordinateSwizzleNV::eNegativeX,
    vk::ViewportCoordinateSwizzleNV::ePositiveY,
    vk::ViewportCoordinateSwizzleNV::eNegativeY,
    vk::ViewportCoordinateSwizzleNV::ePositiveZ,
    vk::ViewportCoordinateSwizzleNV::eNegativeZ,
    vk::ViewportCoordinateSwizzleNV::ePositiveW,
    vk::ViewportCoordinateSwizzleNV::eNegativeW,
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}ViewportCoordinateSwizzleNV{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}

