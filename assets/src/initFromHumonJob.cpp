#include "initFromHumonJob.h"

using namespace overground;

JobPool <InitFromHumonJob<Mesh>> overground::InitMeshJobs;
JobPool <InitFromHumonJob<Model>> overground::InitModelJobs;
JobPool <InitFromHumonJob<RenderPass>> overground::InitRenderPassJobs;
JobPool <InitFromHumonJob<Material>> overground::InitMaterialJobs;
JobPool <InitFromHumonJob<Shader>> overground::InitShaderJobs;
