#ifndef CONFIG_H
#define CONFIG_H

#include "pool.h"
#include "humon.h"

namespace overground
{
  class Config
  {
  public:
    Config();

    void setName(std::string const & name)
      { this->name = name; }

    void loadFromHumon(humon::HuNode const & src);
  
  private:
    std::string name;
    struct General
    {
      int numWorkerThreads;
    } general;

    struct Graphics
    {
      bool windowedMode;
      int width;
      int height;
      std::vector<std::string> extensions;
      bool debugging;
      int numGraphicsThreads;
    } graphics;

  };

  extern Config appConfig;
}

#endif // #ifndef CONFIG_H
