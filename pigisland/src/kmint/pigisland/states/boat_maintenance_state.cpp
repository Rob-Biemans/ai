#pragma once
#include "kmint/pigisland/states/boat_maintenance_state.h"
#include "kmint/pigisland/pig.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void BoatMaintenanceState::Enter()
			{
				std::cout << "BoatMaintenanceState::Enter()" << std::endl;
			}

			void BoatMaintenanceState::Execute()
			{
				//std::cout << "BoatMaintenanceState::Execute()" << std::endl;
			}

			void BoatMaintenanceState::Exit()
			{
				std::cout << "BoatMaintenanceState::Exit()" << std::endl;
			}

			std::string BoatMaintenanceState::Name() {
				return "BoatMaintenanceState";
			}
		}
	}
}

