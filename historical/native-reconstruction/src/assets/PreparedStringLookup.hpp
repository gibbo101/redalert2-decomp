// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/StringTable.hpp"
#include "sim/StringLookup.hpp"
namespace ra2 {
// Immutable host association of authored CSF v3 decoding to recovered lookup.
// Sorting/slot construction/UTF-8 presentation are supplied adapters, not the
// original CSF loader. Missing or multi-value labels refuse when requested.
class PreparedStringLookup {
    const StringTable table_;
    std::vector<StringLookupLabel> labels_;
    std::vector<std::uint32_t> handles_;
    std::vector<const std::string*> values_;
public:
    explicit PreparedStringLookup(const Data&);
    PreparedStringLookup(const PreparedStringLookup&)=delete;
    PreparedStringLookup& operator=(const PreparedStringLookup&)=delete;
    const std::string& text(std::string_view)const;
};
}
