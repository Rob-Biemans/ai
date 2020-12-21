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

				// Look for specific maintance dock node
				map::map_node* node = &graph_[0];
				std::for_each(graph_.begin(), graph_.end(), [&](map::map_node &n)
				{
					if (n.node_info().kind == '1')
					{
						selected_maintenance_dock_ = &n;
					}
				});
				// end look

				auto &a = *selected_maintenance_dock_;
				std::for_each(graph_.begin(), graph_.end(), [&](map::map_node &n)
				{
					if (math::distance(n.location(), a.location()) < math::distance(node->location(), a.location()))
					{
						node = &n;
					}
				});

				path_maintenance_dock_ = a_star_.search(m_boat_.node(), *node);
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
				m_boat_.repairDamage(1, 50);
				a_star_.untag_nodes();
			}

			std::string BoatMaintenanceState::Name() {
				return "BoatMaintenanceState";
			}
		}
	}
}

