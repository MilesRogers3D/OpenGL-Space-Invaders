#pragma once

#include "defs.h"
#include "ColorPresets.h"
#include "Core/Math/MathTypes.h"

#include <cstdint>
#include <string>

namespace Engine {

struct Color
{
  float r = 1.0F;
  float g = 1.0F;
  float b = 1.0F;
  float a = 1.0F;

  explicit Color(const float r,
                 const float g,
                 const float b,
                 const float a = 1.0F)
    : r(r), g(g), b(b), a(a)
  {
  }

  uint32_t rInt() const { return static_cast<uint32_t>(r * 255.0F); }
  uint32_t gInt() const { return static_cast<uint32_t>(g * 255.0F); }
  uint32_t bInt() const { return static_cast<uint32_t>(b * 255.0F); }
  uint32_t aInt() const { return static_cast<uint32_t>(a * 255.0F); }

  bool operator==(const Color& other) const
  {
    return r == other.r &&
           g == other.g &&
           b == other.b &&
           a == other.a;
  }
};

class ENG_API ColorUtils
{
public:
  static Color fromRGBAFloat(float r, float g, float b, float a = 1.0F);
  static Color fromRGBAInt32(uint32_t r, uint32_t g, uint32_t b, uint32_t a = 255);
  static Color fromHexCode(uint32_t hexCode);
  static Color fromPreset(const EColor& colorPreset);
};

}