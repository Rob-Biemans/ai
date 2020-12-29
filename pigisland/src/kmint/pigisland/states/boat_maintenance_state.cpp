#pragma once
#include "kmint/pigisland/states/boat_maintenance_state.h"
#include "kmint/pigisland/states/boat_wander_state.h"
#include "kmint/pigisland/node_algorithm.hpp"
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

				//TODO dock based on % and learning
				selected_maintenance_dock_ = m_boat_.getMaintenancesPlaces()[dockNumber].node;

				path_maintenance_dock_ = a_star_.search(m_boat_.node(), *selected_maintenance_dock_);
			}

			void BoatMaintenanceState::Execute()
			{
				//std::cout << "BoatMaintenanceState::Execute()" << std::endl;
				std::cout << "m_boat_.getTurnsToWait() " << m_boat_.getTurnsToWait() << " \n";
				if (!path_maintenance_dock_.empty())
				{
					std::size_t id = path_maintenance_dock_.front()->node_id();
					int found_index = 0;
					for (std::size_t i = 0; i < m_boat_.node().num_edges(); ++i) {
						if (m_boat_.node()[i].to().node_id() == id)
						{
							found_index = i;
						}
					}
					m_boat_.moveToNextNode(found_index);

					path_maintenance_dock_.pop();
				}
				else
				{
					m_boat_.getFSM().ChangeState(new BoatWanderState(m_boat_));
				}
			}

			void BoatMaintenanceState::Exit()
			{
				std::cout << "BoatMaintenanceState::Exit()" << std::endl;
				//TODO repairDamage based on %
				int repairedFor = random_int(0, 50);

				m_boat_.repairDamage(dockNumber, 50);
				a_star_.untag_nodes();
			}

			std::string BoatMaintenanceState::Name() {
				return "BoatMaintenanceState";
			}
		}
	}
}

