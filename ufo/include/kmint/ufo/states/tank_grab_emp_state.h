#include "state.h"
#include "../tank.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class TankGrabEmpState : public State
			{
			public:
				TankGrabEmpState(tank & tank) : m_tank_(tank) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				tank & m_tank_;
			};
		}
	}
}