#include <SFML/Graphics.hpp>
#include "gtest/gtest.h"
#include "Level.h"

using namespace IlluminatiConfirmed;

TEST(LevelTest, CheckDefaultConstructor) {
  Level level;
  level.loadMapFromFile("../Game/resources/maps/test_ver3000.tmx");

  sf::Vector2i expected = {32, 32};
  sf::Vector2i actual = level.GetTileSize();

  ASSERT_EQ(expected, actual);

  auto actual_info = level.GetMapInfo();

  decltype(actual_info) excepted_info = {{32, 32}, {5, 5}, 1, 25, 250};

  ASSERT_EQ(excepted_info, actual_info);

  auto actual_Layer =
      level.GetVecOfRectsByNameOfObjAndLayer("Buildings_obj", "Building_layer");
  // std::vector<std::pair<sf::Rect<int>, sf::Vector2i>>
  // std::map<int, std::pair<sf::Rect<int>, sf::Vector2i>>
  std::vector<std::pair<sf::Rect<int>, sf::Vector2i>> excepted_layer = {
      {{256, 3840, 32,32 }, {32, 64}}, {{ 288, 3840, 32, 32}, {64, 64}},
      {{ 320, 3840, 32, 32}, {96, 64}}, {{256, 3872, 32, 32}, {32, 96}},
      {{ 288, 3872, 32, 32}, {64, 96}}, {{ 320, 3872, 32, 32}, {96, 96}}};
  ASSERT_EQ(actual_Layer, excepted_layer);
}

//    Vector<int> v1;
//      ASSERT_EQ(v1.capacity(), 0);

//      // test 2
//      Vector<int> v2(0);
//      ASSERT_EQ(v2.capacity(), 0);

//      // test 3
//      Vector<int> v3(10);
//      ASSERT_EQ(v3.capacity(), 10);

//      // test 4
//      Vector<int> v4(-10);
//      ASSERT_EQ(v4.capacity(), 0);

//      // test 5
//      Vector<int> v5(1000000000000000);
//      ASSERT_EQ(v5.capacity(), 0);
