#include "state.h"
#include "../saucer.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class SaucerChaseTankState : public State
			{
			//Als een UFO een tank ziet, zal hij stoppen waarmee hij bezig is en de tank volgen. Wat er gebeurt wanneer een UFO en tank elkaar ontmoeten lees je in paragraaf 5.
			public:
				SaucerChaseTankState(saucer & saucer) : m_saucer_(saucer) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				saucer & m_saucer_;
			};
		}
	}
}