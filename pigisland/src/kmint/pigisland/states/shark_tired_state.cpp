#pragma once
#include "kmint/pigisland/states/shark_tired_state.h"
#include "kmint/pigisland/states/shark_wander_state.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include <string>
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void SharkTiredState::Enter()
			{
				std::cout << "SharkTiredState::Enter()" << std::endl;

				m_shark_.empty_perceived();

				path_to_resting_place_ = a_star_.search(m_shark_.node(), find_node_of_kind(graph_, m_shark_.getRestingPlaceChar()));
			}

			void SharkTiredState::Execute()
			{
				//std::cout << "SharkTiredState::Execute()" << std::endl;
				if (!path_to_resting_place_.empty())
				{
					std::size_t id = path_to_resting_place_.front()->node_id();
					int found_index = 0;
					for (std::size_t i = 0; i < m_shark_.node().num_edges(); ++i) {
						if (m_shark_.node()[i].to().node_id() == id) 
						{
							found_index = i;
						}
					}

					if (m_shark_.getTurnsToWait() <= 0) {
						path_to_resting_place_.pop();
					}

					m_shark_.moveToNextNode(found_index);
				}
				else
				{
					//std::cout << "Shark Reached resting place \n";
					m_shark_.getFSM().ChangeState(new SharkWanderState(graph_, m_shark_));
				}
			}

			void SharkTiredState::Exit()
			{
				std::cout << "SharkTiredState::Exit()" << std::endl;
				m_shark_.resetTired();
				m_shark_.setRested();
				a_star_.untag_nodes();
			}

			std::string SharkTiredState::Name() {
				return "SharkTiredState";
			}
		}
	}
}

