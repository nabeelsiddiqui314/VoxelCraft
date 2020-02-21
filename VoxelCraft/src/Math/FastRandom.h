#pragma once

class FastRandom
{
private:
	FastRandom();
public:
	FastRandom(FastRandom&) = delete;
	~FastRandom() = default;
public:
	static FastRandom& get();
public:
	void seed(int seed);
	int random();
private:
	int m_seed;
};

