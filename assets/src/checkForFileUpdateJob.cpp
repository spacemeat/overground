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
  sout {} << "CheckForFileUpdateJob::run_impl()" << endl;

  if (fileInfo->doesNeedUpdate())
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
