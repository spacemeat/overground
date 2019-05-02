#ifndef CHECKFORFILEUPDATEJOB_H
#define CHECKFORFILEUPDATEJOB_H

#include <sys/stat.h>
#include "job.h"
#include "humon.h"
#include "pool.h"
#include "assetPack.h"

namespace overground
{
  class CheckForFileUpdateJob : public Job
  {
  public:
    CheckForFileUpdateJob();

    void reset(FileReference * fileInfo);
//    void setPath(std::string const & path);
//    void setAssetPack(AssetPack * assets);
//    void setObjectModTime(time_t mTime);

  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    FileReference * fileInfo;
  };

  extern JobPool<CheckForFileUpdateJob> checkForFileUpdateJobs;
}


#endif // #ifndef CHECKFORFILEUPDATEJOB_H
