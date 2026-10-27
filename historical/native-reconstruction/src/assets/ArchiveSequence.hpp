// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <functional>
#include <string>
#include <vector>

namespace ra2 {
struct ArchiveRequests { bool success=false; std::vector<std::string> names; };
// Bounded original requests. Directory enumeration is a supplied platform input;
// these helpers do not implement media checks or file/cache lifetime.
ArchiveRequests startupMixRequests(bool enumerate, unsigned mediaIndex,
    const std::vector<std::string>& maps, const std::vector<std::string>& movies,
    const std::function<bool(const std::string&)>& exists);
std::vector<std::string> theaterMixRequests(unsigned theater, int previousTheater);
}
