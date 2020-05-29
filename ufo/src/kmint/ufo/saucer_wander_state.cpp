#pragma once
#include "../include/kmint/ufo/states/saucer_wander_state.h"
#include <string>
#include <iostream>

namespace kmint
{
	namespace ufo
	{
		namespace states
		{
			//Aan het begin van een ronde starten de UFO's op een willekeurige plek in de stad. Aanvankelijk zullen ze dwalen door de stad. Op het moment dat ze een mens zien, wordt dit hun doelwit.
			void SaucerWanderState::Enter()
			{
				//std::cout << "SaucerWanderState::Enter()" << std::endl;
			}

			void SaucerWanderState::Execute()
			{
				//std::cout << "SaucerWanderState::Execute()" << std::endl;
			}

			void SaucerWanderState::Exit()
			{
				//std::cout << "SaucerWanderState::Exit()" << std::endl;
			}
		}
	}
}

