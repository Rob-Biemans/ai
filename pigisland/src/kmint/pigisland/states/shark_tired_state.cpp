#pragma once
#include "kmint/pigisland/states/shark_tired_state.h"
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
				//std::cout << "SharkTiredState::Enter()" << std::endl;
			}

			void SharkTiredState::Execute()
			{
				//TODO 
				//m_shark_.GetAStar().untag_nodes();
				//path_to_resting_place_ = m_shark_.GetAStar().search(m_shark_.node(), find_node_of_kind(m_shark_.GetGraph(), m_shark_.GetRestingPlaceChar()));
			}

			void SharkTiredState::Exit()
			{
				//std::cout << "SharkTiredState::Exit()" << std::endl;
			}
		}
	}
}

