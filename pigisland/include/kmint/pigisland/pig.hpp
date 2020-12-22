#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "kmint/math/vector2d.hpp"
#include <tuple>
#include <vector>

#include "kmint/pigisland/steering_behaviors.hpp"

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
  scalar perception_range() const override { return 30.0f; }

  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;

  float mass() const { return mass_; }
  float maxSpeed() const { return maxSpeed_; }
  float maxForce() const { return maxForce_; }
  float maxTurnRate() const { return maxTurnRate_; }
  math::vector2d heading() const { return heading_; }
  bool isTagged() const { return isTagged_; }
  math::vector2d velocity() const { v_; }
private:
  play::image_drawable drawable_;
  //SteeringBehaviors steeringBehaviors_;
  math::vector2d v_{};
  math::vector2d heading_{};
  math::vector2d side_{};

  float mass_;
  float maxSpeed_;
  float maxForce_;
  float maxTurnRate_;
  bool isTagged_;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
