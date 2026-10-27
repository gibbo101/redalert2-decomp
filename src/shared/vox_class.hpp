// EVA voices (VoxClass): Find_Index 0x00716640 (-1 for a null name).
// shared/radar.hpp and shared/wdt_voices.hpp declare the same function as
// Unknown_00716640 (proposal: use this declaration).
#ifndef RA2_SHARED_VOX_CLASS_HPP
#define RA2_SHARED_VOX_CLASS_HPP

class VoxClass {
public:
    static int __fastcall Find_Index(char const *name);    // 0x00716640
    static char const *__fastcall Name_From(int index);    // 0x007158A0 ("none" out of range; name hypothesis)
};

#endif
