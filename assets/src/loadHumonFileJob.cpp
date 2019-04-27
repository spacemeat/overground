#include "loadHumonFileJob.h"
#include "initFromHumonJob.h"
#include <fstream>
#include "humon.h"
#include "config.h"
#include "model.h"
#include "mesh.h"

using namespace std;
using namespace overground;


LoadHumonFileJob::LoadHumonFileJob()
{
}


void LoadHumonFileJob::setPath(std::string const & path)
{
  this->path = path;
}


void LoadHumonFileJob::setAssetPack(AssetPack * assets)
{
  this->assets = assets;
}


void LoadHumonFileJob::run_impl(JobManager * jobManager)
{
  string strContent;
  {
    auto ifs = ifstream(path);
    if (ifs.is_open())
    {
      strContent = string( (istreambuf_iterator<char>(ifs)),
                          (istreambuf_iterator<char>()));
                // TODO: Try ifs.begin(), ifs.end()
    }
  }

  rootNode = humon::fromString(strContent);
  if (rootNode->isDict())
  {
    auto & rootDict = rootNode->asDict();
    if (rootDict.hasKey("config"))
    {
      auto & config = assets->configs.emplace_back();
      config.loadFromHumon(rootDict / "config");
    }

    // meshes models renderPasses materials shaders
    if (rootDict.hasKey("meshes"))
    {
      auto & meshesDict = rootDict / "meshes";
      for (size_t i = 0; i < meshesDict.size(); ++i)
      {
        auto key = meshesDict.keyAt(i);
        auto & mesh = assets->meshes.emplace_back();
        mesh.setName(key);
        auto job = initMeshJobs.next();
        job->reset(mesh, meshesDict / key);

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }

    if (rootDict.hasKey("models"))
    {
      auto & modelsDict = rootDict / "models";
      for (size_t i = 0; i < modelsDict.size(); ++i)
      {
        auto key = modelsDict.keyAt(i);
        auto & model = assets->models.emplace_back();
        auto job = initModelJobs.next();
        job->reset(model, modelsDict / key);

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }
  }
}


JobPool<LoadHumonFileJob> overground::loadHumonFileJobs;
