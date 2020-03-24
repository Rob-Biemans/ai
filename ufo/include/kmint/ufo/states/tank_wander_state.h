#include "state.h"
#include "../tank.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class TankWanderState : public State<tank>
			{
			public:
				TankWanderState() = default;
				void Enter(tank& tank) override;
				void Execute(tank& tank) override;
				void Exit(tank& tank) override;
			};
		}
	}
}