#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include <string>

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			class State
			{
			public:
				State(play::map_bound_actor & actor) : m_actor_(actor) {}
				virtual ~State() = default;
				virtual void Enter() = 0;
				virtual void Execute() = 0;
				virtual void Exit() = 0;
			protected:
				play::map_bound_actor & m_actor_;
			};
		}
	}
}