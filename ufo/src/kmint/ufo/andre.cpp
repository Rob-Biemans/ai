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
  path_to_knoop_ = a_star_.search(node(), find_node_of_kind(graph_, this->next_knoop));

  if (to_seconds(t_since_move_) >= 1) {
	  // find next correct edge
	  std::size_t id = path_to_knoop_.front()->node_id();
	  int found_index = 0;
	  for (std::size_t i = 0; i < node().num_edges(); ++i) {
		  if (node()[i].to().node_id() == id) {
			  found_index = i;
		  }
	  }
	  this->node(node()[found_index].to());
	  t_since_move_ = from_seconds(0);
  }

  // if andre has reached destination/knoop, switch next target knoop in line
  if (this->node().node_info().kind == this->next_knoop) {
	  if (this->next_knoop == '1') {
		  this->next_knoop = '2';
	  }
	  else if (this->next_knoop == '2') {
		  this->next_knoop = '3';
	  }
	  else if (this->next_knoop == '3') {
		  this->next_knoop = '4';
	  }
	  else if (this->next_knoop == '4') {
		  this->next_knoop = '1';
	  }
  }
}

} // namespace kmint::ufo
