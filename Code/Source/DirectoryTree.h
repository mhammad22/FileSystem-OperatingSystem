#pragma once

#include "json.hpp"

#include <stack>
#include <iostream>

#include "Common.h"

class DirectoryTree {

private:
	static DirectoryTree* s_Instance;

private:
	static nlohmann::json s_Object;
	std::stack<std::string> m_PathStack;
	std::stack<nlohmann::json*> m_JsonStack;
	nlohmann::json* m_Current;

protected:
	DirectoryTree();
	~DirectoryTree() = default;

public:
	static void Start();
	static void PowerOff();

	static DirectoryTree* GetInstance() { return s_Instance; }

	uint AddFile(const std::string& file);
	bool AddDirectory(const std::string& directory);

	bool ChangeDirectory(const std::string& directory);

	std::vector<std::string> ListDirectories();

	void RemoveFile(const std::string& file);
	bool RemoveDirectory(const std::string& directory);

	std::string GetCurrentDirectory();

private:
	static void Flush();
	void RemoveFile(uint index) const;
};

