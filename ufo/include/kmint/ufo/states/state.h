#pragma once
#include <string>

namespace kmint 
{
	namespace ufo
	{
		namespace states
		{
			template <class entity_type>
			class State
			{
			public:
				virtual ~State() = default;
				virtual void Enter(entity_type &) = 0;
				virtual void Execute(entity_type &) = 0;
				virtual void Exit(entity_type &) = 0;
			};
		}
	}
}