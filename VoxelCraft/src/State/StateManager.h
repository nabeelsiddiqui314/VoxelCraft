#pragma once
#include <stack>
#include "State.h"

typedef std::shared_ptr<State> StatePtr;

class StateManager
{
public:
	StateManager() = default;
	~StateManager() = default;
public:
	void pushState(const StatePtr& state);
	void popState();

	const StatePtr& getCurrentState() const;
private:
	std::stack<StatePtr> m_states;
};

