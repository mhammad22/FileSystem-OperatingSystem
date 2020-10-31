#include "DirectoryTree.h"

#include <fstream>
#include <sstream>

#include "FAT.h"
#include "Disk.h"

using namespace nlohmann;

DirectoryTree* DirectoryTree::s_Instance = nullptr;
json DirectoryTree::s_Object;

DirectoryTree::DirectoryTree() 

{

	m_Current = &s_Object;
}

void DirectoryTree::Start() {

	std::ifstream fin("VCB/DT.json");

	if (!fin) {

		s_Object = json {};
		Flush();
	}
	else
		fin >> s_Object;
	
	fin.close();
	s_Instance = new DirectoryTree();
}


uint DirectoryTree::AddFile(const std::string& file) {

	if (m_Current->find(file) != m_Current->end())
		return (uint)-1;

	uint index = FAT::GetInstance()->Allocate();
	(*m_Current)[file] = index;

	Flush();
	return index;
}

void DirectoryTree::PowerOff() {

	Flush();
	delete s_Instance;
}

bool DirectoryTree::ChangeDirectory(const std::string& directory) {

	if (directory == "..") { 
		
		if (!m_JsonStack.empty()) {
			
			m_Current = m_JsonStack.top();
			m_JsonStack.pop();
			m_PathStack.pop();
		}
	}
	else {

		auto it = (*m_Current).find(directory);

		if (it != (*m_Current).end()) {

			if ((*it).is_number())
				return false;

			m_JsonStack.push(m_Current);
			m_PathStack.push(it.key());
			m_Current = &(*it);
		}
		else
			return false;
	}
	return true;
}

std::vector<std::string> DirectoryTree::ListDirectories() {

	std::vector<std::string> result;

	for (auto it = m_Current->begin(); it != m_Current->end(); it++)
		result.push_back(it.key());
	
	return result;
}

bool DirectoryTree::AddDirectory(const std::string& directory) {

	if (m_Current->find(directory) != m_Current->end())
		return false;

	(*m_Current)[directory] = nullptr;
	Flush();
	return true;
}

void DirectoryTree::RemoveFile(const std::string& file) {

	auto it = m_Current->find(file);

	if (it != m_Current->end()) {

		if (!(*it).is_number())
			return;

		uint index;
		(*m_Current)[it.key()].get_to(index);

		RemoveFile(index);
		(*m_Current).erase(file);
		Flush();
	}
}

bool DirectoryTree::RemoveDirectory(const std::string& directory) {

	std::stack<json> jsonStack;

	auto ans = m_Current->find(directory);

	if (ans == m_Current->end())
		return false;

	jsonStack.push(*ans);

	while (!jsonStack.empty()) {

		auto val = jsonStack.top();
		jsonStack.pop();

		for (auto it = val.begin(); it != val.end(); it++) {

			if ((*it).is_number()) {

				uint index;
				(*it).get_to(index);

				RemoveFile(index);
			}
			else if ((*it).is_object()) {

				jsonStack.push(*it);
			}
		}
	}

	(*m_Current).erase(directory);
	Flush();
	return true;
}

std::string DirectoryTree::GetCurrentDirectory() { 

	if (m_JsonStack.empty())
		return "root";

	else
	{


	}
	return m_JsonStack.top()->begin().key();
}

void DirectoryTree::Flush() {

	std::ofstream fout("VCB/DT.json");

	if (!fout) {

		std::cout << "VCB Directory Doesn not Exists!" << std::endl;
		return;
	}

	fout << s_Object;
	fout.close();
}

void DirectoryTree::RemoveFile(uint index) const {

	uint key = index;
	uint count = 0;

	while (true)

	 {

		Block block = FAT::GetInstance()->GetBlock(key);

		FAT::GetInstance()->Free(key);

		count++;
		if (block.next == (uint)EOF)
		{
			break;

		}
		else
		{


		}

		key = block.next;
	}

	Disk::CalculateStatus(count);
}


