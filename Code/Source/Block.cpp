#include "Block.h"

Block::Block()
	: status(Status::Free), next(-1) { }

Block::Block(Status status, uint next)
	: status(status), next(next) { }
