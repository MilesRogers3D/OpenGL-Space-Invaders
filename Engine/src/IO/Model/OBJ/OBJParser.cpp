#include "OBJParser.h"
#include "Core/Logger/Logger.h"

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <string>

using namespace Engine::IO;

bool OBJParser::loadModel(const std::string& path)
{
  std::ifstream file(path);
  if (!file.is_open()) {
    Logger::logError("Could not open file: '{}'", path);
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    p_parseLine(line);
  }

  p_generateOutputData();
  m_loaded = true;

  return true;
}

void OBJParser::p_parseLine(const std::string& line)
{
  // Skip empty lines and comments
  if (line.empty() || line[0] == '#') {
    return;
  }

  std::istringstream iss(line);
  std::string type;
  iss >> type;

  if (type == "v") {
    p_parseVertex(iss);
  }
  else if (type == "vt") {
    p_parseTexCoord(iss);
  }
  else if (type == "vn") {
    p_parseNormal(iss);
  }
  else if (type == "f") {
    p_parseFace(iss);
  }
  else if (type == "l") {
    p_parseEdge(iss);
  }
}

void OBJParser::p_parseVertex(std::istringstream& iss) const
{
  Vector3 v;
  iss >> v.x >> v.y >> v.z;
  m_objModel->points.emplace_back(v);
}

void OBJParser::p_parseTexCoord(std::istringstream& iss) const
{
  Vector2 uv;
  iss >> uv.x >> uv.y;
  m_objModel->texCoords.emplace_back(uv);
}

void OBJParser::p_parseNormal(std::istringstream& iss) const
{
  Vector3 n;
  iss >> n.x >> n.y >> n.z;
  m_objModel->normals.emplace_back(n);
}

OBJParser::FaceVertDesc OBJParser::p_parseFaceVertex(const std::string& vertexStr)
{
  FaceVertDesc fv;

  std::istringstream iss(vertexStr);
  std::string indexStr;

  // Parse vertex index
  if (std::getline(iss, indexStr, '/')) {
    fv.vIndex = std::stoi(indexStr) - 1;
  }

  // Parse texture coordinate index
  if (std::getline(iss, indexStr, '/')) {
    if (!indexStr.empty()) {
      fv.tcIndex = std::stoi(indexStr) - 1;
    }
  }

  // Parse normal index
  if (std::getline(iss, indexStr, '/')) {
    if (!indexStr.empty()) {
      fv.nIndex = std::stoi(indexStr) - 1;
    }
  }

  return fv;
}

void OBJParser::p_parseFace(std::istringstream& iss) const
{
  FaceDesc face;
  std::string vertexStr;

  while (iss >> vertexStr) {
    FaceVertDesc fv = p_parseFaceVertex(vertexStr);
    face.vertices.emplace_back(fv);
  }

  m_objModel->faces.emplace_back(face);
}

void OBJParser::p_parseEdge(std::istringstream& iss) const
{
  EdgeDesc e = {};
  std::string edgeStr;

  iss >> e.v0;
  iss >> e.v1;

  m_objModel->edges.emplace_back(e);
}

void OBJParser::p_generateOutputData()
{
  m_model = std::make_shared<Model>();

  // Faces
  // std::map<std::tuple<int, int, int>, uint32_t> vertexMap;
  //
  // for (const auto& f : m_objModel->faces) {
  //   for (const auto& fv : f.vertices) {
  //     auto key = std::make_tuple(
  //       fv.vIndex, fv.tcIndex, fv.nIndex);
  //
  //     auto it = vertexMap.find(key);
  //     uint32_t index;
  //
  //     if (it != vertexMap.end()) {
  //       index = it->second;
  //     } else {
  //       const Vector3 pos = m_objModel->points[fv.vIndex];
  //       const Vector2 texCoord = m_objModel->texCoords[fv.tcIndex];
  //       const Vector3 norm = m_objModel->normals[fv.nIndex];
  //
  //       index = m_model->points.size();
  //       vertexMap[key] = index;
  //
  //       m_model->points.emplace_back(pos);
  //       m_model->texCoords.emplace_back(texCoord);
  //       m_model->normals.emplace_back(norm);
  //     }
  //
  //     m_model->indices.push_back(index);
  //   }
  // }

  // Edges
  std::map<uint32_t, uint32_t> vertexEdgeMap;

  for (const auto& [v0, v1] : m_objModel->edges) {
    const Vector3 pos0 = m_objModel->points[v0];
    const Vector3 pos1 = m_objModel->points[v1];

    auto v0Itr = vertexEdgeMap.find(v0);
    auto v1Itr = vertexEdgeMap.find(v1);

    uint32_t i0, i1;

    if (v0Itr != vertexEdgeMap.end()) {
      i0 = v0Itr->second;
    }
    else {
      m_model->points.emplace_back(pos0);
      m_model->normals.emplace_back(0.0F, 0.0F, 0.0F);
      m_model->texCoords.emplace_back(0.0F, 0.0F);

      i0 = m_model->points.size() - 1;
      vertexEdgeMap[v0] = i0;
    }

    if (v1Itr != vertexEdgeMap.end()) {
      i1 = v1Itr->second;
    }
    else {
      m_model->points.emplace_back(pos1);
      m_model->normals.emplace_back(0.0F, 0.0F, 0.0F);
      m_model->texCoords.emplace_back(0.0F, 0.0F);

      i1 = m_model->points.size() - 1;
      vertexEdgeMap[v1] = i1;
    }

    m_model->indices.emplace_back(i0);
    m_model->indices.emplace_back(i1);
  }
}