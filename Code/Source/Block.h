#pragma once

#include "Common.h"

struct Block {

public:
	enum class Status : uint {

		Allocated = 0,
		Free
	};

public:
	Status status;
	uint next;

public:
	Block();
	Block(Status status, uint next);
	~Block() = default;
};
