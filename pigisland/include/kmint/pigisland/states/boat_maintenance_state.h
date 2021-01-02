#include "state.h"
#include "../boat.hpp"
#include "kmint/pigisland/a_star.hpp"
#include "kmint/random.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			class BoatMaintenanceState : public State
			{
			public:
				BoatMaintenanceState(kmint::map::map_graph& g, boat & boat) : m_boat_(boat), a_star_{ g }, graph_{ g } {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
				std::string Name() override;

				std::queue<const kmint::map::map_node*> path_maintenance_dock_;
				kmint::map::map_graph& graph_;
				a_star a_star_;
				kmint::map::map_node* selected_maintenance_dock_;

				void setDockNumber(int value) { dockNumber = value; }
				int dockNumber = 0;
				std::vector<RepairHistory> repairHistory;
				int dock1 = 0;
				int dock2 = 0;
				int dock3 = 0;
			protected:
				boat & m_boat_;
			};
		}
	}
}