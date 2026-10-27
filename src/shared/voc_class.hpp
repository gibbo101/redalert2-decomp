// VocClass: the sound effect types (Sound.ini entries).
#ifndef RA2_SHARED_VOC_CLASS_HPP
#define RA2_SHARED_VOC_CLASS_HPP

class VocClass {
public:
    static int __fastcall From_Name(char const *name);              // 0x00714940 (-1 if none)
};

// The name of a VocType (0x00714A00; "<none>" when out of range).
char const *__fastcall Voc_Name(int voc);

#endif
