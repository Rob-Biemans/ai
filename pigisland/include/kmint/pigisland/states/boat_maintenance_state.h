#include "state.h"
#include "../boat.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			class BoatMaintenanceState : public State
			{
			public:
				BoatMaintenanceState(kmint::map::map_graph& g, boat & boat) : m_boat_(boat), graph_{ g } {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
				std::string Name() override;

				kmint::map::map_graph& graph_;
			protected:
				boat & m_boat_;
			};
		}
	}
}