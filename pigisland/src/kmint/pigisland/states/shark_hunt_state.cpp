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
				std::cout << "SharkHuntState::Enter()" << std::endl;
				// laat ook even zien welke varkentjes hij ruikt
				//TODO TESTEN
				for (auto i = m_shark_.begin_perceived(); i != m_shark_.end_perceived(); ++i) {
					auto &a = *i;

					if (dynamic_cast<pig *>(&a)) {
						std::cout << "Smelled a pig at " << a.location().x() << ", " << a.location().y() << "\n";

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
				}
			}

			void SharkHuntState::Execute()
			{
				std::cout << "SharkHuntState::Execute()" << std::endl;
				if (!path_to_pig_.empty())
				{
					std::size_t id = path_to_pig_.front()->node_id();
					int found_index = 0;
					for (std::size_t i = 0; i < m_shark_.node().num_edges(); ++i) {
						if (m_shark_.node()[i].to().node_id() == id) {
							found_index = i;
						}
					}
					m_shark_.node(m_shark_.node()[found_index].to());

					path_to_pig_.pop();
				}
				else
				{
					std::cout << "Shark Reached Last Smelled Pig Position \n";
					m_shark_.getFSM().ChangeState(new SharkWanderState(m_shark_));
				}
			}

			void SharkHuntState::Exit()
			{
				//std::cout << "SharkHuntState::Exit()" << std::endl;
			}
		}
	}
}

