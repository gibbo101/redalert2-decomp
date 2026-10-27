// MSSfxEntry::MSSfxEntry(Wstring const &name, Wstring const &line) (0x005B15B0)
// With sound available: line is "file,volume" (volume in percent, clamped
// to 0..100 and scaled to 0..255); keeps the name when audible.
#include "shared/ms_choice.hpp"
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?As_Integer@Wstring@@QBEHXZ=0076f570
// @ref ?Get_Token@Wstring@@QBEHHPBDAAV1@@Z=0076f200

MSSfxEntry::MSSfxEntry(Wstring const &name, Wstring const &line) :
    Name((char const *)0),
    unknown_04(false),
    unknown_08(0),
    Volume(255)
{
    if (name != 0 && unknown_check_406f30()) {
        Wstring file;
        int position = line.Get_Token(0, ",", file);
        Wstring volume;
        line.Get_Token(position, ",", volume);
        if (volume != 0) {
            Volume = volume.As_Integer();
            if (Volume > 100) {
                Volume = 100;
            } else if (Volume < 0) {
                Volume = 0;
            }
            Volume = Volume * 255 / 100;
        }
        if (Volume > 0 && file != 0) {
            Name = name;
        }
    }
}
