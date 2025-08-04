#pragma once

#include "IO/Model/IModelParser.h"

namespace Engine::IO {

class ENG_API OBJParser final : public IModelParser
{
public:
private:
  struct FaceVertDesc
  {
    std::size_t vIndex = 0;
    std::size_t tcIndex = -1;
    std::size_t nIndex = -1;
  };

  struct FaceDesc
  {
    std::vector<FaceVertDesc> vertices;
  };

  struct EdgeDesc
  {
    uint32_t v0 = 0;
    uint32_t v1 = 1;
  };

  struct OBJModel
  {
    std::vector<Vector3> points;
    std::vector<Vector2> texCoords;
    std::vector<Vector3> normals;
    std::vector<FaceDesc> faces;
    std::vector<EdgeDesc> edges;
  };

public:
  OBJParser() : m_objModel(std::make_shared<OBJModel>()) {}
  ~OBJParser() override = default;

public:
  bool loadModel(const std::string& path) override;

private:
  void p_parseLine(const std::string& line);

  void p_parseVertex(std::istringstream& iss) const;
  void p_parseTexCoord(std::istringstream& iss) const;
  void p_parseNormal(std::istringstream& iss) const;
  static FaceVertDesc p_parseFaceVertex(
    const std::string& vertexStr);
  void p_parseFace(std::istringstream& iss) const;
  void p_parseEdge(std::istringstream& iss) const;

  void p_generateOutputData();

private:
  std::shared_ptr<OBJModel> m_objModel;
};

} // Engine::IO