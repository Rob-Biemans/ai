#include "state.h"
#include "../saucer.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class SaucerWanderState : public State
			{
			public:
				SaucerWanderState(saucer & saucer) : m_saucer_(saucer) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				saucer & m_saucer_;
			};
		}
	}
}