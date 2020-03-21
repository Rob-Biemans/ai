#ifndef KMINT_UFO_HUMAN_HPP
#define KMINT_UFO_HUMAN_HPP
#include "kmint/math/vector2d.hpp"
#include "kmint/play.hpp"
#include <tuple>
#include <vector>

namespace kmint::ufo {

class human : public kmint::play::free_roaming_actor {
public:
  human();
  const ui::drawable& drawable() const override { return drawable_; }
  // participates in collisions
  bool incorporeal() const override { return false; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;

private:
  play::image_drawable drawable_;
  math::vector2d v_{};
};

} // namespace kmint::ufo

#endif /* KMINT_UFO_HUMAN_HPP */
