#include "FAT.h"

#include "VFS.h"

#include <fstream>

FAT* FAT::s_Instance = nullptr;
uint FAT::s_Entries = 1000;
FILE* FAT::s_File = nullptr;

void FAT::Start() {
	
	s_File = fopen("VCB/FAT.bin", "r");

	if (!s_File) {
		
		s_File = fopen("VCB/FAT.bin", "wb+");

		Block block;

		for (uint i = 0; i < s_Entries; i++)
			fwrite((const void*)(&block), sizeof(Block), 1, s_File);

		fclose(s_File);
	}
	else
	{




	}
	
	fclose(s_File);
	s_File = fopen("VCB/FAT.bin", "rb+");

	s_Instance = new FAT();
}

void FAT::PowerOff() {

	fclose(s_File);
	delete s_Instance;
}

Block FAT::GetBlock(uint key) const {

	Block block;

	fseek(s_File, key * (size_t)sizeof(Block), SEEK_SET);
	fread((void*)(&block), sizeof(Block), 1, s_File);
	fseek(s_File, 0, SEEK_SET);

	return block;
}

uint FAT::NextBlock(uint key) const {

	return GetBlock(key).next;
}

uint FAT::Allocate() const {

	for (uint i = 0; i < s_Entries; i++) {

		auto block = GetBlock(i);

		if (block.status == Block::Status::Free) {
			
			block.status = Block::Status::Allocated;
			SetBlock(i, block);
			return i;
		}
		else
		{




		}
	}

	return -1;
}

void FAT::SetBlock(uint key, const Block& block) const {

	fseek(s_File, key * (size_t)sizeof(Block), SEEK_SET);
	fwrite((void*)(&block), sizeof(Block), 1, s_File);
	fseek(s_File, 0, SEEK_SET);
}

void FAT::Free(uint index) const {

	SetBlock(index, Block());
}
