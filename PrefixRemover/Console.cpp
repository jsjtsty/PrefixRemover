#include <iostream>
#include <filesystem>
#include <string>
#include "Version.h"
#include "StringExt.h"

namespace filesystem = std::filesystem;
bool isBoldMode = false;

void ShowWelcome()
{
	std::wcout << L"PrefixRemover Version " << npr_full_version() << std::endl;
	std::wcout << L"Copyright (C) NulStudio 2014-2021. Licensed under the MIT License." << std::endl;
	std::wcout << std::endl;
}

void SelectBoldMode()
{
	std::wcout << L"PrefixRemover supports \"Bold Mode\". We will show text in different attributes in this mode, "
		L"but some terminals (such as cmd.exe) does not support it." << std::endl;
	std::wcout << L"Do you want to enable \"Bold Mode\"? [y/n] ";
	std::wstring buffer;
	std::getline(std::wcin, buffer);
	buffer = stdext::trim(buffer);
	if (buffer.length() == 1) {
		if (buffer == L"Y" || buffer == L"y") {
			isBoldMode = true;
			std::wcout << L"\033[1m\"Bold Mode\"\033[0m enabled. You may restart the program if the display is not correct." << std::endl;
		}
	}
	std::wcout << std::endl;
}

int ShowMenu()
{
	if (isBoldMode) {
		std::wcout << L"\033[1m* Select Mode:\033[0m " << std::endl;
	}
	else {
		std::wcout << L"* Select Mode: " << std::endl;
	}
	std::wcout << L"1. Remove Prefix/Suffix in Batch." << std::endl;
	std::wcout << L"2. About Prefix Remover..." << std::endl;
	std::wcout << L"3. Exit." << std::endl;
	std::wcout << L"Enter Selection: ";
	int selection = 0;
	while (true) {
		std::wstring buffer;
		std::getline(std::wcin, buffer);
		selection = _wtoi(buffer.c_str());
		if (selection == 0 || selection >= 4) {
			std::wcout << L"Invalid input. Please try again: ";
			continue;
		}
		else {
			break;
		}
	}
	return selection;
}

std::wstring SelectPath()
{
	if (isBoldMode) {
		std::wcout << L"\033[36;1m[Step 1 of 3]\033[0m Enter the path to the directory: ";
	}
	else {
		std::wcout << L"[Step 1 of 3] Enter the path to the directory: ";
	}

	std::wstring path;
	while (true) {
		std::getline(std::wcin, path);
		if (!filesystem::exists(path)) {
			std::wcout << L"Directory does not exist. Please try again: ";
			continue;
		}

		std::error_code ec;
		if (!filesystem::is_directory(path, ec)) {
			if (ec.value() != 0) {
				std::wcout << L"Filesystem error detected. Error code: " << ec.value() << L". ";
#				ifdef _MSC_VER
				std::wcout << L"Error message: " << stdext::to_wstring(ec.message());
#				else
				std::cout << "Error Message; " << ec.message();
#				endif
				std::wcout << std::endl << L"Enter path to the directory: ";
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
		std::wcout << L"\033[36;1m[Step 2 of 3]\033[0m ";
	}
	else {
		std::wcout << L"[Step 2 of 3] ";
	}

	std::wcout << L"What do you want to remove?" << std::endl;
	std::wcout << L"1. Prefix." << std::endl;
	std::wcout << L"2. Suffix." << std::endl;
	std::wcout << L"Enter Selection: ";

	int selection = 0;
	while (true) {
		std::wstring buffer;
		std::getline(std::wcin, buffer);
		selection = _wtoi(buffer.c_str());
		if (selection == 0 || selection >= 3) {
			std::wcout << L"Invalid input. Please try again: ";
			continue;
		}
		else {
			break;
		}
	}
	return selection;
}

std::wstring InputPrefixString(int mode)
{
	if (isBoldMode) {
		std::wcout << L"\033[36;1m[Step 3 of 3]\033[0m ";
	}
	else {
		std::wcout << L"[Step 3 of 3] ";
	}

	switch (mode) {
	case 1:
		std::wcout << L"Enter Prefix: ";
		break;
	case 2:
		std::wcout << L"Enter Suffix: ";
		break;
	}

	std::wstring wstr;
	bool flag = true;
	while (flag) {
		std::getline(std::wcin, wstr);
		
		while (true) {
			std::wstring buffer;
			std::wcout << L"\'" << wstr << L"\', Right? [y/n] ";
			std::getline(std::wcin, buffer);
			if (buffer.length() != 1) {
				continue;
			}
			if (buffer[0] == L'Y' || buffer[0] == L'y') {
				flag = false;
				break;
			}
			else if (buffer[0] == L'N' || buffer[0] == L'n') {
				std::wcout << L"Enter the right string: ";
				break;
			}
		}
	}

	return wstr;
}

void RemovePrefix(const std::wstring& path, int mode, const std::wstring& wstr)
{
	if (mode == 1) {
		if (isBoldMode) {
			std::wcout << L"\033[1m# Prefix Remover: \033[0m" << std::endl;
		}
		else {
			std::wcout << L"# Prefix Remover: " << std::endl;
		}
	}
	else {
		if (isBoldMode) {
			std::wcout << L"\033[1m# Suffix Remover: \033[0m" << std::endl;
		}
		else {
			std::wcout << L"# Suffix Remover: " << std::endl;
		}
	}

	int count = 0;

	for (const filesystem::directory_entry& fe : filesystem::directory_iterator(path)) {
		filesystem::path path(fe.path());
		filesystem::path newpath = path;
		std::wstring name = path.filename().stem().native(), newname;

		if (name.length() <= wstr.length()) {
			continue;
		}

		if (mode == 1) {
			if (name.substr(0, wstr.length()) == wstr) {
				newname = name.substr(wstr.length(), name.length() - wstr.length());
				newpath.replace_filename(newname + path.extension().native());
				filesystem::rename(path, newpath);
				std::wcout << L"Renamed \'" << path.filename() << L"\' to \'" << newpath.filename() << L"\'." << std::endl;
				++count;
			}
		}
		else {
			if (name.substr(name.length() - wstr.length(), wstr.length()) == wstr) {
				newname = name.substr(0, name.length() - wstr.length());
				newpath.replace_filename(newname + path.extension().native());
				filesystem::rename(path, newpath);
				std::wcout << L"Renamed \'" << path.filename() << L"\' to \'" << newpath.filename() << L"\'." << std::endl;
				++count;
			}
		}
	}

	std::wcout << std::endl;
	if (isBoldMode) {
		std::wcout << L"\033[36;1mOperation succeeded. " << count << L" files affected.\033[0m" << std::endl << std::endl;
	}
	else {
		std::wcout << L"Operation succeeded. " << count << L" files affected." << std::endl << std::endl;
	}
}

void ShowPrefixRemover()
{
	std::wcout << std::endl;
	if (isBoldMode) {
		std::wcout << L"\033[1m* Prefix/Suffix Remover: \033[0m" << std::endl;
	}
	else {
		std::wcout << L"* Prefix/Suffix Remover: " << std::endl;
	}

	std::wstring path = SelectPath();
	int mode = SelectRemoveMode();
	std::wstring wstr = InputPrefixString(mode);
	std::wcout << std::endl;
	RemovePrefix(path, mode, wstr);
}

void ShowAbout()
{
	std::wcout << std::endl;
	if (isBoldMode) {
		std::wcout << L"\033[1m* About: \033[0m " << std::endl;
	}
	else {
		std::wcout << L"* About: " << std::endl;
	}
	std::wcout << L"PrefixRemover - A simple tool to remove prefix or suffix of files." << std::endl;
	std::wcout << L"Version " << npr_version() << L" Build " << npr_build();
	if (npr_preview()) {
		std::wcout << L" (Preview)";
	}
	std::wcout << std::endl;
	std::wcout << L"Built with Visual Studio 2019 16.11.1 and C++ 17." << std::endl;
	std::wcout << L"Copyright (C) NulStudio 2014-2021. Licensed under the MIT License, View License? [y/n] ";

	std::wstring buffer;
	std::getline(std::wcin, buffer);
	buffer = stdext::trim(buffer);
	if (buffer.length() == 1) {
		if (buffer == L"Y" || buffer == L"y") {
			std::wcout << npr_license() << std::endl;
		}
	}
	std::wcout << std::endl;
}