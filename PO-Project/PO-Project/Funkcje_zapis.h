#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <direct.h>
#include <sys/stat.h>
#include <fstream>

bool is_path_exists(const std::string& s);

void make_directory(const std::string& s);

bool file_exists(std::string fileName, std::string dir);