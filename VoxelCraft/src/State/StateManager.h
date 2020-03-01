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
	template <typename T, typename... Args>
	void pushState(Args&&... args) {
		m_states.push(std::make_shared<T>(std::forward<Args>(args)...));
	}

	void popState();

	const StatePtr& getCurrentState() const;
private:
	std::stack<StatePtr> m_states;
};

