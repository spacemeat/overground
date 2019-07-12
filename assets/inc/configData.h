#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <string>
#include <vector>
#include "utils.h"

namespace overground
{
  struct ConfigData
  {
    enum class Deltas : int
    {
      None                = 0,
      JobManagement       = 1 << 0,
      Window              = 1 << 1,
      WindowExtents       = 1 << 2,
      VulkanInstance      = 1 << 3,
      PhysicalDevice      = 1 << 4,
      LogicalDevice       = 1 << 5,
      Swapchain           = 1 << 6,


      Framebuffer         = 1 << 7,
      RenderPasses        = 1 << 8,
      NumConcurrentFrames = 1 << 9,
      GraphicsPipelines   = 1 << 10,
    };

    void clearDiffs() { lastDiffs = Deltas::None; }

    void applyDiff(Deltas diff) { lastDiffs |= diff; }

    Deltas getDiffs() const { return lastDiffs; }

    void loadFromHumon(humon::HuNode const & src);
    void integrate(ConfigData const & rhs);
    std::string print() const;

  private:
//    FileReference * fileInfo;
    Deltas lastDiffs = Deltas::None;
  
  public:

    struct General
    {
      std::string programName;
      version_t version;
      int numWorkerThreads;
    } general;

    struct Graphics
    {
      bool isConfigured = false;
      bool headless;
      bool fullScreen;
      unsigned int width;
      unsigned int height;
      bool vulkanValidationEnabled;
      std::vector<std::string> vulkanValidationLayers;
      std::vector<std::string> vulkanValidationReports;
      std::vector<std::string> vulkanExtensions;
      std::vector<std::string> deviceExtensions;
      unsigned int minGraphicsQueues;
      unsigned int desiredGraphicsQueues;
      unsigned int minComputeQueues;
      unsigned int desiredComputeQueues;
      unsigned int minTransferQueues;
      unsigned int desiredTransferQueues;
      std::vector<std::string> minDeviceFeatures;
      std::vector<std::string>
      desiredDeviceFeatures;
      
      struct Swapchain
      {
        std::vector<std::pair<std::string, std::string>> formatPriorities;
        unsigned int numViews;
        std::vector<std::string> imageUsages;
        bool imageSharing;
        std::string pretransform;
        std::string windowAlpha;
        std::vector<std::pair<std::string, unsigned int>> presentModePriorities;
        bool clipped;
      } swapchain;

    } graphics;
  };

  extern std::ostream & operator << (
    std::ostream & stream, 
    ConfigData const & rhs);
}


#endif // ! #ifndef CONFIG_DATA_H
