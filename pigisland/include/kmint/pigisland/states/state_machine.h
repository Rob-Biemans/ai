#pragma once
#include "state.h"
#include <string>

#include "kmint/play.hpp"

namespace kmint 
{
	namespace pigisland
	{
		namespace states
		{
			class StateMachine
			{
			private:
				//a pointer to the agent that owns this instance
				play::actor & m_pOwner;

				State* m_pCurrentState;
				//a record of the last state the agent was in
				State* m_pPreviousState;
				//this state logic is called every time the FSM is updated
				State* m_pGlobalState;
			public:
				StateMachine(play::actor & owner) : m_pOwner(owner), m_pCurrentState(NULL), m_pPreviousState(NULL), m_pGlobalState(NULL) {}				
				virtual ~StateMachine() = default;

				//use these methods to initialize the FSM 
				void SetCurrentState(State* s) { m_pCurrentState = s; }
				void SetGlobalState(State* s) { m_pGlobalState = s; }
				void SetPreviousState(State* s) { m_pPreviousState = s; }

				//call this to update the FSM
				void Update() const 
				{
					//if a global state exists, call its execute method 
					if (m_pGlobalState)
					{
						m_pGlobalState->Execute();
					}

					//same for the current state 
					if (m_pCurrentState)
					{
						m_pCurrentState->Execute();
					}
				}

				//change to a new state
				void ChangeState(State* pNewState)
				{
					//assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");
					if (m_pPreviousState != nullptr)
						delete m_pPreviousState;
					//keep a record of the previous state
					m_pPreviousState = m_pCurrentState;

					//call the exit method of the existing state
					m_pCurrentState->Exit();

					//change state to the new state
					m_pCurrentState = pNewState;

					//call the entry method of the new state
					m_pCurrentState->Enter();
				}

				//change state back to the previous state
				void RevertToPreviousState()
				{
					ChangeState(m_pPreviousState);
				}

				//accessors 
				State& CurrentState() const { return *m_pCurrentState; }
				State& GlobalState() const { return *m_pGlobalState; }
				State& PreviousState() const { return *m_pPreviousState; }
			};
		}
	}
}