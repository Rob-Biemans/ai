#include "kmint/ufo/a_star.hpp"
#include "kmint/ufo/priority_queue.hpp"
#include <stack>

namespace kmint {
	namespace ufo
	{

		std::queue<const kmint::map::map_node*> a_star::search(const kmint::map::map_node& source,
			const kmint::map::map_node& target)
		{
			PriorityQueue<const kmint::map::map_node*, double> queue;
			std::map<const kmint::map::map_node*, const kmint::map::map_node*> source_from;
			std::map<const kmint::map::map_node*, double> cost_so_far;
			queue.put(&source, 0);

			source_from[&source] = &source;
			cost_so_far[&source] = 0;

			while (!queue.empty())
			{
				const kmint::map::map_node& current = *queue.get();

				if (current.node_id() == target.node_id())
				{
					break;
				}

				for (size_t i = 0; i < current.num_edges(); i++)
				{
					// Check weight
					const float weight = current[i].weight();
					const double new_cost = cost_so_far[&current] + weight;
					const kmint::map::map_node& neighbor = current[i].to();

					// Visited the nodes during check
					graph_[neighbor.node_id()].tag(kmint::graph::node_tag::visited);
					untag_queue_.push(&neighbor);

					// Calc cost
					if (cost_so_far.find(&neighbor) == cost_so_far.end()
						|| new_cost < cost_so_far[&neighbor])
					{
						cost_so_far[&neighbor] = new_cost;
						const double priority = new_cost + heuristic(neighbor, target);
						queue.put(&neighbor, priority);
						source_from[&neighbor] = &current;
					}
				}
			}

			return reconstruct_path(&source, &target, source_from);
		}

		void a_star::untag_nodes()
		{
			while (!untag_queue_.empty())
			{
				graph_[untag_queue_.front()->node_id()].tag(graph::node_tag::normal);
				untag_queue_.pop();
			}
		}

		std::queue<const kmint::map::map_node*> a_star::reconstruct_path(const kmint::map::map_node* source,
			const kmint::map::map_node* target,
			std::map<const kmint::map::map_node*, const kmint::map
			::map_node*> source_from)
		{
			//Fill queue
			std::queue<const kmint::map::map_node*> path;
			const kmint::map::map_node* current = target;
			while (current != source)
			{
				path.push(current);
				current = source_from[current];
			}

			//Reverse queue
			std::stack<const kmint::map::map_node*> stack;
			while (!path.empty())
			{
				graph_[path.front()->node_id()].tag(kmint::graph::node_tag::path);
				stack.push(path.front());
				untag_queue_.push(path.front());
				path.pop();
			}
			while (!stack.empty())
			{
				path.push(stack.top());
				stack.pop();
			}

			return path;
		}

		//http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
		// Manhatten distance
		double a_star::heuristic(const kmint::map::map_node& a, const kmint::map::map_node& b) const
		{
			float dx = std::abs(a.location().x() - b.location().x());
			float dy = std::abs(a.location().y() - b.location().y());

			return 1 * (dx + dy);
		}

	}
}