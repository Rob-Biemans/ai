#pragma once
#include "kmint/pigisland/states/boat_wander_state.h"
#include <string>
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void BoatWanderState::Enter()
			{
				//std::cout << "BoatWanderState::Enter()" << std::endl;
			}

			void BoatWanderState::Execute()
			{
				//std::cout << "BoatWanderState::Execute()" << std::endl;
			}

			void BoatWanderState::Exit()
			{
				//std::cout << "BoatWanderState::Exit()" << std::endl;
			}

			std::string BoatWanderState::Name() {
				return "BoatWanderState";
			}
		}
	}
}

