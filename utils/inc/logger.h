#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <fmt/core.h>
#include <mutex>
#include <ostream>

namespace overground
{
  namespace logTags
  {
    enum LogTag {
      sys       = 1 << 0,
      info      = 1 << 1,
      verb      = 1 << 2,
      dbg       = 1 << 3,
      err       = 1 << 4,
      warn      = 1 << 5,

      dev       = sys | info | dbg | err | warn,
      spam      = sys | info | verb | dbg | err | warn
    };
  }


  extern thread_local int thId;
  extern std::mutex coutMx;

  using loggerTimePoint_t = std::chrono::time_point
    <std::chrono::system_clock>;

  // logging channel. Set up one per thread, maybe, or one per separate subsystem. Recommended to use createLogChannel() below, which operates on an internal Logger instance, which provides broader filtering.

  class Channel
  {
  public:
    Channel(loggerTimePoint_t startTime,
      int id, std::string_view name,
      int defaultTags = logTags::LogTag::info,
      int filters = logTags::LogTag::spam,
      std::ostream * outStream = nullptr,
      std::mutex * outStreamMutex = nullptr,
      bool prefixWithName = true, 
      bool prefixWithTime = true,
      size_t initialSize = (1 << 20), bool canGrow = true);
    
    int getDefaultTags() { return defaultTags; }
    int getFilters() { return filters; }
    Channel & setDefaultTags(int tags);
    Channel & setFilters(int filters);

    Channel & log(int tags, std::string_view message);
    Channel & log(std::string_view message);

    std::string_view wholeStr();
    std::string_view str();
    size_t spaceLeft();
    void clear();

  private:
    loggerTimePoint_t startTime;
    size_t id;
    std::string name;
    int defaultTags;
    int filters;
    std::string buffer;
    std::ostream * outStream = nullptr;
    std::mutex * outStreamMutex = nullptr;
    bool prefixWithName;
    bool prefixWithTime;
    bool canGrow;

    size_t sizeAtLastStr;
  };

  // owns n channels, and global filters

  class Logger
  {
  public:
    Logger(int filters = logTags::LogTag::spam);

    int createChannel(std::string_view name,
      int defaultTags = logTags::LogTag::info,
      int filters = logTags::LogTag::spam, 
      std::ostream * outStream = nullptr,
      std::mutex * outStreamMutex = nullptr,
      bool prefixWithName = true, 
      bool prefixWithTime = true,
      size_t initialSize = (1 << 20), bool canGrow = true);

    Channel & log(int channel);
    Channel & log(std::string_view channel);

    Channel & log(int channel, std::string_view message);
    Channel & log(std::string_view channel,
      std::string_view message);

    Channel & log(int channel, int tags,
      std::string_view message);
    Channel & log(std::string_view channel, int tags, 
      std::string_view message);

  private:
    std::map<std::string, int, std::less<>> channelMap;
    std::vector<Channel> channels;
    int nextChannel = 0;
    int filters;
    loggerTimePoint_t startTime;

    std::mutex channelsMutex;
  };

  // free functions that operate on an internal instance.

  extern int createLogChannel(std::string_view name,
    int defaultTags = logTags::LogTag::info,
    int filters = logTags::LogTag::spam,
    std::ostream * outStream = nullptr,
    std::mutex * outStreamMutex = nullptr,
    bool prefixWithName = true, 
    bool prefixWithTime = true,
    size_t initialSize = (1 << 20), bool canGrow = true);

  extern Channel & log(int channel);
  extern Channel & log(std::string_view channel);

  extern Channel & log(int channel,
    std::string_view message);
  extern Channel & log(std::string_view channel, 
    std::string_view message);

  extern Channel & log(int channel, int tags, 
    std::string_view message);
  extern Channel & log(std::string_view channel, 
    int tags, std::string_view message);
}


#endif // #ifndef LOGGER_H