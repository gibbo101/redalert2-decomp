#ifndef RA2_ALPHA_TABLE_CACHE_HPP
#define RA2_ALPHA_TABLE_CACHE_HPP
// Shared table cache at 0x008315B8. Physical extent and original class name
// remain unknown; only its observed thiscall Get/Release interface is declared.
typedef unsigned short const (*AlphaTableRows)[256];
class UnknownAlphaTableCache_008315B8 {
public:
    UnknownAlphaTableCache_008315B8(); // 0x0041E3C0 (empty)
    ~UnknownAlphaTableCache_008315B8(); // 0x0041E3D0 (empty)
    // Finds the shared AlphaLightingRemapClass for a level (or builds and
    // registers it) and takes a reference; the table is its first member.
    AlphaTableRows Get(int count); // 0x0041E3E0
    void Release(AlphaTableRows table); // 0x0041E510
};
extern UnknownAlphaTableCache_008315B8 AlphaTableCache_008315B8;
#endif
