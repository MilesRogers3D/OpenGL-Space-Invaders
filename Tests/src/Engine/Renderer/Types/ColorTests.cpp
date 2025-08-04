#include <Engine.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace Engine;

// ==== [Color] ==== //

TEST_CASE("Color struct", "[Color]")
{
  SECTION("Default constructor - white color")
  {
    const Color color(1.0F, 1.0F, 1.0F, 1.0F);

    REQUIRE(color.r == 1.0F);
    REQUIRE(color.g == 1.0F);
    REQUIRE(color.b == 1.0F);
    REQUIRE(color.a == 1.0F);
  }

  SECTION("Constructor with custom values")
  {
    const Color color(0.5F, 0.25F, 0.75F, 0.8F);

    REQUIRE(color.r == Catch::Approx(0.5F));
    REQUIRE(color.g == Catch::Approx(0.25F));
    REQUIRE(color.b == Catch::Approx(0.75F));
    REQUIRE(color.a == Catch::Approx(0.8F));
  }

  SECTION("Constructor with default alpha")
  {
    Color color(0.2F, 0.4F, 0.6F);

    REQUIRE(color.r == Catch::Approx(0.2F));
    REQUIRE(color.g == Catch::Approx(0.4F));
    REQUIRE(color.b == Catch::Approx(0.6F));
    REQUIRE(color.a == 1.0F);
  }
}

TEST_CASE("Color integer conversion methods", "[Color]")
{
  SECTION("Convert float values to integer values")
  {
    Color color(1.0F, 0.5F, 0.0F, 0.75F);

    REQUIRE(color.rInt() == 255);
    REQUIRE(color.gInt() == 127); // truncated to 127
    REQUIRE(color.bInt() == 0);
    REQUIRE(color.aInt() == 191); // truncated to 191
  }

  SECTION("Edge case values")
  {
    Color color(0.0F, 1.0F, 0.003921F, 0.996078F);

    REQUIRE(color.rInt() == 0);
    REQUIRE(color.gInt() == 255);
    REQUIRE(color.bInt() == 0);   // truncated to 0
    REQUIRE(color.aInt() == 253); // truncated to 253
  }
}

TEST_CASE("Color equality operator", "[Color]")
{
  SECTION("Equal colors")
  {
    Color color1(0.5F, 0.6F, 0.7F, 0.8F);
    Color color2(0.5F, 0.6F, 0.7F, 0.8F);
        
    REQUIRE(color1 == color2);
  }
    
  SECTION("Different colors")
  {
    Color color1(0.5F, 0.6F, 0.7F, 0.8F);
    Color color2(0.5F, 0.6F, 0.7F, 0.9F); // Different alpha
        
    REQUIRE_FALSE(color1 == color2);
  }
    
  SECTION("Slightly diFFerent Floating point values")
  {
    Color color1(0.5F, 0.6F, 0.7F, 0.8F);
    Color color2(0.50001F, 0.6F, 0.7F, 0.8F); // Slightly different red
        
    REQUIRE_FALSE(color1 == color2);
  }
}

// ==== [ColorUtils] ==== //

TEST_CASE("Color from RGBA floating-point values", "[ColorUtils]")
{
  SECTION("Create color from float values")
  {
    const Color color = ColorUtils::fromRGBAFloat(0.2F, 0.4F, 0.6F, 0.8F);

    REQUIRE(color.r == Catch::Approx(0.2F));
    REQUIRE(color.g == Catch::Approx(0.4F));
    REQUIRE(color.b == Catch::Approx(0.6F));
    REQUIRE(color.a == Catch::Approx(0.8F));
  }

  SECTION("Create color with default alpha")
  {
    const Color color = ColorUtils::fromRGBAFloat(0.1F, 0.3F, 0.5F);

    REQUIRE(color.r == Catch::Approx(0.1F));
    REQUIRE(color.g == Catch::Approx(0.3F));
    REQUIRE(color.b == Catch::Approx(0.5F));
    REQUIRE(color.a == 1.0F);
  }
}

TEST_CASE("Color from RGBA integer values", "[ColorUtils]")
{
  SECTION("Create color from integer values")
  {
    const Color color = ColorUtils::fromRGBAInt32(255, 128, 64, 200);

    REQUIRE(color.r == Catch::Approx(1.0F));
    REQUIRE(color.g == Catch::Approx(128.0F / 255.0F).margin(0.001F));
    REQUIRE(color.b == Catch::Approx(64.0F  / 255.0F).margin(0.001F));
    REQUIRE(color.a == Catch::Approx(200.0F / 255.0F).margin(0.001F));
  }

  SECTION("Create color with default alpha")
  {
    const Color color = ColorUtils::fromRGBAInt32(100, 150, 200);

    REQUIRE(color.r == Catch::Approx(100.0F / 255.0F).margin(0.001F));
    REQUIRE(color.g == Catch::Approx(150.0F / 255.0F).margin(0.001F));
    REQUIRE(color.b == Catch::Approx(200.0F / 255.0F).margin(0.001F));
    REQUIRE(color.a == 1.0F);
  }

  SECTION("Edge cases with 0 and 255")
  {
    const Color color = ColorUtils::fromRGBAInt32(0, 255, 0, 255);

    REQUIRE(color.r == Catch::Approx(0.0F));
    REQUIRE(color.g == Catch::Approx(1.0F));
    REQUIRE(color.b == Catch::Approx(0.0F));
    REQUIRE(color.a == Catch::Approx(1.0F));
  }
}

TEST_CASE("Color from hex code", "[ColorUtils]")
{
  SECTION("Parse standard RGBA hex code")
  {
    // 0xFF8040C0 = R:255, G:128, B:64, A:192
    const Color color = ColorUtils::fromHexCode(0xFF8040);

    REQUIRE(color.r == Catch::Approx(1.0F));
    REQUIRE(color.g == Catch::Approx(128.0F / 255.0F).margin(0.001F));
    REQUIRE(color.b == Catch::Approx(64.0F  / 255.0F).margin(0.001F));
  }

  SECTION("Parse black color with no alpha")
  {
    Color color = ColorUtils::fromHexCode(0x000000);
    color.a = 0.0F;

    REQUIRE(color.r == Catch::Approx(0.0F));
    REQUIRE(color.g == Catch::Approx(0.0F));
    REQUIRE(color.b == Catch::Approx(0.0F));
    REQUIRE(color.a == Catch::Approx(0.0F));
  }

  SECTION("Parse white color with full alpha")
  {
    const Color color = ColorUtils::fromHexCode(0xFFFFFFFF);

    REQUIRE(color.r == Catch::Approx(1.0F));
    REQUIRE(color.g == Catch::Approx(1.0F));
    REQUIRE(color.b == Catch::Approx(1.0F));
    REQUIRE(color.a == Catch::Approx(1.0F));
  }
}

TEST_CASE("Color from preset", "[ColorUtils]")
{
  SECTION("Create color from preset values")
  {
    // Black color
    const Color black = ColorUtils::fromPreset(EColor::Black);

    REQUIRE(black.r == Catch::Approx(0.0F));
    REQUIRE(black.g == Catch::Approx(0.0F));
    REQUIRE(black.b == Catch::Approx(0.0F));
    REQUIRE(black.a == Catch::Approx(1.0F));

    // White color
    const Color white = ColorUtils::fromPreset(EColor::White);

    REQUIRE(white.r == Catch::Approx(1.0F));
    REQUIRE(white.g == Catch::Approx(1.0F));
    REQUIRE(white.b == Catch::Approx(1.0F));
    REQUIRE(white.a == Catch::Approx(1.0F));
  }
}

TEST_CASE("Color integration tests", "[Integration]")
{
  SECTION("int -> float -> int")
  {
    constexpr uint32_t R = 200;
    constexpr uint32_t G = 150;
    constexpr uint32_t B = 100;
    constexpr uint32_t A = 75;

    const Color color = ColorUtils::fromRGBAInt32(R, G, B, A);

    REQUIRE(color.rInt() == R);
    REQUIRE(color.gInt() == G);
    REQUIRE(color.bInt() == B);
    REQUIRE(color.aInt() == A);
  }
}