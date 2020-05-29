#pragma once
#include "../include/kmint/ufo/states/saucer_chase_human_state.h"
#include <string>
#include <iostream>

namespace kmint
{
	namespace ufo
	{
		namespace states
		{
			// De UFO zal het mens blijven achtervolgen tot hij deze gevangen heeft of een tank ziet.In zijn achtervolging houdt de UFO rekening met de snelheid van de persoon die hij achtergevolgd.
			void SaucerChaseHumanState::Enter()
			{
				//std::cout << "SaucerChaseHumanState::Enter()" << std::endl;
			}

			void SaucerChaseHumanState::Execute()
			{
				//std::cout << "SaucerChaseHumanState::Execute()" << std::endl;
			}

			void SaucerChaseHumanState::Exit()
			{
				//std::cout << "SaucerChaseHumanState::Exit()" << std::endl;
			}
		}
	}
}

