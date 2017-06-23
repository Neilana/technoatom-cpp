#include "constants.h"

std::ostream &operator<<(std::ostream &stream, const b2Vec2 &vec) {
  stream << vec.x << " : " << vec.y;
  return stream;
}
