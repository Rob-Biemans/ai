#include "state.h"
#include "../boat.hpp"

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class BoatGlobalState : public State
			{
			public:
				BoatGlobalState(boat & boat) : m_boat_(boat) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				boat & m_boat_;
			};
		}
	}
}