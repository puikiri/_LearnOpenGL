#ifndef FILE_H
#define FILE_H

#include "include.h"
#include <fstream>
#include <sstream>

class File
{
public:
	File();
	~File();

	static std::string readFileData(std::string path);

private:

public:

private:

};

File::File()
{
}

File::~File()
{
}


std::string File::readFileData(std::string path) 
{
	std::stringstream strStream;
	std::ifstream iStream;
	iStream.open(path);
	strStream << iStream.rdbuf();
	iStream.close();
	return strStream.str();
}



#endif