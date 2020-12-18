#pragma once
#include "kmint/pigisland/states/shark_wander_state.h"
#include "kmint/random.hpp"
#include <string>
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void SharkWanderState::Enter()
			{
				std::cout << "SharkWanderState::Enter()" << std::endl;
			}

			void SharkWanderState::Execute()
			{
				std::cout << "SharkWanderState::Execute()" << std::endl;
				int next_index = random_int(0, m_shark_.node().num_edges());
				m_shark_.node(m_shark_.node()[next_index].to());
			}

			void SharkWanderState::Exit()
			{
				std::cout << "SharkWanderState::Exit()" << std::endl;
			}
		}
	}
}

