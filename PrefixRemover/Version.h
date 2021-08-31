#pragma once
#include <string>

std::wstring npr_version();

uint32_t npr_build();

bool npr_preview();

std::wstring npr_full_version();

const std::wstring& npr_license();