#ifndef ASSETDATA_H
#define ASSETDATA_H

#include "utils.h"
#include "resourceManager.h"

namespace overground
{
  class AssetData
  {
  public:
    AssetData(
      ResourceManager * resMan,
      std::unique_ptr<FileReference> && assetDataPath);

    FileReference * getSrcFile() const
      { return srcFile.get(); }
    FileReference * getCompiledFile() const
      { return compiledFile.get(); }

    void setCompiledPath(path_t compiledPath);

    void updateFileModTimes();
    bool doesNeedCompile();
    bool doesNeedUpdate();
    void forceUpdate();
    bool willUpdate();

  private:
    ResourceManager * resMan;
    std::unique_ptr<FileReference> srcFile;
    std::unique_ptr<FileReference> compiledFile;
    void * memoryBack = nullptr;
  };
}

#endif // #ifndef ASSETDATA_H
