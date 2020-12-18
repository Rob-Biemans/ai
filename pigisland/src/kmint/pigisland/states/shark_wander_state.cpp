#pragma once
#include "kmint/pigisland/states/shark_wander_state.h"
#include "kmint/random.hpp"
#include <string>
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void SharkWanderState::Enter()
			{
				std::cout << "SharkWanderState::Enter()" << std::endl;
			}

			void SharkWanderState::Execute()
			{
				std::cout << "SharkWanderState::Execute()" << std::endl;
				int next_index = random_int(0, m_shark_.node().num_edges());
				m_shark_.node(m_shark_.node()[next_index].to());

				// laat ook even zien welke varkentjes hij ruikt
				for (auto i = m_shark_.begin_perceived(); i != m_shark_.end_perceived(); ++i) {
					auto const &a = *i;
					std::cout << "Smelled a pig at " << a.location().x() << ", "
						<< a.location().y() << "\n";
				}
			}

			void SharkWanderState::Exit()
			{
				std::cout << "SharkWanderState::Exit()" << std::endl;
			}
		}
	}
}

