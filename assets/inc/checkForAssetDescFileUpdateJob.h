#ifndef CHECKFORASSETDESCFILEUPDATEJOB_H
#define CHECKFORASSETDESCFILEUPDATEJOB_H

#include <sys/stat.h>
#include "job.h"
#include "humon.h"
#include "pool.h"
#include "assetPack.h"

namespace overground
{
  class ResourceManager;
  
  class CheckForAssetDescFileUpdateJobs : public Job
  {
  public:
    CheckForAssetDescFileUpdateJobs();

    void reset(ResourceManager * resMan, FileReference * file);

  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
    FileReference * file;
  };

  extern JobPool<CheckForAssetDescFileUpdateJobs> checkForAssetDescFileUpdateJobs;
}


#endif // #ifndef CHECKFORASSETDESCFILEUPDATEJOB_H
