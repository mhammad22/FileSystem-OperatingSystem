#pragma once

#include "Block.h"

#include <stdio.h>

class FAT {

private:
	static FAT* s_Instance;
	static uint s_Entries;
	static FILE* s_File;

protected:
	FAT() = default;
	~FAT() = default;

public:
	static void Start();
	static void PowerOff();

	static FAT* GetInstance() { return s_Instance; }

	static uint GetEntries() { return s_Entries; }

	Block GetBlock(uint key) const;
	uint NextBlock(uint key) const;

	void SetBlock(uint key, const Block& block) const;

	uint Allocate() const;
	void Free(uint index) const;
};
