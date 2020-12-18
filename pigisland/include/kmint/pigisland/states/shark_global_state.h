#include "state.h"
#include "../shark.hpp"

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class SharkGlobalState : public State
			{
			public:
				SharkGlobalState(kmint::map::map_graph& g, shark & shark) : m_shark_(shark), graph_{ g } {}
				void Enter() override;
				void Execute() override;
				void Exit() override;

				kmint::map::map_graph& graph_;
			protected:
				shark & m_shark_;
			};
		}
	}
}