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
	  drawable_{ *this, graphics::image{boat_image()} }, graph_{ g } {
	  m_pStateMachine_ = std::unique_ptr<states::StateMachine>(new states::StateMachine(*this));

	  m_pStateMachine_->SetCurrentState(new states::BoatWanderState(*this));
	  m_pStateMachine_->SetGlobalState(new states::BoatGlobalState(g, *this));

	  findAndStoreMaintenancePlaces();
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

  void boat::setColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
  {
	  graphics::color color{ r, g, b };
	  drawable_.set_tint(color);
  }

  void boat::removeColor() {
	  drawable_.remove_tint();
  }

  void boat::findAndStoreMaintenancePlaces() {
	  //char maintenance_place_char_grain_island_ = '1'; // min 30, max 50
	  //char maintenance_place_char_gras_island_ = '2';  // min 20, max 100
	  //char maintenance_place_char_tree_island_ = '3';  // min 50, max 50

	  map::map_node* node = &graph_[0];
	  std::for_each(graph_.begin(), graph_.end(), [&](map::map_node &n)
	  {
		  if (n.node_info().kind == '1')
		  {
			  maintenances_places_.push_back({1, 30, 50, &n });
		  }

		  if (n.node_info().kind == '2')
		  {
			  maintenances_places_.push_back({ 2, 20, 100, &n });
		  }

		  if (n.node_info().kind == '3')
		  {
			  maintenances_places_.push_back({ 3, 50, 50, &n });
		  }
	  });
  }
} // namespace pigisland
} // namespace kmint
