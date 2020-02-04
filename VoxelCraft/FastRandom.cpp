#include "stdafx.h"
#include "FastRandom.h"


FastRandom::FastRandom(int min, int max) : m_seed(0), m_min(min), m_max(max) {}

void FastRandom::seed(int seed) {
	m_seed = seed;
}

int FastRandom::random() {
	m_seed = 214013*m_seed + 2531011;
	int random =  (m_seed>>16)&0x7FFF;

	return m_min + (random % (m_max - m_min + 1));
}