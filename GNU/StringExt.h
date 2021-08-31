#pragma once
#include <string>

namespace stdext {

#ifdef _MSC_VER

	std::string to_string(const std::string& _val);

	std::string to_wstring(const std::string& _val);

#endif

	bool is_all_ascii(const std::wstring& _val);

	bool is_all_ascii(const std::string& _val);

	std::string trim(const std::string& _val);
}
