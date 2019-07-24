#include "config-gen.h"

using namespace overground;
using namespace humon;
using namespace std;


void overground::importPod(
  humon::HuNode const & src, general_t & dest)
{
  if (src % "programName")
  {
    auto & src0 = src / "programName";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.programName = std::move(dst0);
  }
  if (src % "version")
  {
    auto & src0 = src / "version";
    std::array<int, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      int dst1;
      dst1 = (int) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.version = std::move(dst0);
  }
  if (src % "numWorkerThreads")
  {
    auto & src0 = src / "numWorkerThreads";
    int dst0;
    dst0 = (int) src0; // leaf
    dest.numWorkerThreads = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, general_t & dest)
{
  // NOTE: This operation has not been implemented yet.
}


void overground::exportPod(general_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
general_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
general_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "programName: ";
  ss << (src.programName);
  ss << "\n" << indentIn << "version: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.version.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    int const & src0 = src.version[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "numWorkerThreads: ";
  ss << (src.numWorkerThreads);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, general_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
  humon::HuNode const & src, swapchainImageView_t & dest)
{
  if (src % "viewType")
  {
    auto & src0 = src / "viewType";
    vk::ImageViewType dst0;
    dst0 = fromString<vk::ImageViewType>((std::string) src0); // leaf
    dest.viewType = std::move(dst0);
  }
  if (src % "components")
  {
    auto & src0 = src / "components";
    std::array<vk::ComponentSwizzle, 4> dst0;
    for (size_t i0 = 0; i0 < 4; ++i0)
    {
      auto & src1 = src0 / i0;
      vk::ComponentSwizzle dst1;
      dst1 = fromString<vk::ComponentSwizzle>((std::string) src1); // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.components = std::move(dst0);
  }
  if (src % "aspectMask")
  {
    auto & src0 = src / "aspectMask";
    vk::ImageAspectFlagBits dst0;
    dst0 = fromString<vk::ImageAspectFlagBits>((std::string) src0); // leaf
    dest.aspectMask = std::move(dst0);
  }
  if (src % "layerCount")
  {
    auto & src0 = src / "layerCount";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.layerCount = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, swapchainImageView_t & dest)
{
  // NOTE: This operation has not been implemented yet.
}


void overground::exportPod(swapchainImageView_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
swapchainImageView_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
swapchainImageView_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "viewType: ";
  ss << to_string(src.viewType);
  ss << "\n" << indentIn << "components: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.components.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    vk::ComponentSwizzle const & src0 = src.components[i0];
    ss << "\n" << indentIn;
    ss << to_string(src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "aspectMask: ";
  ss << to_string(src.aspectMask);
  ss << "\n" << indentIn << "layerCount: ";
  ss << (src.layerCount);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, swapchainImageView_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
  humon::HuNode const & src, swapchain_t & dest)
{
  if (src % "formatPriorities")
  {
    auto & src0 = src / "formatPriorities";
    std::vector<std::pair<vk::Format, vk::ColorSpaceKHR>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::pair<vk::Format, vk::ColorSpaceKHR> dst1;
      vk::Format dst2a;
      {
        auto & src2a = src1 / 0;
        dst2a = fromString<vk::Format>((std::string) src2a); // leaf
      }
      vk::ColorSpaceKHR dst2b;
      {
        auto & src2b = src1 / 1;
        dst2b = fromString<vk::ColorSpaceKHR>((std::string) src2b); // leaf
      }
      dst1 = std::make_pair(
        std::move(dst2a), std::move(dst2b));
      dst0.push_back(std::move(dst1));
    }
    dest.formatPriorities = std::move(dst0);
  }
  if (src % "numViews")
  {
    auto & src0 = src / "numViews";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.numViews = std::move(dst0);
  }
  if (src % "imageUsages")
  {
    auto & src0 = src / "imageUsages";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.imageUsages = std::move(dst0);
  }
  if (src % "imageSharing")
  {
    auto & src0 = src / "imageSharing";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.imageSharing = std::move(dst0);
  }
  if (src % "pretransform")
  {
    auto & src0 = src / "pretransform";
    vk::SurfaceTransformFlagBitsKHR dst0;
    dst0 = fromString<vk::SurfaceTransformFlagBitsKHR>((std::string) src0); // leaf
    dest.pretransform = std::move(dst0);
  }
  if (src % "windowAlpha")
  {
    auto & src0 = src / "windowAlpha";
    vk::CompositeAlphaFlagBitsKHR dst0;
    dst0 = fromString<vk::CompositeAlphaFlagBitsKHR>((std::string) src0); // leaf
    dest.windowAlpha = std::move(dst0);
  }
  if (src % "presentModePriorities")
  {
    auto & src0 = src / "presentModePriorities";
    std::vector<std::pair<vk::PresentModeKHR, std::uint32_t>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::pair<vk::PresentModeKHR, std::uint32_t> dst1;
      vk::PresentModeKHR dst2a;
      {
        auto & src2a = src1 / 0;
        dst2a = fromString<vk::PresentModeKHR>((std::string) src2a); // leaf
      }
      std::uint32_t dst2b;
      {
        auto & src2b = src1 / 1;
        dst2b = (std::uint32_t) src2b; // leaf
      }
      dst1 = std::make_pair(
        std::move(dst2a), std::move(dst2b));
      dst0.push_back(std::move(dst1));
    }
    dest.presentModePriorities = std::move(dst0);
  }
  if (src % "clipped")
  {
    auto & src0 = src / "clipped";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.clipped = std::move(dst0);
  }
  if (src % "imageView")
  {
    auto & src0 = src / "imageView";
    swapchainImageView_t dst0;
    importPod(src0, dst0);
    dest.imageView = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, swapchain_t & dest)
{
  // NOTE: This operation has not been implemented yet.
}


void overground::exportPod(swapchain_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
swapchain_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
swapchain_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "formatPriorities: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.formatPriorities.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::pair<vk::Format, vk::ColorSpaceKHR> const & src0 = src.formatPriorities[i0];
    {
      ss << "[";
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      vk::Format const & src1 = src0.first;
      ss << "\n" << indentIn;
      ss << to_string(src1);
      ss << indentIn;
      depth -= 1;
    }
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      vk::ColorSpaceKHR const & src1 = src0.second;
      ss << "\n" << indentIn;
      ss << to_string(src1);
    depth -= 1;
    ss << "\n" << prevIndentIn << "]";
    }
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "numViews: ";
  ss << (src.numViews);
  ss << "\n" << indentIn << "imageUsages: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.imageUsages.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.imageUsages[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "imageSharing: ";
  ss << (src.imageSharing);
  ss << "\n" << indentIn << "pretransform: ";
  ss << to_string(src.pretransform);
  ss << "\n" << indentIn << "windowAlpha: ";
  ss << to_string(src.windowAlpha);
  ss << "\n" << indentIn << "presentModePriorities: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.presentModePriorities.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::pair<vk::PresentModeKHR, std::uint32_t> const & src0 = src.presentModePriorities[i0];
    {
      ss << "[";
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      vk::PresentModeKHR const & src1 = src0.first;
      ss << "\n" << indentIn;
      ss << to_string(src1);
      ss << indentIn;
      depth -= 1;
    }
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      std::uint32_t const & src1 = src0.second;
      ss << "\n" << indentIn;
      ss << (src1);
    depth -= 1;
    ss << "\n" << prevIndentIn << "]";
    }
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "clipped: ";
  ss << (src.clipped);
  ss << "\n" << indentIn << "imageView: ";
  ss << print(src.imageView, depth + 1);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, swapchain_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
  humon::HuNode const & src, graphics_t & dest)
{
  if (src % "isConfigured")
  {
    auto & src0 = src / "isConfigured";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.isConfigured = std::move(dst0);
  }
  if (src % "headless")
  {
    auto & src0 = src / "headless";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.headless = std::move(dst0);
  }
  if (src % "fullScreen")
  {
    auto & src0 = src / "fullScreen";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.fullScreen = std::move(dst0);
  }
  if (src % "width")
  {
    auto & src0 = src / "width";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.width = std::move(dst0);
  }
  if (src % "height")
  {
    auto & src0 = src / "height";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.height = std::move(dst0);
  }
  if (src % "vulkanValidationEnabled")
  {
    auto & src0 = src / "vulkanValidationEnabled";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.vulkanValidationEnabled = std::move(dst0);
  }
  if (src % "vulkanValidationLayers")
  {
    auto & src0 = src / "vulkanValidationLayers";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.vulkanValidationLayers = std::move(dst0);
  }
  if (src % "vulkanValidationReports")
  {
    auto & src0 = src / "vulkanValidationReports";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.vulkanValidationReports = std::move(dst0);
  }
  if (src % "vulkanExtensions")
  {
    auto & src0 = src / "vulkanExtensions";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.vulkanExtensions = std::move(dst0);
  }
  if (src % "deviceExtensions")
  {
    auto & src0 = src / "deviceExtensions";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.deviceExtensions = std::move(dst0);
  }
  if (src % "minGraphicsQueues")
  {
    auto & src0 = src / "minGraphicsQueues";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.minGraphicsQueues = std::move(dst0);
  }
  if (src % "desiredGraphicsQueues")
  {
    auto & src0 = src / "desiredGraphicsQueues";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.desiredGraphicsQueues = std::move(dst0);
  }
  if (src % "minComputeQueues")
  {
    auto & src0 = src / "minComputeQueues";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.minComputeQueues = std::move(dst0);
  }
  if (src % "desiredComputeQueues")
  {
    auto & src0 = src / "desiredComputeQueues";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.desiredComputeQueues = std::move(dst0);
  }
  if (src % "minTransferQueues")
  {
    auto & src0 = src / "minTransferQueues";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.minTransferQueues = std::move(dst0);
  }
  if (src % "desiredTransferQueues")
  {
    auto & src0 = src / "desiredTransferQueues";
    unsigned int dst0;
    dst0 = (unsigned int) src0; // leaf
    dest.desiredTransferQueues = std::move(dst0);
  }
  if (src % "minDeviceFeatures")
  {
    auto & src0 = src / "minDeviceFeatures";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.minDeviceFeatures = std::move(dst0);
  }
  if (src % "desiredDeviceFeatures")
  {
    auto & src0 = src / "desiredDeviceFeatures";
    std::vector<std::string> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.desiredDeviceFeatures = std::move(dst0);
  }
  if (src % "swapchain")
  {
    auto & src0 = src / "swapchain";
    swapchain_t dst0;
    importPod(src0, dst0);
    dest.swapchain = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, graphics_t & dest)
{
  // NOTE: This operation has not been implemented yet.
}


void overground::exportPod(graphics_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
graphics_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
graphics_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "isConfigured: ";
  ss << (src.isConfigured);
  ss << "\n" << indentIn << "headless: ";
  ss << (src.headless);
  ss << "\n" << indentIn << "fullScreen: ";
  ss << (src.fullScreen);
  ss << "\n" << indentIn << "width: ";
  ss << (src.width);
  ss << "\n" << indentIn << "height: ";
  ss << (src.height);
  ss << "\n" << indentIn << "vulkanValidationEnabled: ";
  ss << (src.vulkanValidationEnabled);
  ss << "\n" << indentIn << "vulkanValidationLayers: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.vulkanValidationLayers.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.vulkanValidationLayers[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "vulkanValidationReports: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.vulkanValidationReports.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.vulkanValidationReports[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "vulkanExtensions: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.vulkanExtensions.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.vulkanExtensions[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "deviceExtensions: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.deviceExtensions.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.deviceExtensions[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "minGraphicsQueues: ";
  ss << (src.minGraphicsQueues);
  ss << "\n" << indentIn << "desiredGraphicsQueues: ";
  ss << (src.desiredGraphicsQueues);
  ss << "\n" << indentIn << "minComputeQueues: ";
  ss << (src.minComputeQueues);
  ss << "\n" << indentIn << "desiredComputeQueues: ";
  ss << (src.desiredComputeQueues);
  ss << "\n" << indentIn << "minTransferQueues: ";
  ss << (src.minTransferQueues);
  ss << "\n" << indentIn << "desiredTransferQueues: ";
  ss << (src.desiredTransferQueues);
  ss << "\n" << indentIn << "minDeviceFeatures: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.minDeviceFeatures.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.minDeviceFeatures[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "desiredDeviceFeatures: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.desiredDeviceFeatures.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.desiredDeviceFeatures[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "swapchain: ";
  ss << print(src.swapchain, depth + 1);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, graphics_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
  humon::HuNode const & src, config_t & dest)
{
  if (src % "general")
  {
    auto & src0 = src / "general";
    general_t dst0;
    importPod(src0, dst0);
    dest.general = std::move(dst0);
  }
  if (src % "graphics")
  {
    auto & src0 = src / "graphics";
    graphics_t dst0;
    importPod(src0, dst0);
    dest.graphics = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, config_t & dest)
{
  // NOTE: This operation has not been implemented yet.
}


void overground::exportPod(config_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
config_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
config_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "general: ";
  ss << print(src.general, depth + 1);
  ss << "\n" << indentIn << "graphics: ";
  ss << print(src.graphics, depth + 1);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, config_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


