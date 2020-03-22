#include "kmint/ufo/andre.hpp"
#include "kmint/graphics.hpp"
#include "kmint/ufo/node_algorithm.hpp"
#include "kmint/random.hpp"
#include <iostream>

namespace kmint::ufo {

namespace {

graphics::image andre_image() {
  constexpr scalar scale = 1.0;
  return graphics::image{"resources/andre.png"};
}

} // namespace
andre::andre(map::map_graph& g, map::map_node& initial_node)
	: play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{ andre_image()} }, graph_{ g }, a_star_{g} {}

void andre::act(delta_time dt) {
  t_since_move_ += dt;

  a_star_.untag_nodes();
  path_to_knoop_ = a_star_.search(node(), find_node_of_kind(graph_, '1'));
  
  if (to_seconds(t_since_move_) >= 1) {
	  // pick random edge
	  int next_index = random_int(0, path_to_knoop_.front()->num_edges());
	  this->node(node()[next_index].to());
	  t_since_move_ = from_seconds(0);
  }
}

} // namespace kmint::ufo
