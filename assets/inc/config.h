#ifndef CONFIG_H
#define CONFIG_H

#include "pool.h"
#include "humon.h"
#include "utils.h"

namespace overground
{
  class Config
  {
  public:
    enum class Deltas : int
    {
      None          = 0,
      JobManagement = 1 << 0,
      Window        = 1 << 1,
      Device        = 1 << 2
    };

    void setName(std::string const & name)
      { this->name = name; }

    void loadFromHumon(humon::HuNode const & src);

    Deltas integrate(Config & rhs);

    void print(std::ostream & sout) const;
  
//  private:
    std::string name;
    struct General
    {
      std::string programName;
      int numWorkerThreads;
    } general;

    struct Graphics
    {
      bool fullScreen;
      unsigned int width;
      unsigned int height;
      std::vector<std::string> extensions;
      bool debugging;
//      int numGraphicsThreads;
    } graphics;

  };

  extern std::ostream & operator << (std::ostream & stream, Config const & rhs);
}

#endif // #ifndef CONFIG_H
