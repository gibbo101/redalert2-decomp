// VocType: a sound effect index into the VocClass list (TibSun VocType; VOC_NONE when the
// name is unknown), and the INI reader typed with it (TibSun CCINIClass::Get_VocType; the same
// body as Get_Sound in shared/ccini_class.hpp). RulesClass::Audio_Visual (0x00643E10) reads
// every sound through it into a VocType local. A separate header: a declaration added to
// ccini_class.hpp or voc_class.hpp renumbers the $L labels of the fragile 0x0073FEE0.
#ifndef SHARED_VOC_TYPE_HPP
#define SHARED_VOC_TYPE_HPP

#include "shared/ccini_class.hpp"
#include "shared/voc_class.hpp"

enum VocType {
    VOC_NONE = -1
};

inline VocType Get_VocType(CCINIClass &ini, char const *section, char const *entry, VocType defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        VocType voc = (VocType)VocClass::From_Name(buffer);
        if (voc != VOC_NONE) {
            return voc;
        }
    }
    return defvalue;
}

#endif
