#include "state.h"
#include "../shark.hpp"

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class SharkAfraidState : public State
			{
			public:
				SharkAfraidState(shark & shark) : m_shark_(shark) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				shark & m_shark_;
			};
		}
	}
}