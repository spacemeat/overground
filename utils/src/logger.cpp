#include <chrono>
#include <ctime>
#include <fmt/chrono.h>
#include "logger.h"


using namespace std;
using namespace overground;
using namespace logTags;


thread_local int overground::thId = 0;
std::mutex overground::coutMx;


Channel::Channel(loggerTimePoint_t startTime,
  int id, std::string_view name,
  int defaultTags, int filters,
  ostream * outStream, mutex * outStreamMutex,
  bool prefixWithName, bool prefixWithTime, 
  size_t initialSize, bool canGrow)
: startTime(startTime),
  id(id), name(name), defaultTags(defaultTags),
  filters(filters), buffer(),
  outStream(outStream), outStreamMutex(outStreamMutex), 
  prefixWithName(prefixWithName),
  prefixWithTime(prefixWithTime),
  canGrow(canGrow)
{
  buffer.reserve(initialSize);
}


Channel & Channel::setDefaultTags(int tags)
{
  defaultTags = tags;
  return *this;
}


Channel & Channel::setFilters(int filters)
{
  this->filters = filters;
  return *this;
}


Channel & Channel::log(int tags, std::string_view message)
{
  if ((tags & filters) == 0)
    { return *this; }
  
  if (canGrow == false)
  {
    auto sizeToCopy = std::min(
      buffer.capacity() - buffer.size(),
      message.size());

    buffer.append(message, 0, sizeToCopy);
  }
  else
  {
    buffer.append(message);
  }

  if (outStream != nullptr)
  {
    auto && doIt = [this]
    {
      if (prefixWithTime)
      {
        auto nowTime = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<std::chrono::milliseconds>(nowTime - startTime);
        *outStream << fmt::format("{:=6d}> ", ms.count());
      }
      if (prefixWithName)
        { *outStream << fmt::format("{}: ", name); }
      *outStream << str() << endl;  // flushing is fine
    };

    if (outStreamMutex != nullptr)
    {
      lock_guard<mutex> lock(*outStreamMutex);
      doIt();
    }
    else
    {
      doIt();
    }
  }

  return *this;
}


Channel & Channel::log(std::string_view message)
{
  return this->log(defaultTags, message);
}


std::string_view Channel::wholeStr()
{
  return string_view(buffer);
}


std::string_view Channel::str()
{
  auto sb = string_view(buffer);
  sb.remove_prefix(sizeAtLastStr);
  sizeAtLastStr = buffer.size();
  return sb;
}


size_t Channel::spaceLeft()
{
  return buffer.capacity() - buffer.size();
}


void Channel::clear()
{
  buffer.clear();
  sizeAtLastStr = 0;
}


// ----- logger

Logger::Logger(int filters)
: filters(filters)
{
  startTime = chrono::high_resolution_clock::now();
}


int Logger::createChannel(
  std::string_view name,
  int defaultTags, int filters,
  ostream * outStream,
  std::mutex * outStreamMutex,
  bool prefixWithName, bool prefixWithTime, 
  size_t initialSize, bool canGrow)
{
  auto id = channels.size();
  
  lock_guard<std::mutex> lock(channelsMutex);
  channels.emplace_back(
    startTime, id, name,
    defaultTags, filters, 
    outStream, outStreamMutex,
    prefixWithName, prefixWithTime,
    initialSize, canGrow);
  
  channelMap.emplace(name, id);
  return id;
}


Channel & Logger::log(int channel)
{
  return channels[channel];
}


Channel & Logger::log(std::string_view channel)
{
  return channels[channelMap.find(channel)->second];
}


Channel & Logger::log(int channel,
  std::string_view message)
{
  auto & ch = channels[channel];
  auto tags = ch.getDefaultTags();
  if ((tags & filters) == 0)
    { return ch; }

  ch.log(message);
  return ch;
}


Channel & Logger::log(std::string_view channel,
  std::string_view message)
{
  return this->log(channelMap.find(channel)->second, message);
}


Channel & Logger::log(int channel, int tags,
  std::string_view message)
{
  auto & ch = channels[channel];
  if ((tags & filters) == 0)
    { return ch; }
  
  ch.log(tags, message);
  return ch;
}


Channel & Logger::log(std::string_view channel, int tags,
  std::string_view message)
{  
  return this->log(channelMap.find(channel)->second, tags, message);
}


// ----- free fns

// Logger * _logger is defined elsewhere! Make one.

int overground::createLogChannel(
  std::string_view name,
  int defaultTags, int filters,
  ostream * outStream, 
  std::mutex * outStreamMutex,
  bool prefixWithName, bool prefixWithTime,
  size_t initialSize, bool canGrow)
{
  return _logger->createChannel(name, 
    defaultTags, filters, 
    outStream, outStreamMutex, 
    prefixWithName, prefixWithTime,
    initialSize, canGrow);
}


Channel & overground::log(int channel)
{
  return _logger->log(channel);
}


Channel & overground::log(std::string_view channel)
{
  return _logger->log(channel);
}


Channel & overground::log(int channel,
  std::string_view message)
{
  return _logger->log(channel, message);
}


Channel & overground::log(std::string_view channel, 
  std::string_view message)
{
  return _logger->log(channel, message);
}


Channel & overground::log(int channel, int tags, 
  std::string_view message)
{
  return _logger->log(channel, tags, message);
}


Channel & overground::log(std::string_view channel, 
  int tags, std::string_view message)
{
  return _logger->log(channel, tags, message);
}
