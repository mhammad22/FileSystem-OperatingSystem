#include "VFS.h"

#include <fstream>
#include <iostream>

#include "FAT.h"
#include "Disk.h"
#include "DirectoryTree.h"

VFS* VFS::s_Instance = nullptr;
std::string VFS::s_Name;
std::string VFS::s_Path;
uint VFS::s_BlockSize = 0;


//it will start the virtual file system of block siz eu have given and name of the disk and
//the import the path....then this will make json directory structre
void VFS::Start() {

	std::ifstream fin("Output.txt");

	if (fin) {
	
		fin >> s_BlockSize;
		fin >> s_Name;
		fin >> s_Path;
	}
	else {
		
		std::ofstream fout("Output.txt");

		std::cout << "Enter Size Of Block(Bytes Format)=  ";
		std::cin >> s_BlockSize;
		std::cout << "Enter Name of Disk = ";
		std::cin >> s_Name;
		std::cout << "Enter Import Path= ";
		std::cin >> s_Path;
		std::cin.ignore(1);
		fout << s_BlockSize << std::endl;
		fout << s_Name << std::endl;
		fout << s_Path << std::endl;

		fout.close();
	}

	fin.close();

	FAT::Start();
	DirectoryTree::Start();
	Disk::Start();

	s_Instance = new VFS();
}

//this function basically remove the directory entered by the
//user from your json structure and update the tree structure of json
void VFS::RemoveDirectory(const std::string& directory) {

	if (!DirectoryTree::GetInstance()->RemoveDirectory(directory))
	{
		std::cout << std::endl << directory << " ------Not Found !!!-------" << std::endl << std::endl;
	}
	else
	{


	}

}

//it it will power off and shutdown the system and delete the instance because you hav shutdwon you virtual system 
void VFS::PowerOff() {

	Disk::PowerOff();
	DirectoryTree::PowerOff();
	FAT::PowerOff();

	delete s_Instance;
}

//it will basically make directory in the root in which u are currently present in VFS
void VFS::MakeDirectory(const std::string& directory) {

	if (!DirectoryTree::GetInstance()->AddDirectory(directory))
	{
		std::cout << std::endl << directory << "------------ Already Exists!------------" << std::endl << std::endl;
	}
		else
	{


	}

}

//it will basically chamge the current directory to the required Directory
void VFS::ChangeDirectory(const std::string& directory) {

	if (!DirectoryTree::GetInstance()->ChangeDirectory(directory))	
	{
		std::cout << std::endl << directory << "-------------- Not Found! ---------------" << std::endl << std::endl;	
	}
		else
	{


	}

}

//it will basically import the file from the import and allocate the block which it needed
void VFS::ImportFile(const std::string& filename) {

	if (!Disk::GetInstance()->Import(filename))
	{
		std::cout << std::endl << "------File Cannot be import() = " << filename << std::endl << std::endl;
	}
		else
	{


	}


}
//it will current working directory
std::string VFS::GetCurrentDirectory() {

	return DirectoryTree::GetInstance()->GetCurrentDirectory();
}

//return status of the disk how many blocks are allocated or not
void VFS::DiskStatus() {

	Disk::GetInstance()->Status();
}

//it it print the List of all directories which we add in our json tree
void VFS::ListDirectory() {

	auto ans = DirectoryTree::GetInstance()->ListDirectories();

	std::cout << std::endl;
	int i=0;
	 while(i < ans.size())
	{
		std::cout << "     " << ans[i] << std::endl;
		i++;
	}
	std::cout << std::endl<< std::endl<< std::endl;
}

























