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
      // There's just one config object.
      appConfig.loadFromHumon(rootDict.at<humon::HuNode>("config"));
    }

    // meshes models renderPasses materials shaders
    if (rootDict.hasKey("meshes"))
    {
      auto & meshesDict = rootDict.at<humon::HuDict>("meshes");
      for (size_t i = 0; i < meshesDict.size(); ++i)
      {
        auto key = meshesDict.keyAt(i);
        auto & mesh = Meshes.getOrCreate(key);
        auto job = InitMeshJobs.next();
        job->reset(mesh, meshesDict.at(key));

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }

    if (rootDict.hasKey("models"))
    {
      auto & modelsDict = rootDict.at<humon::HuDict>("models");
      for (size_t i = 0; i < modelsDict.size(); ++i)
      {
        auto key = modelsDict.keyAt(i);
        auto & model = Models.getOrCreate(key);
        auto job = InitModelJobs.next();
        job->reset(model, modelsDict.at(key));

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }
  }
}


JobPool<LoadHumonFileJob> overground::LoadHumonFileJobs;
