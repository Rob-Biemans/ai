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
				// Black
				m_boat_.setColor(1, 1, 1);

				std::cout << "BoatMaintenanceState::Enter()" << std::endl;

				repairHistory = m_boat_.getMemory()->getAllBoatRepairHistory();

				int dock1Chance = m_boat_.getMemory()->getMaintenancePlaceChance(0);
				int dock2Chance = m_boat_.getMemory()->getMaintenancePlaceChance(1);
				int dock3Chance = m_boat_.getMemory()->getMaintenancePlaceChance(2);

				int randomDockNumber;
				int val = (rand() % 100);
				if (repairHistory.empty()) {
					setDockNumber(random_int(0, 3));
				}
				else {
					if (val < dock1Chance) {
						setDockNumber(0);
					}
					else if (val < dock2Chance) {
						setDockNumber(1);
					}
					else {
						setDockNumber(2);
					}
				}

				selected_maintenance_dock_ = m_boat_.getMaintenancesPlaces()[dockNumber].node;

				path_maintenance_dock_ = a_star_.search(m_boat_.node(), *selected_maintenance_dock_);
			}

			void BoatMaintenanceState::Execute()
			{
				//std::cout << "BoatMaintenanceState::Execute()" << std::endl;
				//std::cout << "m_boat_.getTurnsToWait() " << m_boat_.getTurnsToWait() << " \n";
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
				m_boat_.removeColor();
				std::cout << "BoatMaintenanceState::Exit()" << std::endl;

				Dock dock = m_boat_.getMaintenancesPlaces()[dockNumber];

				int repairedFor = 0;
				if (dock.min == dock.max) {
					repairedFor = 50;
				}
				else {
					repairedFor = random_int(dock.min, dock.max);
				}

				// calc chance based on REWARD (more then 50 repaired)
				// if repaired for more than 50, increase chance of dock by 4 and decrease others by 2
				// if repaired for more than 30, increase chance of dock by 2 and decrease others by 1
				// MIN chance = 10
				// MAX chance = 80
				int decreaseChanceVal = 1;
				int increaseChanceVal = 2;
				if (repairedFor >= 30) {
					if (repairedFor >= 50) {
						// Better rewarded
						decreaseChanceVal = 2;
						increaseChanceVal = 4;
					}

					for (size_t i = 0; i < m_boat_.getMaintenancesPlaces().size(); i++)
					{
						if (i != dockNumber) {
							int chance = m_boat_.getMemory()->getMaintenancePlaceChance(i);
							std::cout << i << ") chance = " << chance << std::endl;
							int newDecreasedChance = chance - decreaseChanceVal;

							if (newDecreasedChance < 10)
							{
								newDecreasedChance = 10;
							}

							std::cout << i << ") newDecreasedChance = " << newDecreasedChance << std::endl;
							m_boat_.getMemory()->updateMaintenancePlaceChance(i, newDecreasedChance);
						}
						else {
							int lastChance = m_boat_.getMemory()->getMaintenancePlaceChance(dockNumber);
							std::cout << dockNumber << ") chance = " << lastChance << std::endl;
							int newChance = lastChance + increaseChanceVal;

							if (newChance > 80) {
								newChance = 80;
							}

							std::cout << dockNumber << ") newChance = " << newChance << std::endl;
							m_boat_.getMemory()->updateMaintenancePlaceChance(dockNumber, newChance);
						}
					}
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

