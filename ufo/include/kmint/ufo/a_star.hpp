#ifndef KMINT_UFO_A_STAR_HPP
#define KMINT_UFO_A_STAR_HPP

#include "kmint/map/map.hpp"
#include <queue>
#include <map>

namespace kmint::ufo {

	class a_star {
		map::map_graph& graph_;
		std::queue<const map::map_node*> untag_queue_;

		std::queue<const map::map_node*> reconstruct_path(const map::map_node* source, const map::map_node* target, std::map<const map::map_node*, const map::map_node*> from_source);

		double heuristic(const map::map_node& source, const map::map_node& target) const;
	public:
		a_star(map::map_graph& graph) : graph_(graph)
		{
		}

		std::queue<const map::map_node*> search(const map::map_node& source, const map::map_node& target);

		void untag_nodes();
	};
	
}

#endif /* KMINT_UFO_A_STAR_HPP */