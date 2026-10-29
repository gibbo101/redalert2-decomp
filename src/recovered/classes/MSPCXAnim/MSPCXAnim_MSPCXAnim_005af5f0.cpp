// MSPCXAnim::MSPCXAnim(Wstring const &name, DynamicVectorClass<MSAnim *> *anims, bool unknown_28) (0x005AF5F0)
// Loads "<name up to the first '.'>.PCX" and centres it on the background surface.
#include "shared/ms_anim.hpp"
#include "shared/wstring.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??_7MSPCXAnim@@6B@=007a6e80
// @ref ??_C@_01PJCK@?4?$AA@=007dbe44
// @ref ??_C@_04DCKM@?4PCX?$AA@=007d9d84
// @ref ?unknown_load_pcx_60d110@@YIPAVSurface@@PAVFileClass@@HHH@Z=0060d110
// @ref ??0CCFileClass@@QAE@ABVWstring@@@Z=00468f90
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940

MSPCXAnim::MSPCXAnim(Wstring const &name, DynamicVectorClass<MSAnim *> *anims, bool unknown_28) :
    Background(unknown_surface_839958),
    Anims(anims),
    Image(0),
    unknown_28(unknown_28),
    Done(false),
    PCXRect(0, 0, 0, 0)
{
    unknown_0C = true;
    if (name != 0) {
        Wstring base;
        name.Get_Token(0, ".", base);
        CCFileClass file(base + ".PCX");
        if (file.Is_Available()) {
            Image = unknown_load_pcx_60d110(&file, 0, 0, 0);
            if (Image != 0) {
                PCXRect = Image->Get_Rect();
                Rect screen = Background->Get_Rect();
                PCXRect.X += (screen.Width - PCXRect.Width) / 2;
                PCXRect.Y += (screen.Height - PCXRect.Height) / 2;
            }
        }
    }
}
