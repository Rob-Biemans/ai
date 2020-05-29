#pragma once
#include "../include/kmint/ufo/states/saucer_chase_tank_state.h"
#include <string>
#include <iostream>

namespace kmint
{
	namespace ufo
	{
		namespace states
		{
			//Als een UFO een tank ziet, zal hij stoppen waarmee hij bezig is en de tank volgen. Wat er gebeurt wanneer een UFO en tank elkaar ontmoeten lees je in paragraaf 5.
			void SaucerChaseTankState::Enter()
			{
				//std::cout << "SaucerChaseTankState::Enter()" << std::endl;
			}

			void SaucerChaseTankState::Execute()
			{
				//std::cout << "SaucerChaseTankState::Execute()" << std::endl;
			}

			void SaucerChaseTankState::Exit()
			{
				//std::cout << "SaucerChaseTankState::Exit()" << std::endl;
			}
		}
	}
}

