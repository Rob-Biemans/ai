#include "state.h"
#include "kmint/pigisland/a_star.hpp"
#include "../shark.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			class SharkTiredState : public State
			{
			public:
				SharkTiredState(kmint::map::map_graph& g, shark & shark) : m_shark_(shark), a_star_{ g }, graph_{ g } {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
				std::string Name() override;

				std::queue<const kmint::map::map_node*> path_to_resting_place_;
				kmint::map::map_graph& graph_;
				a_star a_star_;
			protected:
				shark & m_shark_;
			};
		}
	}
}