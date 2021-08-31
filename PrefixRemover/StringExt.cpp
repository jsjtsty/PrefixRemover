#include <string>

#ifdef _MSC_VER
#include <Windows.h>
#endif

namespace stdext {
	std::wstring trim(const std::wstring& _val)
	{
		size_t left = 0, right = _val.length();
		for (auto it = _val.cbegin(); it != _val.cend(); ++it, ++left) {
			if (*it != L' ')
				break;
		}
		for (auto it = _val.crbegin(); it != _val.crend(); ++it, --right) {
			if (*it != L' ')
				break;
		}
		return _val.substr(left, right - left);
	}

#ifdef _MSC_VER
	std::string to_string(const std::wstring& _val)
	{
		int len = WideCharToMultiByte(CP_ACP, NULL, _val.c_str(), -1, NULL, 0, NULL, NULL);
		char* buffer = new char[len];
		WideCharToMultiByte(CP_ACP, NULL, _val.c_str(), -1, buffer, len, NULL, NULL);
		std::string str(buffer);
		delete[] buffer;
		return str;
	}

	std::wstring to_wstring(const std::string& _val)
	{
		int len = MultiByteToWideChar(CP_ACP, NULL, _val.c_str(), -1, NULL, 0);
		wchar_t* buffer = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, NULL, _val.c_str(), -1, buffer, len);
		std::wstring str(buffer);
		delete[] buffer;
		return str;
	}
#endif

	bool is_all_ascii(const std::wstring& _val)
	{
		for (const wchar_t c : _val) {
			if (!isascii(c)) {
				return false;
			}
		}
		return true;
	}

	bool is_all_ascii(const std::string& _val)
	{
		for (const char c : _val) {
			if (!isascii(c)) {
				return false;
			}
		}
		return true;
	}
}
