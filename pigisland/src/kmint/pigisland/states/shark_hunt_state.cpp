#pragma once
#include "kmint/pigisland/states/shark_hunt_state.h"
#include "kmint/pigisland/states/shark_wander_state.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/pig.hpp"
#include <string>
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void SharkHuntState::Enter()
			{
				// Turns red
				m_shark_.setColor(245, 66, 66);

				std::cout << "SharkHuntState::Enter()" << std::endl;

				auto &a = *last_smelled_pig_;
				map::map_node* node = &graph_[0];
				std::for_each(graph_.begin(), graph_.end(), [&](map::map_node &n)
				{
					if (math::distance(n.location(), a.location()) < math::distance(node->location(), a.location()))
					{
						node = &n;
					}
				});

				path_to_pig_ = a_star_.search(m_shark_.node(), *node);
			}

			void SharkHuntState::Execute()
			{
				//std::cout << "SharkHuntState::Execute()" << std::endl;

				if (!path_to_pig_.empty())
				{
					std::size_t id = path_to_pig_.front()->node_id();
					int found_index = 0;
					for (std::size_t i = 0; i < m_shark_.node().num_edges(); ++i) {
						if (m_shark_.node()[i].to().node_id() == id)
						{
							found_index = i;
						}
					}

					if (m_shark_.getTurnsToWait() <= 0) {
						path_to_pig_.pop();
					}

					m_shark_.moveToNextNode(found_index);
				}
				else
				{
					m_shark_.getFSM().ChangeState(new SharkWanderState(graph_, m_shark_));
				}
			}

			void SharkHuntState::Exit()
			{
				m_shark_.removeColor();
				std::cout << "SharkHuntState::Exit()" << std::endl;
				a_star_.untag_nodes();
			}

			std::string SharkHuntState::Name() {
				return "SharkHuntState";
			}
		}
	}
}

