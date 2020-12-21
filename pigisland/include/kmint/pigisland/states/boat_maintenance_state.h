#include "state.h"
#include "../boat.hpp"
#include "kmint/pigisland/a_star.hpp"

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
			protected:
				boat & m_boat_;
			};
		}
	}
}