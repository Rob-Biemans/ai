#include "state.h"
#include "../shark.hpp"

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class SharkHuntState : public State
			{
			public:
				SharkHuntState(kmint::map::map_graph& g, shark & shark, kmint::play::actor* a) : m_shark_(shark), a_star_{ g }, graph_{ g }, last_smelled_pig_{ a }{}
				void Enter() override;
				void Execute() override;
				void Exit() override;
				std::string Name() override;

				std::queue<const kmint::map::map_node*> path_to_pig_;
				kmint::map::map_graph& graph_;
				a_star a_star_;
				kmint::play::actor* last_smelled_pig_;
			protected:
				shark & m_shark_;
			};
		}
	}
}