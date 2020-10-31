#include <iostream>

#include "VFS.h"
#include <string.h>

std::vector<std::string> Tokenize(const std::string& line) {

	std::vector<std::string> result;

	char* buffer = new char[line.length() + 1];

	strcpy(buffer, &line[0]);

	char* token = strtok(buffer, " \n");

	if (token)
		result.push_back(token);

	while (token = strtok(nullptr, " \n"))
		result.push_back(token);

	return result;
}

void Menu() 
{

	std::cout << std::endl << "Requuired System Calls    \t   Explaination     " << std::endl << std::endl;
	std::cout << "ls \t\t --List All Direcctoriees--" << std::endl<< std::endl;
	std::cout << "cd \t\t --Change Directory--" << std::endl<< std::endl;
	std::cout << "mkdir \t\t --Make Directory--" << std::endl<< std::endl;
	std::cout << "rm \t\t --Remove Directory--" << std::endl<< std::endl;
	std::cout << "import \t\t --Import Files to Virtual File--" << std::endl<< std::endl;
	std::cout << "status \t\t --Show Disk's Status" << std::endl<< std::endl;
	std::cout << "Q    \t\t ---Quit--" << std::endl<< std::endl;
}

int main() {
	
	VFS::Start();

	char line[256];
	bool running = true;

	Menu();

	while (running) {

		std::string dir = VFS::GetInstance()->GetCurrentDirectory();

		std::cout << dir << ">> ";

		std::cin.getline(line, 256);

		auto tokens = Tokenize(line);

		if (tokens.size()) {

			if (tokens[0] == "ls") 
			{

				VFS::GetInstance()->ListDirectory();
			}
			else if (tokens[0] == "cd") {

				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->ChangeDirectory(tokens[1]);
				}
				else
					std::cout << std::endl << "Incorrect Syntax ! Check Again" << std::endl << std::endl;
			}
			
			else if (tokens[0] == "rm") {

				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->RemoveDirectory(tokens[1]);
				}
				else
					std::cout << std::endl << "Incorrect Syntax ! Check Again" << std::endl << std::endl;
			}
			else if (tokens[0] == "mkdir") {

				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->MakeDirectory(tokens[1]);
				}
				else
					std::cout << std::endl << "Incorrect Syntax ! Check Again" << std::endl << std::endl;
			}			

			else if (tokens[0] == "status") {
			
				VFS::GetInstance()->DiskStatus();
			}
			else if (tokens[0] == "import") {
			
				if (tokens.size() >= 2)
				{
					VFS::GetInstance()->ImportFile(tokens[1]);
				}
				else
					std::cout << std::endl << "Incorrect Syntax ! Check Again" << std::endl << std::endl;
			}
			else if (tokens[0] == "q" || tokens[0] == "Q") {

				break;
			}
			else {

				std::cout << std::endl << "You Entered an Invalid Command !!!! Try again" << std::endl << std::endl;
			}
		}
	}

	VFS::PowerOff();
	return 0;
}
