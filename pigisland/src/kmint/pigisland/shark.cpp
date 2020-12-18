#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>

#include "../../../include/kmint/pigisland/states/shark_tired_state.h"
#include "../../../include/kmint/pigisland/states/shark_wander_state.h"
#include "../../../include/kmint/pigisland/states/shark_global_state.h"

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph &g, map::map_node &initial_node)
    : play::map_bound_actor{initial_node}, drawable_{*this,
                                                     graphics::image{
                                                         shark_image()}}
{
	m_pStateMachine_ = std::unique_ptr<states::StateMachine>(new states::StateMachine(*this));

	m_pStateMachine_->SetCurrentState(new states::SharkWanderState(*this));
	m_pStateMachine_->SetGlobalState(new states::SharkGlobalState(g, *this));
}

void shark::act(delta_time dt) {
  t_passed_ += dt;

  if (to_seconds(t_passed_) >= 1) {

	std::cout << this->node().node_info().kind << " ";
	m_pStateMachine_->Update();
	
    t_passed_ = from_seconds(0);
  }
}

void shark::resetTired() {
	tired_ = 0;
}

} // namespace pigisland
} // namespace kmint
