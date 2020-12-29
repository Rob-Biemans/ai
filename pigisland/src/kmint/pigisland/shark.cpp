#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>

#include "kmint/pigisland/pig.hpp"

#include "../../../include/kmint/pigisland/states/shark_tired_state.h"
#include "../../../include/kmint/pigisland/states/shark_wander_state.h"
#include "../../../include/kmint/pigisland/states/shark_hunt_state.h"
#include "../../../include/kmint/pigisland/states/shark_global_state.h"

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph &g, map::map_node &initial_node)
    : play::map_bound_actor{initial_node}, drawable_{*this,
                                                     graphics::image{
                                                         shark_image()}}
{
	m_pStateMachine_ = std::unique_ptr<states::StateMachine>(new states::StateMachine(*this));

	m_pStateMachine_->SetCurrentState(new states::SharkWanderState(g, *this));
	m_pStateMachine_->SetGlobalState(new states::SharkGlobalState(g, *this));
}

void shark::act(delta_time dt) {
	t_passed_ += dt;

	if (to_seconds(t_passed_) >= 1) 
	{
		//std::cout << this->node().node_info().kind << " ";
		m_pStateMachine_->Update();
		t_passed_ = from_seconds(0);
	}

	for (std::size_t ix{}; ix < num_colliding_actors(); ++ix) {
		auto &other = colliding_actor(ix);

		if (dynamic_cast<pig *>(&other)) 
		{
			if (m_pStateMachine_->isInState("SharkWanderState") || m_pStateMachine_->isInState("SharkHuntState")) 
			{
				std::cout << "A pig has been eaten \n";
				other.remove();
			}
		}
	}
}

void shark::goToNextRandomNode() {
	int next_index = random_int(0, node().num_edges());
	moveToNextNode(next_index);
}

void shark::moveToNextNode(int next_index) {
	if (getTurnsToWait() <= 0) 
	{
		node(node()[next_index].to());

		if (node().node_info().kind == 'R') 
		{
			std::cout << "shark::set4TurnsToWait() \n";
			set4TurnsToWait();
		}
	}
	else {
		removeTurnsToWaitByOne();
	}
}

void shark::resetTired() {
	tired_ = 0;

	//TODO RESET PIG POPULATION
}

void shark::set4TurnsToWait() {
	turns_to_wait_ = 4;
}

void shark::removeTurnsToWaitByOne() {
	turns_to_wait_--;
}

void shark::setColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	graphics::color color{ r, g, b };
	drawable_.set_tint(color);
}

} // namespace pigisland
} // namespace kmint
