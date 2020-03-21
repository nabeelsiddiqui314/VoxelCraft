#pragma once
#include "ITaskProduct.h"

class IConcurrentTask
{
public:
	IConcurrentTask() {}
	virtual ~IConcurrentTask() {}
public:
	virtual void execute() = 0;
	virtual std::shared_ptr<ITaskProduct> getProduct() = 0;
};