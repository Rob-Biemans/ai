#pragma once
#include "kmint/pigisland/states/shark_afraid_state.h"
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
			void SharkAfraidState::Enter()
			{
				std::cout << "SharkAfraidState::Enter()" << std::endl;
				// Yellow
				m_shark_.setColor(245, 242, 66);
				m_shark_.set10ForcedTurnsToWander();
			}

			void SharkAfraidState::Execute()
			{
				//std::cout << "SharkAfraidState::Execute()" << std::endl;
				m_shark_.goToNextRandomNode();
				m_shark_.decreaseForcedTurnToWanderByOne();
			}

			void SharkAfraidState::Exit()
			{
				std::cout << "SharkAfraidState::Exit()" << std::endl;
				m_shark_.removeColor();
			}

			std::string SharkAfraidState::Name() {
				return "SharkAfraidState";
			}
		}
	}
}

