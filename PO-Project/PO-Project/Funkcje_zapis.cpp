#pragma once

#include "Funkcje_zapis.h"

bool is_path_exists(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

void make_directory(const std::string& s)
{
	if (_mkdir(s.c_str()) != 0)
	{
		std::cout << "Nie udalo sie stworzyc folderu o nazwie \"" << s << "\"" << std::endl;
	}
}

bool file_exists(std::string fileName, std::string dir)
{
	std::ifstream infile(dir + fileName +".txt");
	return infile.good();
}