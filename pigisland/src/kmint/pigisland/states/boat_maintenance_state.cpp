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

				setDockNumber(random_int(0, 3));

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

					if (m_boat_.getTurnsToWait() <= 0) {
						path_maintenance_dock_.pop();
					}

					m_boat_.moveToNextNode(found_index);
				}
				else
				{
					m_boat_.getFSM().ChangeState(new BoatWanderState(m_boat_));
				}
			}

			void BoatMaintenanceState::Exit()
			{
				std::cout << "BoatMaintenanceState::Exit()" << std::endl;

				Dock dock = m_boat_.getMaintenancesPlaces()[dockNumber];

				int repairedFor = 0;
				if (dock.min == dock.max) {
					repairedFor = 50;
				}
				else {
					repairedFor = random_int(dock.min, dock.max);
				}

				m_boat_.repairDamage(dock.id, repairedFor);
				a_star_.untag_nodes();
			}

			std::string BoatMaintenanceState::Name() {
				return "BoatMaintenanceState";
			}
		}
	}
}

