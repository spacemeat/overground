#ifndef LOADHUMONFILE_H
#define LOADHUMONFILE_H

#include "job.h"
#include "humon.h"
#include "pool.h"
#include "assetPack.h"

namespace overground
{
  class FileReference;
  
  class LoadHumonFileJob : public Job
  {
  public:
    LoadHumonFileJob();

    void reset(FileReference * fileInfo);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    FileReference * fileInfo;
    humon::nodePtr_t rootNode;
  };

  extern JobPool<LoadHumonFileJob> loadHumonFileJobs;
}

#endif // #ifndef LOADHUMONFILE_H

