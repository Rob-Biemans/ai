#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

#include "kmint/pigisland/pig.hpp"

#include "../../../include/kmint/pigisland/states/boat_wander_state.h"
#include "../../../include/kmint/pigisland/states/boat_global_state.h"

namespace kmint {
namespace pigisland {
  boat::boat(map::map_graph& g, map::map_node& initial_node)
    : play::map_bound_actor{ initial_node },
      drawable_{ *this, graphics::image{boat_image()} } {
	  m_pStateMachine_ = std::unique_ptr<states::StateMachine>(new states::StateMachine(*this));

	  m_pStateMachine_->SetCurrentState(new states::BoatWanderState(*this));
	  m_pStateMachine_->SetGlobalState(new states::BoatGlobalState(*this));
  }


  void boat::act(delta_time dt) {
	m_pStateMachine_->Update();

    t_passed_ += dt;
    if (to_seconds(t_passed_) >= 1) {
      // pick random edge
      int next_index = random_int(0, node().num_edges());
      this->node(node()[next_index].to());
      t_passed_ = from_seconds(0);
    }

	// Boat helped Pig to board for safety
	for (std::size_t ix{}; ix < num_colliding_actors(); ++ix) {
		auto &other = colliding_actor(ix);
		if (dynamic_cast<pig *>(&other)) {
			std::cout << "A pig safely climbed onto the boat \n";
			other.remove();
		}
	}
  }

} // namespace pigisland
} // namespace kmint
