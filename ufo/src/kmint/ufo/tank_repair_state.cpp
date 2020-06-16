#pragma once
#include "../include/kmint/ufo/states/tank_repair_state.h"
#include <string>
#include <iostream>

namespace kmint
{
	namespace ufo
	{
		namespace states
		{
			void TankRepairState::Enter()
			{
				//TODO find ANDRE and set waypoints and move.
			}

			void TankRepairState::Execute()
			{
				//CHECK if next of ANDRE (if true then exit this state)
				//TODO find ANDRE new location and set waypoint and move.
			}

			void TankRepairState::Exit()
			{
				//TODO remove A* and reset health points to 100 (max)
			}
		}
	}
}

