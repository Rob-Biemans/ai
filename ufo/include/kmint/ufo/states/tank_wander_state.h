#include "state.h"
#include "../tank.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class TankWanderState : public State
			{
			public:
				TankWanderState(tank & tank) : State(tank) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			};
		}
	}
}