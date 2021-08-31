#pragma once
#include <string>

namespace stdext {

#ifdef _MSC_VER

	std::string to_string(const std::wstring& _val);

	std::wstring to_wstring(const std::string& _val);

#endif

	bool is_all_ascii(const std::wstring& _val);

	bool is_all_ascii(const std::string& _val);

	std::wstring trim(const std::wstring& _val);
}