// int __fastcall Theater_Choice_Menu(int faction) (0x00768DD0): runs the WDTChoice.ini
// menu section "TheaterChoice<faction name>Menu" and returns its choice 1-3 (0 for none or
// cancel). Names are hypotheses; faction stays in ecx for Faction_Name. The menu type and
// its loader 0x004DE260 / run 0x004DE9E0 are declared here until their unit is recovered.
// @ref _sprintf=007820f4
// @ref ?Faction_Name@@YIABVWstring@@H@Z=007685a0
// @ref ?Load@GraphicMenu@@SIPAV1@ABVWstring@@0@Z=004de260
// @ref ?Run@GraphicMenu@@QAEHXZ=004de9e0
// @ref ??_C@_0BE@PFNJ@TheaterChoice?$CFsMenu?$AA@=008005ac
// @ref ??_C@_0O@FDI@WDTChoice?4ini?$AA@=0080059c
#include "shared/wstring.hpp"

Wstring const &__fastcall Faction_Name(int faction);

class GraphicMenu {
public:
    virtual ~GraphicMenu();
    static GraphicMenu *__fastcall Load(Wstring const &file, Wstring const &section);
    int Run();
};

int __fastcall Theater_Choice_Menu(int faction)
{
    char buffer[128];
    sprintf(buffer, "TheaterChoice%sMenu", Faction_Name(faction));
    GraphicMenu *menu = GraphicMenu::Load("WDTChoice.ini", buffer);
    if (!menu) {
        return 0;
    }
    int choice = menu->Run();
    delete menu;
    switch (choice) {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
    }
    return 0;
}
