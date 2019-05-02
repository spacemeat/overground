#include "initFromHumonJob.h"

using namespace overground;

JobPool <InitFromHumonJob<Config>> overground::initConfigJobs;
JobPool <InitFromHumonJob<Mesh>> overground::initMeshJobs;
JobPool <InitFromHumonJob<Model>> overground::initModelJobs;
JobPool <InitFromHumonJob<RenderPass>> overground::initRenderPassJobs;
JobPool <InitFromHumonJob<Material>> overground::initMaterialJobs;
JobPool <InitFromHumonJob<Shader>> overground::initShaderJobs;
