#include <SFML/Graphics.hpp>
#include "../Exceptions/Exception.h"
#include "Level.h"
#include "gtest/gtest.h"

using namespace IlluminatiConfirmed;

TEST(LevelTest, CheckInfoMap) {
  try {
    Level level;
    level.loadMapFromFile("../Game/resources/maps/test_ver3000.tmx");

    sf::Vector2i expected = {32, 32};
    sf::Vector2i actual = level.GetTileSize();

    ASSERT_EQ(expected, actual);
  } catch (Exception &e) {
    std::cout << e.what();
  }
}

TEST(LevelTest, CheckLoadMapBigObjs) {
  try {
    Level level_layer;
    level_layer.loadMapFromFile("../Game/resources/maps/test_ver3002.tmx");
    auto actual_Layer = level_layer.GetVecOfBigObjs(
        "Buildings_sprite", "Buildings_obj", "Building_layer");

    std::vector<IlluminatiConfirmed::Big_Object> excepted_layer = {
        {{"3", "sprite", {106, 110, 46, 32}},
         {"3", "body", {106, 130, 46, 13}},
         {{{448, 320, 32, 32}, {96, 96}},
          {{480, 320, 32, 32}, {128, 96}},
          {{448, 352, 32, 32}, {96, 128}},
          {{480, 352, 32, 32}, {128, 128}}}},

        {{"2", "sprite", {41, 109, 46, 32}},
         {"2", "body", {41, 129, 46, 13}},
         {{{448, 320, 32, 32}, {32, 96}},
          {{480, 320, 32, 32}, {64, 96}},
          {{448, 352, 32, 32}, {32, 128}},
          {{480, 352, 32, 32}, {64, 128}}}},

        {{"1", "sprite", {105, 14, 46, 32}},
         {"1", "body", {105, 34, 46, 13}},
         {{{448, 320, 32, 32}, {96, 0}},
          {{480, 320, 32, 32}, {128, 0}},
          {{448, 352, 32, 32}, {96, 32}},
          {{480, 352, 32, 32}, {128, 32}}}}};

    ASSERT_EQ(actual_Layer, excepted_layer);
  } catch (Exception &e) {
    std::cout << e.what();
  }
}
