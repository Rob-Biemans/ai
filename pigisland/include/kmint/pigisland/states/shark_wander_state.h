#include "state.h"
#include "../shark.hpp"

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class SharkWanderState : public State
			{
			public:
				SharkWanderState(kmint::map::map_graph& g, shark & shark) : m_shark_(shark), graph_{ g } {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
				std::string Name() override;

				kmint::map::map_graph& graph_;
			protected:
				shark & m_shark_;
			};
		}
	}
}