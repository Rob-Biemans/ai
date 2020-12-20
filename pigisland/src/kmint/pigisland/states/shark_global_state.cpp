#pragma once
#include "kmint/pigisland/states/shark_global_state.h"
#include "kmint/pigisland/states/shark_tired_state.h"
#include "kmint/pigisland/states/shark_afraid_state.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void SharkGlobalState::Enter()
			{

			}

			void SharkGlobalState::Execute()
			{
				//std::cout << "Shark tired level at " << m_shark_.getTired() << "%\n";
				if (m_shark_.getTired() >= 100 && !m_shark_.getFSM().isInState("SharkTiredState"))
				{
					m_shark_.getFSM().ChangeState(new SharkTiredState(graph_, m_shark_));
				}
				else if (!m_shark_.getFSM().isInState("SharkTiredState"))
				{
					m_shark_.addTired();
				}

				for (auto i = m_shark_.begin_perceived(); i != m_shark_.end_perceived(); ++i) {
					auto &a = *i;

					if (dynamic_cast<boat *>(&a) && !m_shark_.getFSM().isInState("SharkAfraidState")) 
					{
						if (math::distance(m_shark_.location(), a.location()) <= 500) 
						{
							std::cout << "Noticed a boat at " << a.location().x() << ", " << a.location().y() << "\n";
							m_shark_.getFSM().ChangeState(new SharkAfraidState(graph_, m_shark_));
							break;
						}
					}
				}
			}

			void SharkGlobalState::Exit()
			{

			}

			std::string SharkGlobalState::Name() {
				return "SharkGlobalState";
			}
		}
	}
}

