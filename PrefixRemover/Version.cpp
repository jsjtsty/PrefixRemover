#include <string>

const std::wstring NPR_VERSION = L"1.0";
constexpr bool NPR_IS_PREVIEW = false;
constexpr uint32_t NPR_BUILD = 2;

const std::wstring NPR_LICENSE(
	LR"LICENSE(The MIT License

Copyright 2014-2021 NulStudio

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.)LICENSE",
1071);

std::wstring npr_version()
{
	return NPR_VERSION;
}

uint32_t npr_build()
{
	return NPR_BUILD;
}

bool npr_preview()
{
	return NPR_IS_PREVIEW;
}

std::wstring npr_full_version()
{
	return NPR_VERSION + (NPR_IS_PREVIEW ? L" (Preview)" : L"");
}

const std::wstring& npr_license()
{
	return NPR_LICENSE;
}