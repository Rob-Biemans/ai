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
  bool perceivable() const override { return true; }
  bool perceptive() const override { return true; }

  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;

private:
  play::image_drawable drawable_;
  math::vector2d v_{};

  char maintenance_place_char_grain_island_ = '1'; // min 30, max 50
  char maintenance_place_char_gras_island_ = '2';  // min 20, max 100
  char maintenance_place_char_tree_island_ = '3';  // min 50, max 50
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
