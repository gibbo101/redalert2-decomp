// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/IniRecords.hpp"
namespace ra2 {
struct IniKeyIndexEntry {std::uint32_t hash=0;IniRecordEntry* entry=nullptr;};
// The original has two index instantiations: Section* and Entry*. Keep their
// actual typed payloads while sharing the recovered field/copy/search algorithms.
template<class Entry> struct IniIndexTraits;
template<> struct IniIndexTraits<IniKeyIndexEntry> {
    using Payload=IniRecordEntry;
    static Payload*& value(IniKeyIndexEntry& e){return e.entry;}
};
template<> struct IniIndexTraits<IniSectionIndexEntry> {
    using Payload=IniEnumerationSection;
    static Payload*& value(IniSectionIndexEntry& e){return e.section;}
};
template<class Entry> struct IniIndexStorage {
    using Payload=typename IniIndexTraits<Entry>::Payload;
    std::span<Entry>& backing;
    std::int32_t& count4;
    std::int32_t& capacity8;
    std::uint8_t& sortedC;
    Entry*& hot10;
    Payload*& fallback;
};
template<class Entry> struct IniIndexStorageServices {
    // Requests preserve the original wrapped32 byte size and eight-byte stride,
    // independent of native pointer/record size. Heap and CRT sorting are supplied.
    std::function<std::span<Entry>(std::uint32_t)> allocate;
    std::function<void(std::span<Entry>)> release;
    std::function<void(std::span<Entry>,std::int32_t)> sort;
    std::function<void(std::int32_t,std::uint32_t,const void*)> store;
    std::function<void(Entry*,std::int32_t,std::uint32_t,const void*)> entryStore;
};
// Complete510CE0 (zeroed key index),510D00 (append) and5111D0 (Section reserve).
template<class E> void constructIniIndex(IniIndexStorage<E>,const IniIndexStorageServices<E>&);
template<class E> bool growIniIndex(IniIndexStorage<E>,std::int32_t,const IniIndexStorageServices<E>&);
template<class E> bool appendIniIndex(IniIndexStorage<E>,const std::uint32_t&,typename IniIndexTraits<E>::Payload* const&,const IniIndexStorageServices<E>&);
// Complete key510DD0/510E70/511150 and Section510FF0, with existing Section
//511090/511280 separately rechecked on the same borrowed fields. Queries stay live.
template<class E> bool containsIniIndex(IniIndexStorage<E>,const std::uint32_t&,const IniIndexStorageServices<E>&);
template<class E> typename IniIndexTraits<E>::Payload*& iniIndexValue(IniIndexStorage<E>,const std::uint32_t&,const IniIndexStorageServices<E>&);
template<class E> E* findIniIndex(IniIndexStorage<E>,const std::uint32_t&,const IniIndexStorageServices<E>&);
}
