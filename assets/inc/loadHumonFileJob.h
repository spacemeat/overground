#ifndef LOADHUMONFILE_H
#define LOADHUMONFILE_H

#include "job.h"
#include "humon.h"
#include "pool.h"

namespace overground
{
  class LoadHumonFileJob : public Job
  {
  public:
    LoadHumonFileJob();

    void setPath(std::string const & path);

    std::string const & getPath() { return path; }
    humon::nodePtr_t & getRootNode() { return rootNode; }
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    std::string path;
    humon::nodePtr_t rootNode;
  };

  extern JobPool<LoadHumonFileJob> LoadHumonFileJobs;
}

#endif // #ifndef LOADHUMONFILE_H

