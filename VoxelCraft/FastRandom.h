#pragma once

class FastRandom
{
public:
	FastRandom(int min, int max);
	~FastRandom() = default;
public:
	void seed(int seed);
	int random();
private:
	int m_seed;
	int m_min;
	int m_max;
};

