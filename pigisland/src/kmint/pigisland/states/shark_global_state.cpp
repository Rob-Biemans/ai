#pragma once
#include "kmint/pigisland/states/shark_global_state.h"
#include "kmint/pigisland/states/shark_tired_state.h"

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
				std::cout << "Shark tired level at " << m_shark_.getTired() << "%\n";
				if (m_shark_.getTired() >= 100) {
					m_shark_.GetFSM().ChangeState(new SharkTiredState(graph_, m_shark_));
				}
				else {
					m_shark_.addTired();
				}
			}

			void SharkGlobalState::Exit()
			{

			}
		}
	}
}

