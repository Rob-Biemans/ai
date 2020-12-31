#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "kmint/math/vector2d.hpp"
#include <tuple>
#include <vector>

#include "steering_behaviors.h"
#include "chromosomes.hpp"

#include "shark.hpp"
#include "boat.hpp"

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  pig(math::vector2d location, Chromosomes chromosomes, pigisland::shark& shark, pigisland::boat& boat);
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
  math::vector2d side() const { return side_; }
  bool isTagged() const { return isTagged_; }
  math::vector2d velocity() const { return v_; }

  Chromosomes& getChromosomes() { return chromosomes_; }

private:
  play::image_drawable drawable_;
  math::vector2d v_{};
  math::vector2d heading_{};
  math::vector2d side_{};

  float mass_ = 1;
  float maxSpeed_ = 25;
  float maxForce_ = 100;
  float maxTurnRate_ = 100;
  bool isTagged_ = false;

  Chromosomes chromosomes_;
  shark& shark;
  boat& boat;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
