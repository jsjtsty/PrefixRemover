#include <iostream>
#include <filesystem>
#include <string>
#include "Version.h"
#include "StringExt.h"

namespace filesystem = std::filesystem;
bool isBoldMode = false;

void ShowWelcome()
{
	std::cout << "PrefixRemover Version " << npr_full_version() << std::endl;
	std::cout << "Copyright (C) NulStudio 2014-2021. Licensed under the MIT License." << std::endl;
	std::cout << std::endl;
}

void SelectBoldMode()
{
	std::cout << "PrefixRemover supports \"Bold Mode\". We will show text in different attributes in this mode, "
		"but some terminals (such as cmd.exe) does not support it." << std::endl;
	std::cout << "Do you want to enable \"Bold Mode\"? [y/n] ";
	std::string buffer;
	std::getline(std::cin, buffer);
	buffer = stdext::trim(buffer);
	if (buffer.length() == 1) {
		if (buffer == "Y" || buffer == "y") {
			isBoldMode = true;
			std::cout << "\033[1m\"Bold Mode\"\033[0m enabled. You may restart the program if the display is not correct." << std::endl;
		}
	}
	std::cout << std::endl;
}

int ShowMenu()
{
	if (isBoldMode) {
		std::cout << "\033[1m* Select Mode:\033[0m " << std::endl;
	}
	else {
		std::cout << "* Select Mode: " << std::endl;
	}
	std::cout << "1. Remove Prefix/Suffix in Batch." << std::endl;
	std::cout << "2. About Prefix Remover..." << std::endl;
	std::cout << "3. Exit." << std::endl;
	std::cout << "Enter Selection: ";
	int selection = 0;
	while (true) {
		std::string buffer;
		std::getline(std::cin, buffer);
		selection = atoi(buffer.c_str());
		if (selection == 0 || selection >= 4) {
			std::cout << "Invalid input. Please try again: ";
			continue;
		}
		else {
			break;
		}
	}
	return selection;
}

std::string SelectPath()
{
	if (isBoldMode) {
		std::cout << "\033[36;1m[Step 1 of 3]\033[0m Enter the path to the directory: ";
	}
	else {
		std::cout << "[Step 1 of 3] Enter the path to the directory: ";
	}

	std::string path;
	while (true) {
		std::getline(std::cin, path);
		if (!filesystem::exists(path)) {
			std::cout << "Directory does not exist. Please try again: ";
			continue;
		}

		std::error_code ec;
		if (!filesystem::is_directory(path, ec)) {
			if (ec.value() != 0) {
				std::cout << "Filesystem error detected. Error code: " << ec.value() << ". ";
#				ifdef _MSC_VER
				std::cout << "Error message: " << stdext::to_string(ec.message());
#				else
				std::cout << "Error Message; " << ec.message();
#				endif
				std::cout << std::endl << "Enter path to the directory: ";
				continue;
			}
		}

		break;
	}
	return path;
}

int SelectRemoveMode()
{
	if (isBoldMode) {
		std::cout << "\033[36;1m[Step 2 of 3]\033[0m ";
	}
	else {
		std::cout << "[Step 2 of 3] ";
	}

	std::cout << "What do you want to remove?" << std::endl;
	std::cout << "1. Prefix." << std::endl;
	std::cout << "2. Suffix." << std::endl;
	std::cout << "Enter Selection: ";

	int selection = 0;
	while (true) {
		std::string buffer;
		std::getline(std::cin, buffer);
		selection = atoi(buffer.c_str());
		if (selection == 0 || selection >= 3) {
			std::cout << "Invalid input. Please try again: ";
			continue;
		}
		else {
			break;
		}
	}
	return selection;
}

std::string InputPrefixString(int mode)
{
	if (isBoldMode) {
		std::cout << "\033[36;1m[Step 3 of 3]\033[0m ";
	}
	else {
		std::cout << "[Step 3 of 3] ";
	}

	switch (mode) {
	case 1:
		std::cout << "Enter Prefix: ";
		break;
	case 2:
		std::cout << "Enter Suffix: ";
		break;
	}

	std::string wstr;
	bool flag = true;
	while (flag) {
		std::getline(std::cin, wstr);
		
		while (true) {
			std::string buffer;
			std::cout << "\'" << wstr << "\', Right? [y/n] ";
			std::getline(std::cin, buffer);
			if (buffer.length() != 1) {
				continue;
			}
			if (buffer[0] == L'Y' || buffer[0] == L'y') {
				flag = false;
				break;
			}
			else if (buffer[0] == L'N' || buffer[0] == L'n') {
				std::cout << "Enter the right string: ";
				break;
			}
		}
	}

	return wstr;
}

void RemovePrefix(const std::string& path, int mode, const std::string& wstr)
{
	if (mode == 1) {
		if (isBoldMode) {
			std::cout << "\033[1m# Prefix Remover: \033[0m" << std::endl;
		}
		else {
			std::cout << "# Prefix Remover: " << std::endl;
		}
	}
	else {
		if (isBoldMode) {
			std::cout << "\033[1m# Suffix Remover: \033[0m" << std::endl;
		}
		else {
			std::cout << "# Suffix Remover: " << std::endl;
		}
	}

	int count = 0;

	for (const filesystem::directory_entry& fe : filesystem::directory_iterator(path)) {
		filesystem::path path(fe.path());
		filesystem::path newpath = path;
		std::string name = path.filename().stem().native(), newname;

		if (name.length() <= wstr.length()) {
			continue;
		}

		if (mode == 1) {
			if (name.substr(0, wstr.length()) == wstr) {
				newname = name.substr(wstr.length(), name.length() - wstr.length());
				newpath.replace_filename(newname + path.extension().native());
				filesystem::rename(path, newpath);
				std::cout << "Renamed \'" << path.filename() << "\' to \'" << newpath.filename() << "\'." << std::endl;
				++count;
			}
		}
		else {
			if (name.substr(name.length() - wstr.length(), wstr.length()) == wstr) {
				newname = name.substr(0, name.length() - wstr.length());
				newpath.replace_filename(newname + path.extension().native());
				filesystem::rename(path, newpath);
				std::cout << "Renamed \'" << path.filename() << "\' to \'" << newpath.filename() << "\'." << std::endl;
				++count;
			}
		}
	}

	std::cout << std::endl;
	if (isBoldMode) {
		std::cout << "\033[36;1mOperation succeeded. " << count << " files affected.\033[0m" << std::endl << std::endl;
	}
	else {
		std::cout << "Operation succeeded. " << count << " files affected." << std::endl << std::endl;
	}
}

void ShowPrefixRemover()
{
	std::cout << std::endl;
	if (isBoldMode) {
		std::cout << "\033[1m* Prefix/Suffix Remover: \033[0m" << std::endl;
	}
	else {
		std::cout << "* Prefix/Suffix Remover: " << std::endl;
	}

	std::string path = SelectPath();
	int mode = SelectRemoveMode();
	std::string wstr = InputPrefixString(mode);
	std::cout << std::endl;
	RemovePrefix(path, mode, wstr);
}

void ShowAbout()
{
	std::cout << std::endl;
	if (isBoldMode) {
		std::cout << "\033[1m* About: \033[0m " << std::endl;
	}
	else {
		std::cout << "* About: " << std::endl;
	}
	std::cout << "PrefixRemover - A simple tool to remove prefix or suffix of files." << std::endl;
	std::cout << "Version " << npr_version() << " Build " << npr_build();
	if (npr_preview()) {
		std::cout << " (Preview)";
	}
	std::cout << std::endl;
	std::cout << "Built with GNU GCC 10.1 and C++ 17." << std::endl;
	std::cout << "Copyright (C) NulStudio 2014-2021. Licensed under the MIT License, View License? [y/n] ";

	std::string buffer;
	std::getline(std::cin, buffer);
	buffer = stdext::trim(buffer);
	if (buffer.length() == 1) {
		if (buffer == "Y" || buffer == "y") {
			std::cout << npr_license() << std::endl;
		}
	}
	std::cout << std::endl;
}
