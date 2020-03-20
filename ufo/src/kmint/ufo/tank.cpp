#include "kmint/ufo/tank.hpp"
#include "kmint/graphics.hpp"
#include "kmint/ufo/node_algorithm.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/human.hpp"
#include <iostream>

namespace kmint::ufo {

namespace {
graphics::image tank_image(tank_type t) {
  constexpr scalar scale = 0.35;
  switch (t) {
  case tank_type::red:
    return graphics::image{"resources/tank_red.png", scale};
  case tank_type::green:
    return graphics::image{"resources/tank_green.png", scale};
  }
  return graphics::image{"resources/tank_green.png", scale};
}


} // namespace

tank::tank(map::map_graph& g, map::map_node& initial_node, tank_type t)
	: play::map_bound_actor{ initial_node }, type_{t},
	drawable_{ *this, graphics::image{tank_image(t)} } {}

void tank::act(delta_time dt) {
	t_since_move_ += dt;
	if (to_seconds(t_since_move_) >= 1) {
		// pick random edge
		int next_index = random_int(0, node().num_edges());
		this->node(node()[next_index].to());
		t_since_move_ = from_seconds(0);
	}
	// laat ook zien wat hij ziet
	for (auto i = begin_perceived(); i != end_perceived(); ++i) {
		auto const& a = *i;
		//std::cout << &a == saucer_;
		//std::cout << "Saw something at " << a.location().x() << ", "
		//	<< a.location().y() << "\n";
	}

	// *Red Tank overran human
	for (std::size_t ix{}; ix < num_colliding_actors(); ++ix) {
		auto &other = colliding_actor(ix);
		if (dynamic_cast<human *>(&other) && this->type_ != tank_type::green) {
			std::cout << "Red tank overran human\n";
			other.remove();
		}

		if (dynamic_cast<human *>(&other) && this->type_ != tank_type::red) {
			this->amount_of_saved_humans += 1;
			std::cout << "Green tank put human inside, and saved intotal "<< this->amount_of_saved_humans << "\n";
			other.remove();
		}
	}
}

} // namespace kmint::ufo
