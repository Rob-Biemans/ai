#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

#include "kmint/pigisland/states/state_machine.h"

namespace kmint {
namespace pigisland {

class boat : public play::map_bound_actor {
public:
	boat(map::map_graph& g, map::map_node& initial_node);
	// wordt elke game tick aangeroepen
	void act(delta_time dt) override;
	ui::drawable const& drawable() const override { return drawable_; }
	// als incorporeal false is, doet de actor mee aan collision detection
	bool incorporeal() const override { return false; }
	// geeft de lengte van een zijde van de collision box van deze actor terug.
	// Belangrijk voor collision detection
	scalar collision_range() const override { return 16.0; }

	states::StateMachine& getFSM() const {
		return *m_pStateMachine_;
	}

	int getTotalDamaged() const { return damaged_; }
	void addDamage() { damaged_++; }
	void repairDamage(int dock, int value);
	void goToNextRandomNode();
	void moveToNextNode(int next_index);

	void set4TurnsToWait();
	int getTurnsToWait() const { return turns_to_wait_; }
	void removeTurnsToWaitByOne();
private:
	// hoeveel tijd is verstreken sinds de laatste beweging
	delta_time t_passed_{};
	// weet hoe de koe getekend moet worden
	play::image_drawable drawable_;

	std::unique_ptr<states::StateMachine> m_pStateMachine_;
	int damaged_ = 0;
	int turns_to_wait_ = 0;

	char maintenance_place_char_grain_island_ = '1'; // min 30, max 50
	char maintenance_place_char_gras_island_ = '2';  // min 20, max 100
	char maintenance_place_char_tree_island_ = '3';  // min 50, max 50
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
