// GraphicMenu *GraphicMenu::Load(Wstring const &file, Wstring const &section) (0x004DE260): the menu of the
// INI file's section, or 0 when the file is missing or does not load.
#include "shared/graphic_menu_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
// @ref ??0CCFileClass@@QAE@ABVWstring@@@Z=00468f90
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Load@INIClass@@QAEHAAVFileClass@@_N@Z=0050bbe0
// @ref ?Load@GraphicMenu@@SIPAV1@AAVINIClass@@ABVWstring@@@Z=004de380
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0GenericNode@@QAE@XZ=0040e160
// @ref ?Link@GenericNode@@QAEXPAV1@@Z=0040e180
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0

GraphicMenu *__fastcall GraphicMenu::Load(Wstring const &file, Wstring const &section)
{
    CCFileClass inifile(file);
    if (!inifile.Is_Available()) {
        return 0;
    }
    INIClass ini;
    GraphicMenu *menu;
    if (ini.Load(inifile, false) > 0) {
        menu = Load(ini, section);
    } else {
        menu = 0;
    }
    return menu;
}
