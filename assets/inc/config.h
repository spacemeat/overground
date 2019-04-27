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

    /*
    Config();
    ~Config();
    Config(Config const & rhs);
    Config(Config && rhs);
    Config & operator =(Config const & rhs);
    Config & operator =(Config && rhs);
    */

    void setName(std::string const & name)
      { this->name = name; }

    void loadFromHumon(humon::HuNode const & src);

    Deltas integrate(Config & rhs);

    void print(std::ostream & sout) const;
  
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
//      int numGraphicsThreads;
    } graphics;

  };

  extern std::ostream & operator << (std::ostream & stream, Config const & rhs);
}

#endif // #ifndef CONFIG_H
