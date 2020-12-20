#pragma once
#include "kmint/pigisland/states/boat_global_state.h"
#include "kmint/pigisland/states/boat_maintenance_state.h"
#include "kmint/pigisland/pig.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void BoatGlobalState::Enter()
			{

			}

			void BoatGlobalState::Execute()
			{
				//std::cout << "Shark tired level at " << m_shark_.getTired() << "%\n";
				if (m_boat_.getTotalDamaged() >= 100 && !m_boat_.getFSM().isInState("BoatMaintenanceState"))
				{
					m_boat_.getFSM().ChangeState(new BoatMaintenanceState(graph_, m_boat_));
				}
				else if (!m_boat_.getFSM().isInState("BoatMaintenanceState"))
				{
					m_boat_.addDamage();
				}

				for (std::size_t ix{}; ix < m_boat_.num_colliding_actors(); ++ix) {
					auto &other = m_boat_.colliding_actor(ix);
					if (dynamic_cast<pig *>(&other))
					{
						std::cout << "A pig safely climbed onto the boat \n";
						other.remove();
					}
				}
			}

			void BoatGlobalState::Exit()
			{

			}

			std::string BoatGlobalState::Name() {
				return "BoatGlobalState";
			}
		}
	}
}

