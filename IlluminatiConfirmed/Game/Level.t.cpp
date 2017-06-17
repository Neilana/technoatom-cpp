#include <SFML/Graphics.hpp>
#include "../Exceptions/Exception.h"
#include "Level.h"
#include "gtest/gtest.h"

using namespace IlluminatiConfirmed;

TEST(LevelTest, CheckDefaultConstructor) {
  try {
    Level level;
    level.loadMapFromFile("../Game/resources/maps/test_ver3000.tmx");

    sf::Vector2i expected = {32, 32};
    sf::Vector2i actual = level.GetTileSize();

    ASSERT_EQ(expected, actual);

    auto actual_info = level.GetMapInfo();

    decltype(actual_info) excepted_info = {{32, 32}, {5, 5}, 1, 25, 250};

    ASSERT_EQ(excepted_info, actual_info);

    auto actual_Layer = level.GetVecOfRectsByNameOfObjsGroupAndLayer(
        "Buildings_sprite", "Building_layer");
    // std::vector<std::pair<sf::Rect<int>, sf::Vector2i>>
    // std::map<int, std::pair<sf::Rect<int>, sf::Vector2i>>
    std::vector<std::vector<std::pair<sf::Rect<int>, sf::Vector2i>>>
        excepted_layer = {{
                           {{256, 3808, 32, 32}, {32, 32}},
                           {{288, 3808, 32, 32}, {64, 32}},
                           {{320, 3808, 32, 32}, {96, 32}},
                           {{256, 3840, 32, 32}, {32, 64}},
                           {{288, 3840, 32, 32}, {64, 64}},
                           {{320, 3840, 32, 32}, {96, 64}},
                           {{256, 3872, 32, 32}, {32, 96}},
                           {{288, 3872, 32, 32}, {64, 96}},
                           {{320, 3872, 32, 32}, {96, 96}}}};
    ASSERT_EQ(actual_Layer, excepted_layer);
  } catch (Exception &e) {
    std::cout << e.what();
  }
}
