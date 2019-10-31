#ifndef MESH_ASSET_H
#define MESH_ASSET_H

#include <string>
#include <fstream>
#include "assetManager.h"

namespace overground
{
  enum class VertexElementType
  {
    eUnknown = 0,
    eFloat
  };

  
  class MeshAsset : public Asset
  {
  public:
    MeshAsset(std::string_view name);
    virtual ~MeshAsset();

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc, asset::asset_t const & asset) override;
    virtual void compileToAss_impl();
    virtual void compileToBuffer_impl(std::byte * buffer) override;

  private:
    bool loadedDataIsSrc = false;
    humon::nodePtr_t loadedData;

    using bufferSpan_t = std::pair<size_t, size_t>;

    // shut up, it's fine
    using vertexFormatElement_t = std::tuple<std::string, VertexElementType, size_t>;
    using vertexFormat_t = std::vector<vertexFormatElement_t>;
    vertexFormat_t vertexFormat;
    bufferSpan_t vbSpan = { 0, 0 };

    // IT'S FINE
    using ibSpanSet_t = std::vector<bufferSpan_t>;
    using submesh_t = std::tuple<size_t, vk::PrimitiveTopology, ibSpanSet_t>;
    stringDict<submesh_t> submeshes;
  };


  MeshAsset::MeshAsset(std::string_view name)
  : Asset(name)
  {
  }


  MeshAsset::~MeshAsset()
  {

  }


  void MeshAsset::loadAssetInfo_impl(path_t path, bool loadFromSrc, asset::asset_t const & asset)
  {
    // -- Get vertex buffer size

    // Loading from mesh .hu or .ass, in a shared codebase. This works because the mesh .ass content is almost identical to the .hu content. ImageAssets and ShaderAssets won't be.
    loadedData = std::move(loadHumonDataFromFile(path));
    loadedDataIsSrc = loadFromSrc;

    auto & meshNode = * loadedData / "mesh";      
    if (meshNode % "name")
    {
      if (auto claimedName = string(meshNode / "name"); 
          claimedName != name())
      {
        log(thId, logTags::warn, fmt::format("Asset '{}' at {} calls itself '{}'. Are we pointing to the right thing?", name(), path, claimedName));
      }
    }

    auto & formatNode = meshNode / "format";
    size_t vertexSize = 0;
    for (size_t i = 0; i < formatNode.size(); ++i)
    {
      auto & elementNode = formatNode / i;
      size_t veSize = 0;
      auto veType = VertexElementType::eUnknown;
      if (string(elementNode / 1) == "float")
      {
        veSize = 4;
        veType = VertexElementType::eFloat;
      }
      size_t veCount = size_t(elementNode / 1);
      vertexSize += veSize * veCount;

      vertexFormat.push_back({ string(elementNode / 0), veType, veCount });
    }

    if (meshNode % "vertices")
    {
      auto & verticesNode = meshNode / "vertices";
      size_t numVertices = verticesNode.size();
      vbSpan = { 0, vertexSize * numVertices };
    }
    else if (meshNode % "verticesBuffer")
    {
      auto & vbNode = meshNode / "verticesBuffer";
      auto offset = size_t(vbNode / 0);
      vbSpan = { size_t(vbNode / 0), size_t(vbNode / 1) };
    }

    // Get index buffers sizes

    size_t totalBufferSize = vbSpan.first + vbSpan.second;
    auto & submeshesNode = meshNode / "submeshes";
    for (int i = 0; i < submeshesNode.size(); ++i)
    {
      auto & submeshNode = submeshesNode / i;
      size_t indexElementSize = size_t(submeshNode / "indexBits") / 8;
      auto topology = fromString<vk::PrimitiveTopology>(std::string(submeshNode / "topology"));

      submesh_t submesh { indexElementSize * 8, topology, {} };
      if (submeshNode % "indices")
      {
        auto & lodNode = submeshNode / "indices";
        for (int j = 0; j < lodNode.size(); ++j)
        {
          auto & facesNode = lodNode / j;
          size_t facesSize = facesNode.size() * indexElementSize;
          std::get<2>(submesh).push_back({totalBufferSize, facesSize});
          totalBufferSize += facesSize;
        }

      }
      else if (submeshNode % "indicesBuffers")
      {
        auto & lodNode = submeshNode / "indices";
        for (int j = 0; j < lodNode.size(); ++j)
        {
          auto & facesNode = lodNode / j;
          size_t facesSize = size_t(facesNode / 1) * indexElementSize;
          std::get<2>(submesh).push_back({totalBufferSize, facesSize});
          totalBufferSize += facesSize;
        }
      }

      submeshes.push_back(submeshesNode.keyAt(i), std::move(submesh));
    }

    bufferSize() = totalBufferSize;
  }

  /*
    mesh.ass should contain:
{
  cube: {
    format: [
      [positions float 3]
      [normals float 3]
      [texcoord0 float 2]
    ]
    verticesBuffer: [0 768]
    submeshes: [
      cubeFaces: {
        indexBits: 16
        topology: triangleList
        indicesBuffers: [[768 72]]   // entry pairs are separate LODs
      }
    ]
  }
}
  */


  void MeshAsset::compileToAss_impl()
  {
    std::ofstream ofs { assFile().path() };

    auto & meshNode = * loadedData / "mesh";
    auto & formatNode = meshNode / "format";
    auto & submeshesNode = meshNode / "submeshes";
    
    ofs << 
R"({{
  cube: {{
    format: [
)";

    for (auto & formatElement : vertexFormat)
    {
      ofs << fmt::format(
R"(      [{} {} {}]
)", 
        std::get<0>(formatElement), 
        std::get<1>(formatElement), 
        std::get<2>(formatElement));
    }

    ofs << fmt::format(
R"(    ]
    verticesBuffer: [{} {}]
    submeshes: [
)", vbSpan.first, vbSpan.second);

    for (auto & [key, idx]: submeshes.keys())
    {
      auto & submesh = submeshes.vect()[idx];
      ofs << fmt::format(
R"(      {}: {{
        indexBits: {}
        topology: {}
        indices: [)", key, std::get<0>(submesh) * 8, to_string(std::get<1>(submesh)));

      auto & lods = std::get<2>(submesh);
      for (int i = 0; i < lods.size(); ++i)
      {
        ofs << fmt::format(
R"([{} {}])", lods[i].first, lods[i].second);
      }

      ofs << fmt::format(
R"(
      }}
)");
    }

    ofs << fmt::format(
R"(    ]
  }}
}}
)");
  }


  void MeshAsset::compileToBuffer_impl(std::byte * buffer)
  {
    size_t bytesAdded = 0;

    auto & meshNode = * loadedData / "mesh";
    auto & verticesNode = meshNode / "vertices";
    auto & formatNode = meshNode / "format";
    size_t numFormats = formatNode.size();
    size_t numFormatsAdded = 0;
    for (size_t i = 0; i < verticesNode.size(); ++i)
    {
      auto & vertexNode = verticesNode / i;

      for (size_t j = 0; j < formatNode.size(); ++j)
      {
        auto & formatElementNode = formatNode / j;
        size_t formatElementCount = formatElementNode / 2;
        size_t vertexElement = 0;
        if (string(formatElementNode / 1) == "float")
        {
          for (size_t k = 0; k < formatElementCount; ++k)
          {
            // lolololol there's no right way to do this
            float * rcb = reinterpret_cast<float *>(buffer + bytesAdded);
            * rcb = float(vertexNode / vertexElement);
            bytesAdded += sizeof(float);

            vertexElement += 1;
          }
        }
        else
        {
          log(thId, logTags::err, fmt::format("Asset '{}' at '{}': invalid vertex format type '{}'.", name(), srcFile().value().path(), string(formatElementNode / 1)));
        }
      }
    }

    auto & submeshesNode = meshNode / "submeshes";
    for (size_t i = 0; i < submeshesNode.size(); ++i)
    {
      auto & submeshNode = submeshesNode / i;
      size_t indexElementSize = size_t(submeshNode / "indexBits") / 8;

      auto & lodNode = submeshNode / "indices";
      for (size_t j = 0; j < lodNode.size(); ++j)
      {
        auto & facesNode = lodNode / j;

        if (indexElementSize == 2)
        {
          for (size_t k = 0; k < facesNode.size(); ++k)
          {
            uint16_t * rcb = reinterpret_cast<uint16_t *>(buffer + bytesAdded);
            * rcb = uint16_t(facesNode / k);
            bytesAdded += sizeof(uint16_t);
          }
        }
        else if (indexElementSize == 4)
        {
          for (size_t k = 0; k < facesNode.size(); ++k)
          {
            uint32_t * rcb = reinterpret_cast<uint32_t *>(buffer + bytesAdded);
            * rcb = uint32_t(facesNode / k);
            bytesAdded += sizeof(uint32_t);
          }
        }
      }
    }
  }
}

#endif // ifndef MESH_ASSET_H
