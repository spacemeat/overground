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

    void loadAssetInfo();

    void compileToAss();
    void compileToBuffer(std::byte * buffer);

    bool isImage();
    vk::MemoryRequirements getDeviceMemoryRequirements();

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc);

    virtual void compileToAss_impl();
    virtual void compileToBuffer_impl(std::byte * buffer);
    
  public:
    inline std::string_view name() const noexcept;
    inline std::optional<FileRef> const & srcFile() const noexcept;
    inline FileRef const & assFile() const noexcept;
    inline std::unordered_map<std::string, size_t> const & tableauRefCounts() const noexcept;
    inline bool erroneous() const noexcept;
    inline bool & erroneous() noexcept;
    inline size_t bufferOffset() const noexcept;
    inline size_t bufferSize() const noexcept;

    inline void removeReferencingTableau(std::string_view tableauName) noexcept;
  
  protected:
    inline size_t & bufferOffset() noexcept;
    inline size_t & bufferSize() noexcept;

  private:
    asset::asset_t & desc_;
    std::optional<FileRef> srcFile_;
    FileRef assFile_;
    std::unordered_map<std::string, size_t> tableauRefCounts_;
    bool erroneous_ = false;
    size_t bufferOffset_;
    size_t bufferSize_;
  };


#pragma region inline impl

  inline std::string_view Asset::name() const noexcept
  {
    return desc_.name;
  }

  inline std::optional<FileRef> const & Asset::srcFile() const noexcept
  {
    return srcFile_;
  }

  inline FileRef const & Asset::assFile() const noexcept
  {
    return assFile_;
  }


  inline std::unordered_map<std::string, size_t> const & Asset::tableauRefCounts() const noexcept
  {
    return tableauRefCounts_;
  }


  inline bool Asset::erroneous() const noexcept
  {
    return erroneous_;
  }

  inline size_t Asset::bufferOffset() const noexcept
  {
    return bufferOffset_;
  }

  inline size_t Asset::bufferSize() const noexcept
  {
    return bufferSize_;
  }

  inline void Asset::removeReferencingTableau(std::string_view tableauName) noexcept
  {
    // TODO: Remove the std::string()
    if (auto it = tableauRefCounts_.find(std::string(tableauName));
        it != tableauRefCounts_.end())
    {
      if (it->second > 0)
      {
        it->second -= 1;
        if (it->second == 0)
        {
    // TODO: Remove the std::string()
          tableauRefCounts_.erase(std::string(tableauName));

          if (tableauRefCounts_.size() == 0)
          {
            // We can unload this asset.
            
          }
        }
      }
    }
  }

  inline size_t & Asset::bufferOffset() noexcept
  {
    return bufferOffset_;
  }

  inline size_t & Asset::bufferSize() noexcept
  {
    return bufferSize_;
  }

  #pragma endregion


  using makeAssetFn_t = std::function<
    std::unique_ptr<Asset>(
      std::string_view name
  )>;

  template <class T> // TODO: requires T derived from Asset
  static std::unique_ptr<T> makeAsset(std::string_view name)
  {
    return name;
  }
}

#endif // #ifndef ASSET_H
