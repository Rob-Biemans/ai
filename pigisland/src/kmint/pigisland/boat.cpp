#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

#include "../../../include/kmint/pigisland/states/boat_wander_state.h"
#include "../../../include/kmint/pigisland/states/boat_global_state.h"

namespace kmint {
namespace pigisland {
  boat::boat(map::map_graph& g, map::map_node& initial_node)
    : play::map_bound_actor{ initial_node },
      drawable_{ *this, graphics::image{boat_image()} } {
	  m_pStateMachine_ = std::unique_ptr<states::StateMachine>(new states::StateMachine(*this));

	  m_pStateMachine_->SetCurrentState(new states::BoatWanderState(*this));
	  m_pStateMachine_->SetGlobalState(new states::BoatGlobalState(g, *this));
  }


  void boat::act(delta_time dt) {
	
    t_passed_ += dt;
    if (to_seconds(t_passed_) >= 1) 
	{
	  m_pStateMachine_->Update();
      t_passed_ = from_seconds(0);
    }
  }

  void boat::repairDamage(int dock, int value) {
	  damaged_ -= value;

	  std::cout << "Repaired for " << value << " at dock number " << dock;
  }

  void boat::goToNextRandomNode() {
	  int next_index = random_int(0, node().num_edges());
	  moveToNextNode(next_index);
  }

  void boat::moveToNextNode(int next_index) {
	  if (getTurnsToWait() <= 0) {
		  node(node()[next_index].to());

		  if (node().node_info().kind == 'R') {
			  std::cout << "boat::set4TurnsToWait() \n";
			  set4TurnsToWait();
		  }
	  }
	  else {
		  removeTurnsToWaitByOne();
	  }
  }

  void boat::set4TurnsToWait() {
	  turns_to_wait_ = 4;
  }

  void boat::removeTurnsToWaitByOne() {
	  turns_to_wait_--;
  }
} // namespace pigisland
} // namespace kmint
