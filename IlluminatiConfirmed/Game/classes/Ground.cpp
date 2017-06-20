#include "Ground.h"

using namespace IlluminatiConfirmed;

Ground::Ground(const sf::Texture *texture, const Layer &layer) {
  m_sprites.reserve(layer.m_sub_rects.size() + 1);

  for (auto &&rect_info : layer.m_sub_rects) {
    auto pos = rect_info.second.second;
    sf::Sprite sprite(*texture);
    sprite.setTextureRect(rect_info.second.first);
    sprite.setPosition(pos.x, pos.y);

    m_sprites.push_back(std::move(sprite));
  }
}

void Ground::draw_ground(sf::RenderWindow &window) {
  for (auto &&it : m_sprites) {
    window.draw(it);
  }
}
