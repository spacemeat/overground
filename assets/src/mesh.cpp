#include "mesh.h"
#include "config.h"
#include <numeric>
#include "pool.h"
#include "humon.h"
#include "fileRegistry.h"

using namespace std;
using namespace humon;
using namespace overground;


void Mesh::setFileInfo(FileReference * newFileInfo)
{
  fileInfo = newFileInfo;
  fileInfo->addRef();
}


void Mesh::loadFromHumon(HuNode const & src)
{
  //HuList & positions;
  //HuList & normals;
  //vector<HuList &> tex;
  bool hasPositions = false;
  bool hasNormals = false;
  size_t hasTex = 0;
  
  if (src % "positions")
  {
    auto & positions = src / "positions";
    numVertices = positions.size();
    positionSize = positions / 0;
    hasPositions = true;
  }

  if (src % "normals")
  {
    auto & normals = src / "normals";
    assert(numVertices == normals.size());
    normalSize = normals / 0;
    hasNormals = true;
  }
  
  if (src % "tex")
  {
    auto & list = src / "tex";
    auto numTexCoords = list.size();
    for (size_t i = 0; i < numTexCoords; ++i)
    {
      auto & tex = list / i;
      assert(numVertices == tex.size());
      texSizes[i] = tex / 0;
      hasTex += 1;
    }
  }

  bytesPerVertex = (positionSize + normalSize + 
    accumulate(texSizes.begin(), texSizes.end(), 0)) * 4;
  verticesMemSize = bytesPerVertex * numVertices;

  if (src % "submeshes")
  {
    auto & submeshesHu = src / "submeshes";
    auto numSubmeshes = submeshes.size();
    submeshes.resize(numSubmeshes);

    for (size_t i = 0; i < numSubmeshes; ++i)
    {
      Submesh & submesh = submeshes[i];

      auto & submeshHu = submeshesHu / i;
      if (submeshHu % "indexBits")
        { submesh.indexBits = submeshHu / "indexBits"; }

      if (submeshHu % "topology")
      {
        string topologyV = submeshHu / "topology";
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

      if (submeshHu % "indices")
      {
        auto & lodsHu = submeshHu / "indices";
        submesh.numIndices.resize(lodsHu.size());

        for (size_t j = 0; j < lodsHu.size(); ++j)
        {
          auto & indicesHu = lodsHu / i;
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
      auto & positions = src / "positions";
      auto & vecP = positions / i;
      for (size_t j = 0; j < positionSize; ++j)
      {
        * (float *) pBuf = vecP / j;
        pBuf += sizeof(float);
      }
    }

    if (hasNormals)
    {
      auto & normals = src / "normals";
      auto & vecN = normals / i;
      for (size_t j = 0; j < normalSize; ++j)
      {
        * (float *) pBuf = vecN / j;
        pBuf += sizeof(float);
      }
    }

    for (size_t j = 0; j < texSizes.size(); ++j)
    {
      auto & texes = src / "tex";
      auto & uv = texes / j / i;
      for (size_t k = 0; k < texSizes[j]; ++k)
      {
        * (float *) pBuf = uv / k;
        pBuf += sizeof(float);
      }
    }
  }

  if (src % "submeshes")
  {
    auto & submeshesHu = src / "submeshes";
    for (size_t i = 0; i < submeshes.size(); ++i)
    {
      Submesh & submesh = submeshes[i];
      auto & lodsHu = submeshesHu / i / "indices";
      for (size_t j = 0; j < submesh.numIndices.size(); ++j)
      {
        auto & indicesHu = lodsHu / j;
        for (size_t k = 0; k < submesh.numIndices[j]; ++k)
        {
          if (submesh.indexBits == 16)
          {
            * (uint16_t *) pBuf = static_cast<uint16_t>(long(indicesHu / k));
            pBuf += sizeof(uint16_t);
          }
          else
          {
            * (uint32_t *) pBuf = static_cast<uint32_t>(long(indicesHu / k));
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

