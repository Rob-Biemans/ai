#pragma once
#include "kmint/pigisland/states/shark_tired_state.h"
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
				a_star_.untag_nodes();
				path_to_resting_place_ = a_star_.search(m_shark_.node(), find_node_of_kind(graph_, m_shark_.GetRestingPlaceChar()));
				//std::cout << "SharkTiredState::Enter()" << std::endl;
			}

			void SharkTiredState::Execute()
			{
				//std::cout << "SharkTiredState::Execute()" << std::endl;
			}

			void SharkTiredState::Exit()
			{
				//std::cout << "SharkTiredState::Exit()" << std::endl;
			}
		}
	}
}

