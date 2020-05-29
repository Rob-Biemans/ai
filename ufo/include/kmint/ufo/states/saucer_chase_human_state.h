#include "state.h"
#include "../saucer.hpp"

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class SaucerChaseHumanState : public State
			{
			// De UFO zal het mens blijven achtervolgen tot hij deze gevangen heeft of een tank ziet.In zijn achtervolging houdt de UFO rekening met de snelheid van de persoon die hij achtergevolgd.
			public:
				SaucerChaseHumanState(saucer & saucer) : m_saucer_(saucer) {}
				void Enter() override;
				void Execute() override;
				void Exit() override;
			protected:
				saucer & m_saucer_;
			};
		}
	}
}