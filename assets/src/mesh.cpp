#include "mesh.h"
#include "config.h"
#include <numeric>
#include "pool.h"
#include "humon.h"

using namespace std;
using namespace humon;
using namespace overground;


Mesh::Mesh()
{
}


void Mesh::loadFromHumon(HuNode const & src)
{
  auto & configSrc = src.asDict();

  //HuList & positions;
  //HuList & normals;
  //vector<HuList &> tex;
  bool hasPositions = false;
  bool hasNormals = false;
  size_t hasTex = 0;
  
  if (configSrc.hasKey("positions"))
  {
    auto & positions = configSrc.at<HuList>("positions");
    numVertices = positions.size();
    positionSize = positions.at<HuList>(0).size();
    hasPositions = true;
  }

  if (configSrc.hasKey("normals"))
  {
    auto & normals = configSrc.at<HuList>("normals");
    assert(numVertices == normals.size());
    normalSize = normals.at<HuList>(0).size();
    hasNormals = true;
  }
  
  if (configSrc.hasKey("tex"))
  {
    auto & list = configSrc.at<HuList>("tex");
    auto numTexCoords = list.size();
    for (size_t i = 0; i < numTexCoords; ++i)
    {
      auto & tex = list.at<HuList>(i);
      assert(numVertices == tex.size());
      texSizes[i] = tex.at<HuList>(0).size();
      hasTex += 1;
    }
  }

  bytesPerVertex = (positionSize + normalSize + 
    accumulate(texSizes.begin(), texSizes.end(), 0)) * 4;
  verticesMemSize = bytesPerVertex * numVertices;

  if (configSrc.hasKey("submeshes"))
  {
    auto & submeshesHu = configSrc.at<HuDict>("submeshes");
    auto numSubmeshes = submeshes.size();
    submeshes.resize(numSubmeshes);

    for (size_t i = 0; i < numSubmeshes; ++i)
    {
      Submesh & submesh = submeshes[i];

      auto & submeshHu = submeshesHu.at(i).asDict();
      if (submeshHu.hasKey("indexBits"))
        { submesh.indexBits = submeshHu.at<HuValue>("indexBits").getLong(); }

      if (submeshHu.hasKey("topology"))
      {
        auto topologyV = submeshHu.at<HuValue>("topology").getString();
        if (topologyV == "pointList")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST; }
        else if (topologyV == "lineList")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST; }
        else if (topologyV == "lineStrip")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; }
        else if (topologyV == "triangleList")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; }
        else if (topologyV == "triangleStrip")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; }
        else if (topologyV == "triangleFan")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN; }
        else if (topologyV == "lineListWithAdjacency")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY; }
        else if (topologyV == "lineStripWithAdjacency")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY; }
        else if (topologyV == "triangleListWithAdjacency")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY; }
        else if (topologyV == "triangleStripWithAdjacency")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY; }
        else if (topologyV == "patchList")
          { submesh.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST; }
      }

      if (submeshHu.hasKey("indices"))
      {
        auto & lodsHu = submeshHu.at<HuList>("indices");
        submesh.numIndices.resize(lodsHu.size());

        for (size_t j = 0; j < lodsHu.size(); ++j)
        {
          auto & indicesHu = lodsHu.at<HuList>(i);
          submesh.numIndices[j] = indicesHu.size();
        }

        submesh.indicesMemSize = (submesh.indexBits >> 3) * 
          accumulate(submesh.numIndices.begin(), submesh.numIndices.end(), 0);
        indicesMemSize += submesh.indicesMemSize;
      }
    }
  }

  // TODO: Get memory buffer from managed source.
  binaryData.resize(verticesMemSize + indicesMemSize);

  // Populate binaryData.data() with data, D.A.T.A. Yes, Captain.
  int8_t * pBuf = binaryData.data();
  for (size_t i = 0; i < numVertices; ++i)
  {
    if (hasPositions)
    {
      auto & positions = configSrc.at<HuList>("positions");
      auto & vecP = positions.at<HuList>(i);
      for (size_t j = 0; j < positionSize; ++j)
      {
        * (float *) pBuf = vecP.at<HuValue>(j).getFloat();
        pBuf += sizeof(float);
      }
    }

    if (hasNormals)
    {
      auto & normals = configSrc.at<HuList>("normals");
      auto & vecN = normals.at<HuList>(i);
      for (size_t j = 0; j < normalSize; ++j)
      {
        * (float *) pBuf = vecN.at<HuValue>(j).getFloat();
        pBuf += sizeof(float);
      }
    }

    for (size_t j = 0; j < texSizes.size(); ++j)
    {
      auto & texes = configSrc.at<HuList>("tex");
      auto & uv = texes.at<HuList>(j).at<HuList>(i);
      for (size_t k = 0; k < texSizes[j]; ++k)
      {
        * (float *) pBuf = uv.at<HuValue>(k).getFloat();
        pBuf += sizeof(float);
      }
    }
  }

  if (configSrc.hasKey("submeshes"))
  {
    auto & submeshesHu = configSrc.at<HuDict>("submeshes");
    for (size_t i = 0; i < submeshes.size(); ++i)
    {
      Submesh & submesh = submeshes[i];
      auto & lodsHu = submeshesHu.at<HuDict>(i).at<HuList>("indices");
      for (size_t j = 0; j < submesh.numIndices.size(); ++j)
      {
        auto & indicesHu = lodsHu.at<HuList>(j);
        for (size_t k = 0; k < submesh.numIndices[j]; ++k)
        {
          if (submesh.indexBits == 16)
          {
            * (uint16_t *) pBuf = static_cast<uint16_t>(indicesHu.at<HuValue>(k).getLong());
            pBuf += sizeof(uint16_t);
          }
          else
          {
            * (uint32_t *) pBuf = static_cast<uint32_t>(indicesHu.at<HuValue>(k).getLong());
            pBuf += sizeof(uint32_t);
          }
        }
      }
    }
  }

  assert(size_t(pBuf - binaryData.data()) == binaryData.size());

  // TODO: Update the binary cache.
  

  // TODO: Mark mesh dirty for recreation.
}


ObjectMap<Mesh> overground::Meshes;

