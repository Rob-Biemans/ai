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
				TankWanderState(tank & tank) : m_tank_(tank) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				tank & m_tank_;
			};
		}
	}
}