#pragma once

#include "defs.h"
#include "Types/ModelTypes.h"

namespace Engine::IO {

class ENG_API IModelParser
{
public:
  IModelParser()
    : m_model(std::make_shared<Model>()) {}

  virtual ~IModelParser()
  {
    // Clear model data / reset pointer
    m_model->points.clear();
    m_model->indices.clear();
    m_model.reset();
  }

public:
  virtual bool loadModel(const std::string& path) = 0;

  std::shared_ptr<Model> getModel()
  {
    if (!m_loaded) {
      return nullptr;
    }

    return m_model;
  }

protected:
  std::shared_ptr<Model> m_model;
  bool m_loaded = false;
};

}