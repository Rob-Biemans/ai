#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>

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
	m_pStateMachine_->SetGlobalState(new states::SharkGlobalState(*this));
}

void shark::act(delta_time dt) {
  m_pStateMachine_->Update();

  t_passed_ += dt;
  if (to_seconds(t_passed_) >= 1) {
    // pick random edge
    int next_index = random_int(0, node().num_edges());
    this->node(node()[next_index].to());
    t_passed_ = from_seconds(0);
  }
  // laat ook even zien welke varkentjes hij ruikt
  //for (auto i = begin_perceived(); i != end_perceived(); ++i) {
  //  auto const &a = *i;
  //  std::cout << "Smelled a pig at " << a.location().x() << ", "
  //            << a.location().y() << "\n";
  //}
}

} // namespace pigisland
} // namespace kmint
