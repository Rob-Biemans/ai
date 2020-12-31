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
				//std::cout << "Boat damaged level at " << m_boat_.getTotalDamaged() << "%\n";
				if (!m_boat_.getFSM().isInState("BoatMaintenanceState"))
				{
					if (m_boat_.getTotalDamaged() >= 100)
					{
						m_boat_.getFSM().ChangeState(new BoatMaintenanceState(graph_, m_boat_));
					}
					else
					{
						m_boat_.addDamage();
					}
				}

				for (std::size_t ix{}; ix < m_boat_.num_colliding_actors(); ++ix) {
					auto &other = m_boat_.colliding_actor(ix);
					if (dynamic_cast<pig *>(&other))
					{
						auto* savedPig = dynamic_cast<pigisland::pig *>(&other);
						std::cout << "A pig safely climbed onto the boat \n";
						m_boat_.getMemory()->savePigChromosomes(savedPig->getChromosomes());
						savedPig->remove();
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

