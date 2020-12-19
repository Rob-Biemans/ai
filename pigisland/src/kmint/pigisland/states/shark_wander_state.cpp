#pragma once
#include "kmint/pigisland/states/shark_wander_state.h"
#include "kmint/pigisland/states/shark_hunt_state.h"
#include "kmint/pigisland/pig.hpp"
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
				//std::cout << "SharkWanderState::Enter()" << std::endl;
				m_shark_.empty_perceived();
			}

			void SharkWanderState::Execute()
			{
				//std::cout << "SharkWanderState::Execute()" << std::endl;
				m_shark_.goToNextRandomNode();
		
				for (auto i = m_shark_.begin_perceived(); i != m_shark_.end_perceived(); ++i) {
					auto &a = *i;

					if (dynamic_cast<pig *>(&a) && !a.removed()) 
					{
						std::cout << "Smelled a pig at " << a.location().x() << ", " << a.location().y() << "\n";
						m_shark_.getFSM().ChangeState(new SharkHuntState(graph_, m_shark_, &a));
						break;
					}
				}
			}

			void SharkWanderState::Exit()
			{
				//std::cout << "SharkWanderState::Exit()" << std::endl;
			}

			std::string SharkWanderState::Name() {
				return "SharkWanderState";
			}
		}
	}
}

