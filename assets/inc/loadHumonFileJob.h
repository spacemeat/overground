#ifndef LOADHUMONFILE_H
#define LOADHUMONFILE_H

#include "job.h"
#include "humon.h"
#include "pool.h"
#include "assetPack.h"

namespace overground
{
  class LoadHumonFileJob : public Job
  {
  public:
    LoadHumonFileJob();

    void setPath(std::string const & path);
    void setAssetPack(AssetPack * assets);

    std::string const & getPath() { return path; }
    humon::nodePtr_t & getRootNode() { return rootNode; }
    AssetPack * getAssetPack() { return assets; }
  
  protected:
    virtual void run_impl(JobManager * jobManager) override;

  private:
    std::string path;
    humon::nodePtr_t rootNode;
    AssetPack * assets;
  };

  extern JobPool<LoadHumonFileJob> loadHumonFileJobs;
}

#endif // #ifndef LOADHUMONFILE_H

