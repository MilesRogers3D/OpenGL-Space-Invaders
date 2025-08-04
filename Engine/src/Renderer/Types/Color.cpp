#include "Color.h"

using namespace Engine;

Color ColorUtils::fromRGBAFloat(const float r,
                                const float g,
                                const float b,
                                const float a)
{
  return Color(r, g, b, a);
}

Color ColorUtils::fromRGBAInt32(const uint32_t r,
                                const uint32_t g,
                                const uint32_t b,
                                const uint32_t a)
{
  return Color(
    static_cast<float>(r) / 255.0F,
    static_cast<float>(g) / 255.0F,
    static_cast<float>(b) / 255.0F,
    static_cast<float>(a) / 255.0F);
}

Color ColorUtils::fromHexCode(const uint32_t hexCode)
{
  return Color(
    static_cast<float>(hexCode >> 16 & 0xFF) / 255.0F,
    static_cast<float>(hexCode >> 8  & 0xFF) / 255.0F,
    static_cast<float>(hexCode       & 0xFF) / 255.0F,
    1.0F);
}

Color ColorUtils::fromPreset(const EColor& colorPreset)
{
  return fromHexCode(static_cast<uint32_t>(colorPreset));
}