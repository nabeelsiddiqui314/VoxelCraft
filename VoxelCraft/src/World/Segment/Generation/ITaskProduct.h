#pragma once
#include <memory>

class SegmentManager;

class ITaskProduct
{
public:
	ITaskProduct() {}
	virtual ~ITaskProduct() {}
public:
	virtual void sendProduct(SegmentManager& manager) = 0;
};

