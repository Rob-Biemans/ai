#ifndef KMINT_UFO_TANK_HPP
#define KMINT_UFO_TANK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

#include "kmint/ufo/states/state_machine.h"

namespace kmint {
namespace ufo {

enum class tank_type { red, green };

class tank : public play::map_bound_actor {
public:
  tank(map::map_graph& g, map::map_node& initial_node, tank_type t);
  // wordt elke game tick aangeroepen
  void act(delta_time dt) override;
  ui::drawable const& drawable() const override { return drawable_; }
  // als incorporeal false is, doet de actor mee aan collision detection
  bool incorporeal() const override { return false; }
  // geeft de lengte van een zijde van de collision box van deze actor terug.
  // Belangrijk voor collision detection
  scalar collision_range() const override { return 16.0; }
  // geeft aan dat de tank andere actors kan zien
  bool perceptive() const override { return true; }
  // geeft het bereik aan waarbinnen een tank
  // andere actors kan waarnemen.
  scalar perception_range() const override { return 200.f; }

  states::StateMachine<tank>* GetFSM()const {
	  return m_pStateMachine_;
  }

private:
  play::image_drawable drawable_;
  delta_time t_since_move_{};
  tank_type type_;
  int amount_of_saved_humans = 0;
  int amount_of_damage = 0;
  int slowed_for_turns = 0;

  states::StateMachine<tank>* m_pStateMachine_;

};

} // namespace ufo
} // namespace kmint

#endif /* KMINT_UFO_TANK_HPP */
