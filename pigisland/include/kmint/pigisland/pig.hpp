#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "kmint/math/vector2d.hpp"
#include <tuple>
#include <vector>

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  pig(math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }
  // participates in collisions
  bool incorporeal() const override { return false; }

  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;

private:
  play::image_drawable drawable_;
  math::vector2d v_{};
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
