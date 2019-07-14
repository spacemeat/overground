#include "jobManager.h"
#include "updateJobs.h"
#include "fileReference.h"
#include "resourceManager.h"
#include "asset.h"

using namespace std;
using namespace overground;


// ------------ CompileAssetJob

CheckForAssetDescFileUpdatesJob::CheckForAssetDescFileUpdatesJob(  
  string_view jobTitle,
  ResourceManager * resMan,
  FileReference * file)
: Job(jobTitle), resMan(resMan), file(file)
{
}


void CheckForAssetDescFileUpdatesJob::run_impl(JobManager * jobManager)
{
  resMan->checkForAssetDescFileUpdate(file);
}


JobPool<CheckForAssetDescFileUpdatesJob> overground::checkForAssetDescFileUpdatesJobs;


// ------------ CompileAssetJob

CompileAssetJob::CompileAssetJob(
  string_view jobTitle,
  ResourceManager * resMan, Asset * asset)
: Job(jobTitle), resMan(resMan), asset(asset)
{
}


void CompileAssetJob::run_impl(JobManager * jobManager)
{
  if (asset->isCompiled())
  {
    asset->compileSrcAsset();

    // if asset is cached, save the compiled version to disk in a separate job
    if (asset->isCached())
    {
      auto saveJob = saveCompiledAssetJobs.next(
        "saveCompiledAssetJob", resMan, asset);
      if (jobManager != nullptr)
        { jobManager->enqueueJob(saveJob); }
      else
        { saveJob->run(); }
    }
  }
}


JobPool<CompileAssetJob> overground::compileAssetJobs;


// ------------ LoadCompiledAssetJob

LoadCompiledAssetJob::LoadCompiledAssetJob(
  string_view jobTitle,
  ResourceManager * resMan, Asset * asset)
: Job(jobTitle), resMan(resMan), asset(asset)
{
}


void LoadCompiledAssetJob::run_impl(JobManager * jobManager)
{
  asset->loadCompiledAsset();
}


JobPool<LoadCompiledAssetJob> overground::loadCompiledAssetJobs;


// ------------ SaveCompiledAssetJob

SaveCompiledAssetJob::SaveCompiledAssetJob(
  string_view jobTitle,
  ResourceManager * resMan, Asset * asset)
: Job(jobTitle), resMan(resMan), asset(asset)
{
}


void SaveCompiledAssetJob::run_impl(JobManager * jobManager)
{
  asset->saveCompiledAsset();
}


JobPool<SaveCompiledAssetJob> overground::saveCompiledAssetJobs;


// ------------ CreateAssetBufferJob

CreateAssetBufferJob::CreateAssetBufferJob(
  string_view jobTitle,
  ResourceManager * resMan)
: Job(jobTitle), resMan(resMan)
{
}


void CreateAssetBufferJob::run_impl(JobManager * jobManager)
{
  // TODO: compare asset data requirements against existing asset buffer. Handle all the details about which assets need to be updated, whether sizes change, when to recreate vs reuse the buffer, etc.
  resMan->updateFromFreshAssets(jobManager == nullptr);
}


JobPool<CreateAssetBufferJob> overground::createAssetBufferJobs;


// ------------ UpdateAssetJob

UpdateAssetJob::UpdateAssetJob(
  string_view jobTitle,
  ResourceManager * resMan, Asset * asset)
: Job(jobTitle), resMan(resMan), asset(asset)
{
}


void UpdateAssetJob::run_impl(JobManager * jobManager)
{
  // TODO: If asset is config, apply to engine. If asset is a buffered object, copy (maybe from file) the compiled asset data into the buffer. If asset is a pipeline object, remake relevant graphics pipelines. (?)
  asset->applyToEngine();
}


JobPool<UpdateAssetJob> overground::updateAssetJobs;


// ------------ SyncAssetBufferJob

SyncAssetBufferJob::SyncAssetBufferJob(
  string_view jobTitle,
  ResourceManager * resMan)
: Job(jobTitle), resMan(resMan)
{
}


void SyncAssetBufferJob::run_impl(JobManager * jobManager)
{
  // TODO: slap the buffer on into the device.
}


JobPool<SyncAssetBufferJob> overground::syncAssetBufferJobs;


// ------------ SyncAssetRenderPipelineJob

SyncAssetRenderPipelineJob::SyncAssetRenderPipelineJob(
  string_view jobTitle,
  ResourceManager * resMan)
: Job(jobTitle), resMan(resMan)
{
}


void SyncAssetRenderPipelineJob::run_impl(JobManager * jobManager)
{
  // TODO: diff the relevant objects, and create / replace various pipeline objects as needed. This is currently quite nebulous. Nebulose. Nnnnnebular.
}


JobPool<SyncAssetRenderPipelineJob> overground::syncAssetRenderPipelineJobs;
