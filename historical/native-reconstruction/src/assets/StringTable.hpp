// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include <map>
namespace ra2 {
// Bounded CSF v3 reader based on supplied file structure. Not a reconstruction
// of the engine's loader, fallback localization or multi-string selection.
// Repeated labels retain all values in file order; ambiguous lookups refuse.
struct LocalizedString {std::string utf8,extra;};
using StringTable=std::map<std::string,std::vector<LocalizedString>>;
StringTable readStringTable(const Data&);
const std::string& localizedText(const StringTable&,const std::string& label);
}
