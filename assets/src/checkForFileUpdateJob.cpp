#include "checkForFileUpdateJob.h"
#include "loadHumonFileJob.h"
#include "jobManager.h"
#include "fileRegistry.h"
#include <fstream>
#include <sys/stat.h>

using namespace std;
using namespace overground;


CheckForFileUpdateJob::CheckForFileUpdateJob()
{
  
}


void CheckForFileUpdateJob::reset(FileReference * fileInfo)
{
  this->fileInfo = fileInfo;
}


void CheckForFileUpdateJob::run_impl(JobManager * jobManager)
{
  //  if file mtime > this->objectModTime
  //    make AssetPack
  //    make loadHumonFileJob
  //    schedule the job
  struct stat stats;
  auto path = fileInfo->getPath();
  if (stat(path.c_str(), & stats) != 0)
    { throw runtime_error("Could not stat."); }
  
  if (stats.st_mtime < fileInfo->getModTime())
  {
    auto job = loadHumonFileJobs.next();
    job->reset(fileInfo);

    if (jobManager != nullptr)
      { jobManager->enqueueJob(job); }
    else
      { job->run(); }
  }
}


JobPool<CheckForFileUpdateJob> overground::checkForFileUpdateJobs;
