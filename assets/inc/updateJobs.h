#ifndef LOADHUMONFILE_H
#define LOADHUMONFILE_H

#include "job.h"
#include "humon.h"
#include "pool.h"

namespace overground
{
  class ResourceManager;  
  class Asset;


  class CompileAssetJob : public Job
  {
  public:
    CompileAssetJob();

    void reset(ResourceManager * resMan, Asset * asset);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
    Asset * asset;
  };

  extern JobPool<CompileAssetJob> compileAssetJobs;


  class LoadCompiledAssetJob : public Job
  {
  public:
    LoadCompiledAssetJob();

    void reset(ResourceManager * resMan, Asset * asset);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
    Asset * asset;
  };

  extern JobPool<LoadCompiledAssetJob> loadCompiledAssetJobs;


  class SaveCompiledAssetJob : public Job
  {
  public:
    SaveCompiledAssetJob();

    void reset(ResourceManager * resMan, Asset * asset);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
    Asset * asset;
  };

  extern JobPool<SaveCompiledAssetJob> saveCompiledAssetJobs;


  class CreateAssetBufferJob : public Job
  {
  public:
    CreateAssetBufferJob();

    void reset(ResourceManager * resMan);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
  };

  extern JobPool<CreateAssetBufferJob> createAssetBufferJobs;


  class UpdateAssetJob : public Job
  {
  public:
    UpdateAssetJob();

    void reset(ResourceManager * resMan, Asset * asset);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
    Asset * asset;
  };

  extern JobPool<UpdateAssetJob> updateAssetJobs;


  class SyncAssetBufferJob : public Job
  {
  public:
    SyncAssetBufferJob();

    void reset(ResourceManager * resMan);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
  };

  extern JobPool<SyncAssetBufferJob> syncAssetBufferJobs;

  
  class SyncAssetRenderPipelineJob : public Job
  {
  public:
    SyncAssetRenderPipelineJob();

    void reset(ResourceManager * resMan);
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
  };

  extern JobPool<SyncAssetRenderPipelineJob> syncAssetRenderPipelineJobs;
}

#endif // #ifndef LOADHUMONFILE_H

