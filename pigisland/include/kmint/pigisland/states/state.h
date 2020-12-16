#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include <string>

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class State
			{
			public:
				virtual ~State() = default;
				virtual void Enter() = 0;
				virtual void Execute() = 0;
				virtual void Exit() = 0;
			};
		}
	}
}