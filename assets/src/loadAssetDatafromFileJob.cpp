#include "loadAssetDatafromFileJob.h"
#include "initFromHumonJob.h"
#include <fstream>
#include "humon.h"
#include "config.h"
#include "model.h"
#include "mesh.h"
#include "fileRegistry.h"

using namespace std;
using namespace overground;


LoadAssetDatafromFileJob::LoadAssetDatafromFileJob()
{
}


void LoadAssetDatafromFileJob::reset(FileReference * fileInfo)
{
  this->fileInfo = fileInfo;
}


void LoadAssetDatafromFileJob::run_impl(JobManager * jobManager)
{
  sout {} << "LoadAssetDatafromFileJob::run_impl()" << endl;

  resMan->gatherAssetsFromFile(fileInfo);

  string strContent;
  {
    auto ifs = ifstream(fileInfo->getPath());
    if (ifs.is_open())
    {
      strContent = string(
        (istreambuf_iterator<char>(ifs)),
        (istreambuf_iterator<char>()));
    }
  }

  fileInfo->getAssets()->clearContents();

  rootNode = humon::fromString(strContent);
  if (rootNode->isDict())
  {
    auto & rootDict = rootNode->asDict();
    if (rootDict.hasKey("config"))
    {
      auto & config = fileInfo->getAssets()->configs.emplace_back();
      config.setFileInfo(fileInfo);
      auto job = initConfigJobs.next();
      job->reset(config, rootDict / "config");

      if (jobManager != nullptr)
        { jobManager->enqueueJob(job); }
      else
        { job->run(); }
    }

    if (rootDict.hasKey("meshes"))
    {
      auto & meshesDict = rootDict / "meshes";
      for (size_t i = 0; i < meshesDict.size(); ++i)
      {
        auto key = meshesDict.keyAt(i);
        auto & mesh = fileInfo->getAssets()->meshes.emplace_back();
        mesh.setFileInfo(fileInfo);
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
        auto & model = fileInfo->getAssets()->models.emplace_back();
        model.setFileInfo(fileInfo);
        model.setName(key);
        auto job = initModelJobs.next();
        job->reset(model, modelsDict / key);

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }

    // renderPasses materials shaders
  }
}


JobPool<LoadAssetDatafromFileJob> overground::loadAssetDatafromFileJobs;
