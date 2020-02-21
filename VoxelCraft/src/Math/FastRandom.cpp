#include "FastRandom.h"


FastRandom::FastRandom() : m_seed(0) {}

FastRandom& FastRandom::get() {
	static FastRandom instance;
	return instance;
}

void FastRandom::seed(int seed) {
	m_seed = seed;
}

int FastRandom::random() {
	m_seed = 214013 * m_seed + 2531011;
	return  (m_seed >> 16) & 0x7FFF;
}