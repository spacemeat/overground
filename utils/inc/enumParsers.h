#ifndef ENUMPARSERSCUSTOM_H
#define ENUMPARSERSCUSTOM_H

#include "utils.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "enumParsers-gen.h"

namespace overground
{
  inline std::string to_string(FramePhaseKinds value)
  {
    switch (value)
    {
    case FramePhaseKinds::frameMaintenance: return "frameMaintenance";
    case FramePhaseKinds::graphicsStructure: return "graphicsStructure";
    case FramePhaseKinds::acquireImage: return "acquireImage";
    case FramePhaseKinds::beginComputePass: return "beginComputePass";
    case FramePhaseKinds::endComputePass: return "beginComputePass";
    case FramePhaseKinds::beginRenderPass: return "beginRenderPass";
    case FramePhaseKinds::beginSubpass: return "beginSubpass";
    case FramePhaseKinds::endRenderPass: return "endRenderPass";
    case FramePhaseKinds::submitCommands: return "submitCommands";
    case FramePhaseKinds::present: return "present";
    case FramePhaseKinds::nonBarrierJobQueue: return "nonBarrierJobQueue";
    case FramePhaseKinds::barrierJobQueue: return "barrierJobQueue";
    default: return "invalid";
    }
  }


  template<>
  FramePhaseKinds fromString<FramePhaseKinds>(std::string_view rhs);
}

#endif // #ifndef ENUMPARSERSCUSTOM_H
