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
				SharkHuntState(shark & shark) : m_shark_(shark) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				shark & m_shark_;
			};
		}
	}
}