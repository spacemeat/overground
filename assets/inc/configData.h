#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <string>
#include <vector>
#include "utils.h"
#include "config-gen.h"

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
    Deltas lastDiffs = Deltas::None;
  
  public:

    config_t config;
  };


  extern std::ostream & operator << (
    std::ostream & stream, 
    ConfigData const & rhs);
}


#endif // ! #ifndef CONFIG_DATA_H
