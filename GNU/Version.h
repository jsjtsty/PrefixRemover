#pragma once
#include <string>

std::string npr_version();

uint32_t npr_build();

bool npr_preview();

std::string npr_full_version();

const std::string& npr_license();
