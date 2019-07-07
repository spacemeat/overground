#include "checkForFileUpdateJob.h"
#include "loadAssetDatafromFileJob.h"
#include "resourceManager.h"
#include "jobManager.h"
#include "fileRegistry.h"

using namespace std;
using namespace overground;


CheckForAssetDescFileUpdateJobs::CheckForAssetDescFileUpdateJobs()
{
  
}


void CheckForAssetDescFileUpdateJobs::reset(ResourceManager * resMan, FileReference * file)
{
  this->resMan = resMan;
  this->file = file;
}


void CheckForAssetDescFileUpdateJobs::run_impl(JobManager * jobManager)
{
  sout {} << "CheckForAssetDescFileUpdateJobs::run_impl()" << endl;

  resMan->checkForAssetDescFileUpdate(file);
}


JobPool<CheckForAssetDescFileUpdateJobs> overground::checkForAssetDescFileUpdateJobs;
