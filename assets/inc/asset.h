#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <optional>
#include "asset-gen.h"
#include "fileReference.h"

namespace overground
{
  class Asset
  {
  public:
    Asset(asset::asset_t const & desc);
    virtual ~Asset();

    //void loadAssetInfo();

    void computeImportData();
    void compileToBuffer(std::byte * buffer);

    bool isImage();
    vk::MemoryRequirements getDeviceMemoryRequirements();

    std::string getAssetType() const noexcept;

  protected:
    virtual std::string getAssetType_impl() const noexcept;
    //virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc);

    virtual void computeImportData_impl();
    virtual void compileToBuffer_impl(std::byte * buffer);
    
  public:
    inline std::string_view getName() const noexcept;
    inline std::optional<FileRef> const & getSrcFile() const noexcept;
    inline std::unordered_map<std::string, size_t> const & getTableauRefCounts() const noexcept;
    inline bool isErroneous() const noexcept;
    inline bool & isErroneous() noexcept;
    inline size_t getDataOffset() const noexcept;
    inline size_t getDataSize() const noexcept;
    inline void setDataOffset(size_t size) noexcept;
    inline vk::Format getFormat() const;

    void setNeedToCompile();
  
  private:
    asset::asset_t const & desc;
    std::optional<FileRef> srcFile;
    bool erroneous = false;
    size_t dataOffset;
    size_t dataSize;
    vk::Format format = vk::Format::eUndefined;
  };


#pragma region inline impl

  inline std::string_view Asset::getName() const noexcept
  {
    return desc.name;
  }

  inline std::optional<FileRef> const & Asset::getSrcFile() const noexcept
  {
    return srcFile;
  }

  inline bool Asset::isErroneous() const noexcept
  {
    return erroneous;
  }

  inline size_t Asset::getDataOffset() const noexcept
  {
    return dataOffset;
  }

  inline size_t Asset::getDataSize() const noexcept
  {
    return dataSize;
  }

  inline void Asset::setDataOffset(size_t offset) noexcept
  {
    dataOffset = offset;
  }

  #pragma endregion


  std::unique_ptr<Asset> makeAsset(asset::asset_t const & desc);
}

#endif // #ifndef ASSET_H
