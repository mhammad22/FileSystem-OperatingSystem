#pragma once

#include <stdio.h>
#include <string>

#include "Common.h"

class Disk {

private:
	static Disk* s_Instance;

private:
	static FILE* s_FileStream;
	static uint s_FreeBlocks;
	static uint s_AllocatedBlocks;

protected:
	Disk() = default;
	~Disk() = default;

public:
	static void Start();
	static void PowerOff();

	bool Import(const std::string& filename);

	void Status();

	static void CalculateStatus(uint count);

	static Disk* GetInstance() { return s_Instance; }
};
