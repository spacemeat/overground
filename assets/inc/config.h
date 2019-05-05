#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include "pool.h"
#include "humon.h"
#include "utils.h"

namespace overground
{
  class FileReference;

  class Config
  {
  public:
    enum class Deltas : int
    {
      None            = 0,
      JobManagement   = 1 << 0,
      Window          = 1 << 1,
      VulkanInstance  = 1 << 2,
      PhysicalDevice  = 1 << 3,
      LogicalDevice   = 1 << 4,
    };

    void setFileInfo(FileReference * newFileInfo);
    FileReference * getFileInfo() { return fileInfo; }

    void setName(std::string const & name)
      { this->name = name; }

    void loadFromHumon(humon::HuNode const & src);

    void integrate(Config const & rhs);

    void print(std::ostream & sout) const;

    // public members. TODO: better

    FileReference * fileInfo;
    Deltas lastDiffs = Deltas::None;

    std::string name;
    struct General
    {
      std::string programName;
      version_t version;
      int numWorkerThreads;
    } general;

    struct Graphics
    {
      bool fullScreen;
      unsigned int width;
      unsigned int height;
      bool validationEnabled;
      std::vector<std::string> extensions;
      std::vector<std::string> deviceExtensions;
      std::vector<std::string> validationLayers;
//      int numGraphicsThreads;
    } graphics;

  };

  extern std::ostream & operator << (std::ostream & stream, Config const & rhs);
}

#endif // #ifndef CONFIG_H
