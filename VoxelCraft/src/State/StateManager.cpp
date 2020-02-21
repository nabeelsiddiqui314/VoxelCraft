#include "StateManager.h"

void StateManager::pushState(const StatePtr& state) {
	m_states.emplace(state);
}

void StateManager::popState() {
	m_states.pop();
}

const StatePtr& StateManager::getCurrentState() const {
	return m_states.top();
}
