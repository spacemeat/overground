#ifndef INITFROMHUMONJOB_H
#define INITFROMHUMONJOB_H

#include "job.h"
#include "jobManager.h"
#include "humon.h"
#include "pool.h"

#include "mesh.h"
#include "model.h"
#include "material.h"
#include "renderPass.h"
#include "shader.h"


namespace overground
{
  template<class RuntimeType>
  class InitFromHumonJob : public Job
  {
  public:
    InitFromHumonJob();
    void reset(RuntimeType & data, humon::HuNode & humon);
    RuntimeType & getData() { return * data; }

  protected:
    virtual humon::HuNode & getHumonObject();
    virtual void run_impl(JobManager * jobManager) override;

  private:
    RuntimeType * data;
    humon::HuNode * humon;
  };


  template<class RuntimeType>
  InitFromHumonJob<RuntimeType>::InitFromHumonJob()
  {
  }


  template<class RuntimeType>
  void InitFromHumonJob<RuntimeType>::reset(
    RuntimeType & data, humon::HuNode & humon)
  {
    this->data = & data;
    this->humon = & humon;
  }


  template<class RuntimeType>
  void InitFromHumonJob<RuntimeType>::run_impl(JobManager * jobManager)
  {
    // RuntimeType can impl loadFromHumon
    data->loadFromHumon(*humon);
  }


  extern JobPool<InitFromHumonJob<Mesh>> initMeshJobs;
  extern JobPool<InitFromHumonJob<Model>> initModelJobs;
  extern JobPool<InitFromHumonJob<RenderPass>> initRenderPassJobs;
  extern JobPool<InitFromHumonJob<Material>> initMaterialJobs;
  extern JobPool<InitFromHumonJob<Shader>> initShaderJobs;
}

#endif // #ifndef INITFROMHUMONJOB_H
