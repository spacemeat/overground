#ifndef ENUMPARSERS_H
#define ENUMPARSERS_H

#include "utils.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "enumParsers.h"

namespace overground
{
  template<class EnumType>
  EnumType fromString(std::string_view rhs);

  template<>
  vk::AccessFlagBits fromString<vk::AccessFlagBits>(std::string_view rhs);
  template<>
  vk::AttachmentDescriptionFlagBits fromString<vk::AttachmentDescriptionFlagBits>(std::string_view rhs);
  template<>
  vk::AttachmentLoadOp fromString<vk::AttachmentLoadOp>(std::string_view rhs);
  template<>
  vk::AttachmentStoreOp fromString<vk::AttachmentStoreOp>(std::string_view rhs);
  template<>
  vk::BlendFactor fromString<vk::BlendFactor>(std::string_view rhs);
  template<>
  vk::BlendOp fromString<vk::BlendOp>(std::string_view rhs);
  template<>
  vk::BlendOverlapEXT fromString<vk::BlendOverlapEXT>(std::string_view rhs);
  template<>
  vk::BorderColor fromString<vk::BorderColor>(std::string_view rhs);
  template<>
  vk::BufferCreateFlagBits fromString<vk::BufferCreateFlagBits>(std::string_view rhs);
  template<>
  vk::BufferUsageFlagBits fromString<vk::BufferUsageFlagBits>(std::string_view rhs);
  template<>
  vk::ChromaLocation fromString<vk::ChromaLocation>(std::string_view rhs);
  template<>
  vk::ColorComponentFlagBits fromString<vk::ColorComponentFlagBits>(std::string_view rhs);
  template<>
  vk::ColorSpaceKHR fromString<vk::ColorSpaceKHR>(std::string_view rhs);
  template<>
  vk::CommandBufferLevel fromString<vk::CommandBufferLevel>(std::string_view rhs);
  template<>
  vk::CommandBufferResetFlagBits fromString<vk::CommandBufferResetFlagBits>(std::string_view rhs);
  template<>
  vk::CommandBufferUsageFlagBits fromString<vk::CommandBufferUsageFlagBits>(std::string_view rhs);
  template<>
  vk::CommandPoolCreateFlagBits fromString<vk::CommandPoolCreateFlagBits>(std::string_view rhs);
  template<>
  vk::CommandPoolResetFlagBits fromString<vk::CommandPoolResetFlagBits>(std::string_view rhs);
  template<>
  vk::CompareOp fromString<vk::CompareOp>(std::string_view rhs);
  template<>
  vk::ComponentSwizzle fromString<vk::ComponentSwizzle>(std::string_view rhs);
  template<>
  vk::CompositeAlphaFlagBitsKHR fromString<vk::CompositeAlphaFlagBitsKHR>(std::string_view rhs);
  template<>
  vk::ConservativeRasterizationModeEXT fromString<vk::ConservativeRasterizationModeEXT>(std::string_view rhs);
  template<>
  vk::CoverageModulationModeNV fromString<vk::CoverageModulationModeNV>(std::string_view rhs);
  template<>
  vk::CullModeFlagBits fromString<vk::CullModeFlagBits>(std::string_view rhs);
  template<>
  vk::DebugReportFlagBitsEXT fromString<vk::DebugReportFlagBitsEXT>(std::string_view rhs);
  template<>
  vk::DebugReportObjectTypeEXT fromString<vk::DebugReportObjectTypeEXT>(std::string_view rhs);
  template<>
  vk::DebugUtilsMessageSeverityFlagBitsEXT fromString<vk::DebugUtilsMessageSeverityFlagBitsEXT>(std::string_view rhs);
  template<>
  vk::DebugUtilsMessageTypeFlagBitsEXT fromString<vk::DebugUtilsMessageTypeFlagBitsEXT>(std::string_view rhs);
  template<>
  vk::DependencyFlagBits fromString<vk::DependencyFlagBits>(std::string_view rhs);
  template<>
  vk::DescriptorBindingFlagBitsEXT fromString<vk::DescriptorBindingFlagBitsEXT>(std::string_view rhs);
  template<>
  vk::DescriptorPoolCreateFlagBits fromString<vk::DescriptorPoolCreateFlagBits>(std::string_view rhs);
  template<>
  vk::DescriptorSetLayoutCreateFlagBits fromString<vk::DescriptorSetLayoutCreateFlagBits>(std::string_view rhs);
  template<>
  vk::DescriptorType fromString<vk::DescriptorType>(std::string_view rhs);
  template<>
  vk::DescriptorUpdateTemplateType fromString<vk::DescriptorUpdateTemplateType>(std::string_view rhs);
  template<>
  vk::DeviceEventTypeEXT fromString<vk::DeviceEventTypeEXT>(std::string_view rhs);
  template<>
  vk::DeviceGroupPresentModeFlagBitsKHR fromString<vk::DeviceGroupPresentModeFlagBitsKHR>(std::string_view rhs);
  template<>
  vk::DeviceQueueCreateFlagBits fromString<vk::DeviceQueueCreateFlagBits>(std::string_view rhs);
  template<>
  vk::DiscardRectangleModeEXT fromString<vk::DiscardRectangleModeEXT>(std::string_view rhs);
  template<>
  vk::DisplayEventTypeEXT fromString<vk::DisplayEventTypeEXT>(std::string_view rhs);
  template<>
  vk::DisplayPlaneAlphaFlagBitsKHR fromString<vk::DisplayPlaneAlphaFlagBitsKHR>(std::string_view rhs);
  template<>
  vk::DisplayPowerStateEXT fromString<vk::DisplayPowerStateEXT>(std::string_view rhs);
  template<>
  vk::DynamicState fromString<vk::DynamicState>(std::string_view rhs);
  template<>
  vk::ExternalFenceFeatureFlagBits fromString<vk::ExternalFenceFeatureFlagBits>(std::string_view rhs);
  template<>
  vk::ExternalFenceHandleTypeFlagBits fromString<vk::ExternalFenceHandleTypeFlagBits>(std::string_view rhs);
  template<>
  vk::ExternalMemoryFeatureFlagBits fromString<vk::ExternalMemoryFeatureFlagBits>(std::string_view rhs);
  template<>
  vk::ExternalMemoryFeatureFlagBitsNV fromString<vk::ExternalMemoryFeatureFlagBitsNV>(std::string_view rhs);
  template<>
  vk::ExternalMemoryFeatureFlagsNV fromString<vk::ExternalMemoryFeatureFlagsNV>(std::string_view rhs);
  template<>
  vk::ExternalMemoryHandleTypeFlagBits fromString<vk::ExternalMemoryHandleTypeFlagBits>(std::string_view rhs);
  template<>
  vk::ExternalMemoryHandleTypeFlagBitsNV fromString<vk::ExternalMemoryHandleTypeFlagBitsNV>(std::string_view rhs);
  template<>
  vk::ExternalMemoryHandleTypeFlagsNV fromString<vk::ExternalMemoryHandleTypeFlagsNV>(std::string_view rhs);
  template<>
  vk::ExternalSemaphoreFeatureFlagBits fromString<vk::ExternalSemaphoreFeatureFlagBits>(std::string_view rhs);
  template<>
  vk::ExternalSemaphoreHandleTypeFlagBits fromString<vk::ExternalSemaphoreHandleTypeFlagBits>(std::string_view rhs);
  template<>
  vk::FenceCreateFlagBits fromString<vk::FenceCreateFlagBits>(std::string_view rhs);
  template<>
  vk::FenceImportFlagBits fromString<vk::FenceImportFlagBits>(std::string_view rhs);
  template<>
  vk::Filter fromString<vk::Filter>(std::string_view rhs);
  template<>
  vk::Format fromString<vk::Format>(std::string_view rhs);
  template<>
  vk::FormatFeatureFlagBits fromString<vk::FormatFeatureFlagBits>(std::string_view rhs);
  template<>
  vk::FrontFace fromString<vk::FrontFace>(std::string_view rhs);
  template<>
  vk::ImageAspectFlagBits fromString<vk::ImageAspectFlagBits>(std::string_view rhs);
  template<>
  vk::ImageCreateFlagBits fromString<vk::ImageCreateFlagBits>(std::string_view rhs);
  template<>
  vk::ImageLayout fromString<vk::ImageLayout>(std::string_view rhs);
  template<>
  vk::ImageTiling fromString<vk::ImageTiling>(std::string_view rhs);
  template<>
  vk::ImageType fromString<vk::ImageType>(std::string_view rhs);
  template<>
  vk::ImageUsageFlagBits fromString<vk::ImageUsageFlagBits>(std::string_view rhs);
  template<>
  vk::ImageViewType fromString<vk::ImageViewType>(std::string_view rhs);
  template<>
  vk::IndexType fromString<vk::IndexType>(std::string_view rhs);
  template<>
  vk::IndirectCommandsLayoutUsageFlagBitsNVX fromString<vk::IndirectCommandsLayoutUsageFlagBitsNVX>(std::string_view rhs);
  template<>
  vk::IndirectCommandsLayoutUsageFlagsNVX fromString<vk::IndirectCommandsLayoutUsageFlagsNVX>(std::string_view rhs);
  template<>
  vk::IndirectCommandsTokenTypeNVX fromString<vk::IndirectCommandsTokenTypeNVX>(std::string_view rhs);
  template<>
  vk::InternalAllocationType fromString<vk::InternalAllocationType>(std::string_view rhs);
  template<>
  vk::LogicOp fromString<vk::LogicOp>(std::string_view rhs);
  template<>
  vk::MemoryAllocateFlagBits fromString<vk::MemoryAllocateFlagBits>(std::string_view rhs);
  template<>
  vk::MemoryHeapFlagBits fromString<vk::MemoryHeapFlagBits>(std::string_view rhs);
  template<>
  vk::MemoryPropertyFlagBits fromString<vk::MemoryPropertyFlagBits>(std::string_view rhs);
  template<>
  vk::ObjectEntryTypeNVX fromString<vk::ObjectEntryTypeNVX>(std::string_view rhs);
  template<>
  vk::ObjectEntryUsageFlagBitsNVX fromString<vk::ObjectEntryUsageFlagBitsNVX>(std::string_view rhs);
  template<>
  vk::ObjectEntryUsageFlagsNVX fromString<vk::ObjectEntryUsageFlagsNVX>(std::string_view rhs);
  template<>
  vk::ObjectType fromString<vk::ObjectType>(std::string_view rhs);
  template<>
  vk::PeerMemoryFeatureFlagBits fromString<vk::PeerMemoryFeatureFlagBits>(std::string_view rhs);
  template<>
  vk::PhysicalDeviceType fromString<vk::PhysicalDeviceType>(std::string_view rhs);
  template<>
  vk::PipelineBindPoint fromString<vk::PipelineBindPoint>(std::string_view rhs);
  template<>
  vk::PipelineCacheHeaderVersion fromString<vk::PipelineCacheHeaderVersion>(std::string_view rhs);
  template<>
  vk::PipelineCreateFlagBits fromString<vk::PipelineCreateFlagBits>(std::string_view rhs);
  template<>
  vk::PipelineStageFlagBits fromString<vk::PipelineStageFlagBits>(std::string_view rhs);
  template<>
  vk::PointClippingBehavior fromString<vk::PointClippingBehavior>(std::string_view rhs);
  template<>
  vk::PolygonMode fromString<vk::PolygonMode>(std::string_view rhs);
  template<>
  vk::PresentModeKHR fromString<vk::PresentModeKHR>(std::string_view rhs);
  template<>
  vk::PrimitiveTopology fromString<vk::PrimitiveTopology>(std::string_view rhs);
  template<>
  vk::QueryControlFlagBits fromString<vk::QueryControlFlagBits>(std::string_view rhs);
  template<>
  vk::QueryPipelineStatisticFlagBits fromString<vk::QueryPipelineStatisticFlagBits>(std::string_view rhs);
  template<>
  vk::QueryResultFlagBits fromString<vk::QueryResultFlagBits>(std::string_view rhs);
  template<>
  vk::QueryType fromString<vk::QueryType>(std::string_view rhs);
  template<>
  vk::QueueFlagBits fromString<vk::QueueFlagBits>(std::string_view rhs);
  template<>
  vk::QueueGlobalPriorityEXT fromString<vk::QueueGlobalPriorityEXT>(std::string_view rhs);
  template<>
  vk::RasterizationOrderAMD fromString<vk::RasterizationOrderAMD>(std::string_view rhs);
  template<>
  vk::Result fromString<vk::Result>(std::string_view rhs);
  template<>
  vk::SampleCountFlagBits fromString<vk::SampleCountFlagBits>(std::string_view rhs);
  template<>
  vk::SamplerAddressMode fromString<vk::SamplerAddressMode>(std::string_view rhs);
  template<>
  vk::SamplerMipmapMode fromString<vk::SamplerMipmapMode>(std::string_view rhs);
  template<>
  vk::SamplerReductionModeEXT fromString<vk::SamplerReductionModeEXT>(std::string_view rhs);
  template<>
  vk::SamplerYcbcrModelConversion fromString<vk::SamplerYcbcrModelConversion>(std::string_view rhs);
  template<>
  vk::SamplerYcbcrRange fromString<vk::SamplerYcbcrRange>(std::string_view rhs);
  template<>
  vk::SemaphoreImportFlagBits fromString<vk::SemaphoreImportFlagBits>(std::string_view rhs);
  template<>
  vk::ShaderInfoTypeAMD fromString<vk::ShaderInfoTypeAMD>(std::string_view rhs);
  template<>
  vk::ShaderStageFlagBits fromString<vk::ShaderStageFlagBits>(std::string_view rhs);
  template<>
  vk::SharingMode fromString<vk::SharingMode>(std::string_view rhs);
  template<>
  vk::SparseImageFormatFlagBits fromString<vk::SparseImageFormatFlagBits>(std::string_view rhs);
  template<>
  vk::SparseMemoryBindFlagBits fromString<vk::SparseMemoryBindFlagBits>(std::string_view rhs);
  template<>
  vk::StencilFaceFlagBits fromString<vk::StencilFaceFlagBits>(std::string_view rhs);
  template<>
  vk::StencilOp fromString<vk::StencilOp>(std::string_view rhs);
  template<>
  vk::StructureType fromString<vk::StructureType>(std::string_view rhs);
  template<>
  vk::SubgroupFeatureFlagBits fromString<vk::SubgroupFeatureFlagBits>(std::string_view rhs);
  template<>
  vk::SubpassContents fromString<vk::SubpassContents>(std::string_view rhs);
  template<>
  vk::SubpassDescriptionFlagBits fromString<vk::SubpassDescriptionFlagBits>(std::string_view rhs);
  template<>
  vk::SurfaceCounterFlagBitsEXT fromString<vk::SurfaceCounterFlagBitsEXT>(std::string_view rhs);
  template<>
  vk::SurfaceTransformFlagBitsKHR fromString<vk::SurfaceTransformFlagBitsKHR>(std::string_view rhs);
  template<>
  vk::SwapchainCreateFlagBitsKHR fromString<vk::SwapchainCreateFlagBitsKHR>(std::string_view rhs);
  template<>
  vk::SystemAllocationScope fromString<vk::SystemAllocationScope>(std::string_view rhs);
  template<>
  vk::TessellationDomainOrigin fromString<vk::TessellationDomainOrigin>(std::string_view rhs);
  template<>
  vk::ValidationCacheHeaderVersionEXT fromString<vk::ValidationCacheHeaderVersionEXT>(std::string_view rhs);
  template<>
  vk::ValidationCheckEXT fromString<vk::ValidationCheckEXT>(std::string_view rhs);
  template<>
  vk::VertexInputRate fromString<vk::VertexInputRate>(std::string_view rhs);
  template<>
  vk::ViewportCoordinateSwizzleNV fromString<vk::ViewportCoordinateSwizzleNV>(std::string_view rhs);
}

#endif // #ifndef ENUMPARSERS_H
