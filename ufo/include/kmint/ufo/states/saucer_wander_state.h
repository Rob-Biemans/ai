#include "state.h"
#include "../saucer.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			//Aan het begin van een ronde starten de UFO's op een willekeurige plek in de stad. Aanvankelijk zullen ze dwalen door de stad. Op het moment dat ze een mens zien, wordt dit hun doelwit.
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