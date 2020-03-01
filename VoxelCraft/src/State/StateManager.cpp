#include "StateManager.h"

void StateManager::popState() {
	m_states.pop();
}

const StatePtr& StateManager::getCurrentState() const {
	return m_states.top();
}
