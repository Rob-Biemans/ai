#ifndef KMINT_UFO_PRIORITY_QUEUE_HPP
#define KMINT_UFO_PRIORITY_QUEUE_HPP

#include <queue>

namespace kmint::ufo 
{
	template<typename T, typename priority_type>
	struct PriorityQueue {
		using PQElement = std::pair<priority_type, T>;
		std::priority_queue<PQElement, std::vector<PQElement>,
			std::greater<>> values;

		bool empty() const {
			return values.empty();
		}

		void put(T item, priority_type priority) {
			values.emplace(priority, item);
		}

		T get() {
			T best_value = values.top().second;
			values.pop();
			return best_value;
		}
	};
	
}

#endif /* KMINT_UFO_PRIORITY_QUEUE_HPP */