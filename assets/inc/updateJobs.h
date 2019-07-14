#ifndef LOADHUMONFILE_H
#define LOADHUMONFILE_H

#include "job.h"
#include "humon.h"
#include "pool.h"

namespace overground
{
  class FileReference;
  class ResourceManager;
  class Asset;


  class CheckForAssetDescFileUpdatesJob : public Job
  {
  public:
    CheckForAssetDescFileUpdatesJob(
      std::string_view jobTitle,
      ResourceManager * resMan, 
      FileReference * file);

  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
    FileReference * file;
  };

  extern JobPool<CheckForAssetDescFileUpdatesJob> checkForAssetDescFileUpdatesJobs;


  class CompileAssetJob : public Job
  {
  public:
    CompileAssetJob(
      std::string_view jobTitle,
      ResourceManager * resMan, 
      Asset * asset);
  
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
    LoadCompiledAssetJob(
      std::string_view jobTitle,
      ResourceManager * resMan, 
      Asset * asset);

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
    SaveCompiledAssetJob(
      std::string_view jobTitle,
      ResourceManager * resMan, 
      Asset * asset);

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
    CreateAssetBufferJob(
      std::string_view jobTitle,
      ResourceManager * resMan);

  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
  };

  extern JobPool<CreateAssetBufferJob> createAssetBufferJobs;


  class UpdateAssetJob : public Job
  {
  public:
    UpdateAssetJob(
      std::string_view jobTitle,
      ResourceManager * resMan, 
      Asset * asset);

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
    SyncAssetBufferJob(
      std::string_view jobTitle,
      ResourceManager * resMan);

  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
  };

  extern JobPool<SyncAssetBufferJob> syncAssetBufferJobs;

  
  class SyncAssetRenderPipelineJob : public Job
  {
  public:
    SyncAssetRenderPipelineJob(
      std::string_view jobTitle,
      ResourceManager * resMan);

  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    ResourceManager * resMan;
  };

  extern JobPool<SyncAssetRenderPipelineJob> syncAssetRenderPipelineJobs;
}

#endif // #ifndef LOADHUMONFILE_H

