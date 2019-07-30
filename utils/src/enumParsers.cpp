#include "enumParsers.h"

using namespace std;
using namespace overground;

template<>
FramePhaseKinds overground::fromString<FramePhaseKinds>(std::string_view rhs)
{
  static initializer_list<FramePhaseKinds> il = {
    FramePhaseKinds::maintenance,
    FramePhaseKinds::top,
    FramePhaseKinds::beginComputePass,
    FramePhaseKinds::endComputePass,
    FramePhaseKinds::beginRenderPass,
    FramePhaseKinds::beginSubpass,
    FramePhaseKinds::endRenderPass,
    FramePhaseKinds::submitCommands,
    FramePhaseKinds::present,
    FramePhaseKinds::jobQueue
  };

  for (auto val : il)
  {
    if (to_string(val) == rhs)
      { return val; }
  }

  throw runtime_error(fmt::format("Invalid value {}{}{} for {}FramePhaseKinds{}", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));
}
