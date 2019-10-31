#include "enumParsers.h"

using namespace std;
using namespace overground;

template<>
FramePhaseKinds overground::fromString<FramePhaseKinds>(std::string_view rhs)
{
  static initializer_list<FramePhaseKinds> il = {
    FramePhaseKinds::frameMaintenance,
    FramePhaseKinds::graphicsStructure,
    FramePhaseKinds::acquireImage,
    FramePhaseKinds::beginComputePass,
    FramePhaseKinds::endComputePass,
    FramePhaseKinds::beginRenderPass,
    FramePhaseKinds::beginSubpass,
    FramePhaseKinds::endRenderPass,
    FramePhaseKinds::submitCommands,
    FramePhaseKinds::present,
    FramePhaseKinds::nonBarrierJobQueue,
    FramePhaseKinds::barrierJobQueue
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}FramePhaseKinds{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}


template<>
BufferStrategy overground::fromString<BufferStrategy>(std::string_view rhs)
{
  static initializer_list<BufferStrategy> il = {
    BufferStrategy::randomTableaux,
    BufferStrategy::lifoTableaux,
    BufferStrategy::randomGroup
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}BufferStrategy{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}
