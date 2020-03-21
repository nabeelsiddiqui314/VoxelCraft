#pragma once

class SegmentStack;

class MapGenerator
{
public:
	virtual ~MapGenerator() {}
public:
	virtual void generateStack(SegmentStack& stack, int x, int z) = 0;
};

