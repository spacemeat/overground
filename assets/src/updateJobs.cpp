#include "jobManager.h"
#include "updateJobs.h"
#include "resourceManager.h"
#include "asset.h"

using namespace std;
using namespace overground;


// ------------ CompileAssetJob

CompileAssetJob::CompileAssetJob()
{
}


void CompileAssetJob::reset(ResourceManager * resMan, Asset * asset)
{
  this->resMan = resMan;
  this->asset = asset;
}


void CompileAssetJob::run_impl(JobManager * jobManager)
{
  // TODO: load src, translate the src file data into native formats according to other asset values. Asset stores the data; since several assets may use the same AssetData, but load differently, each Asset needs its own memory backing. (?)
  if (asset->isCompiled())
  {
    asset->compileSrcAsset();

    // if asset is cached, save the compiled version to disk in a separate job
    if (asset->isCached())
    {
      auto saveJob = saveCompiledAssetJobs.next();
      saveJob->reset(resMan, asset);
      if (jobManager != false)
        { jobManager->enqueueJob(saveJob); }
      else
        { saveJob->run(); }
    }
  }
}


// ------------ LoadCompiledAssetJob

LoadCompiledAssetJob::LoadCompiledAssetJob()
{
}


void LoadCompiledAssetJob::reset(ResourceManager * resMan, Asset * asset)
{
  this->resMan = resMan;
  this->asset = asset;
}


void LoadCompiledAssetJob::run_impl(JobManager * jobManager)
{
  asset->loadCompiledAsset();
}


// ------------ SaveCompiledAssetJob

SaveCompiledAssetJob::SaveCompiledAssetJob()
{
}


void SaveCompiledAssetJob::reset(ResourceManager * resMan, Asset * asset)
{
  this->resMan = resMan;
  this->asset = asset;
}


void SaveCompiledAssetJob::run_impl(JobManager * jobManager)
{
  asset->saveCompiledAsset();
}


// ------------ CreateAssetBufferJob

CreateAssetBufferJob::CreateAssetBufferJob()
{
}


void CreateAssetBufferJob::reset(ResourceManager * resMan)
{
  this->resMan = resMan;
}


void CreateAssetBufferJob::run_impl(JobManager * jobManager)
{
  // TODO: compare asset data requirements against existing asset buffer. Handle all the details about which assets need to be updated, whether sizes change, when to recreate vs reuse the buffer, etc.
}


// ------------ UpdateAssetJob

UpdateAssetJob::UpdateAssetJob()
{
}


void UpdateAssetJob::reset(ResourceManager * resMan, Asset * asset)
{
  this->resMan = resMan;
  this->asset = asset;
}


void UpdateAssetJob::run_impl(JobManager * jobManager)
{
  // TODO: If asset is config, apply to engine. If asset is a buffered object, copy (maybe from file) the compiled asset data into the buffer. If asset is a pipeline object, remake relevant graphics pipelines. (?)
  asset->applyToEngine();
}


// ------------ SyncAssetBufferJob

SyncAssetBufferJob::SyncAssetBufferJob()
{
}


void SyncAssetBufferJob::reset(ResourceManager * resMan)
{
  this->resMan = resMan;
}


void SyncAssetBufferJob::run_impl(JobManager * jobManager)
{
  // TODO: slap the buffer on into the device.
}


// ------------ SyncAssetRenderPipelineJob

SyncAssetRenderPipelineJob::SyncAssetRenderPipelineJob()
{
}


void SyncAssetRenderPipelineJob::reset(ResourceManager * resMan)
{
  this->resMan = resMan;
}


void SyncAssetRenderPipelineJob::run_impl(JobManager * jobManager)
{
  // TODO: diff the relevant objects, and create / replace various pipeline objects as needed. This is currently quite nebulous. Nebulose. Nnnnnebular.
}
