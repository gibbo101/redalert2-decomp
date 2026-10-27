// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <span>
#include <string_view>
#include <stdexcept>
namespace ra2 {
enum class IniNodeDispatch : std::uint8_t { supplied=0, base=1, entry=2 };
struct IniEntryLink {
    IniEntryLink* next4=nullptr;
    IniEntryLink* previous8=nullptr;
    const char* nameC=nullptr;
    IniNodeDispatch dispatch0=IniNodeDispatch::supplied;
};
struct IniEnumerationSection {IniEntryLink* head18=nullptr;std::int32_t count30=0;};
struct IniSectionIndexEntry {std::uint32_t hash;IniEnumerationSection* section;};
struct IniSectionIndex {
    std::span<IniSectionIndexEntry>& backing;
    std::int32_t& count4;
    std::uint8_t& sortedC;
    IniSectionIndexEntry*& hot10;
    IniEnumerationSection*& fallback;
};
struct IniEnumerationServices {
    // Original CRT qsort is a supplied child, not replaced with a claim that a
    // host sort has its duplicate-key permutation. Arguments are saved pre-call.
    std::function<void(std::span<IniSectionIndexEntry>,std::int32_t)> sort;
    std::function<void(std::int64_t,std::uint64_t,const void*)> store;
    // Finite owned linked-list domain. Refuse traversal beyond supplied backing;
    // do not emulate unsafe/unbounded negative-index cycles.
    std::size_t maximumLinks=0;
};
// Zero-state493FC0, NUL-terminated byte names, without case folding. Only its
// returned CRC is represented; the temporary streaming scratch is not exposed.
std::uint32_t iniSectionNameCrc(std::string_view);
// Complete511280 and511260 over supplied backing; no implicit hot update in find.
IniSectionIndexEntry* findIniSectionIndex(IniSectionIndex&,std::uint32_t,const IniEnumerationServices&);
bool hasIniSectionHot(const IniSectionIndex&,std::uint32_t);
// Complete511090: return a borrowed Section-pointer slot, including fallback.
IniEnumerationSection*& iniSectionValue(IniSectionIndex&,std::uint32_t,const IniEnumerationServices&);
// Complete50CB00/50CE00. INI text/index/list construction remains unjoined.
std::int32_t iniEnumerationCount(IniSectionIndex&,std::optional<std::string_view>,const IniEnumerationServices&);
const char* iniEnumerationKey(IniSectionIndex&,std::optional<std::string_view>,std::int32_t,const IniEnumerationServices&);
}
