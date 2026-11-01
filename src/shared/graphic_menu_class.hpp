// GraphicMenu (RTTI GraphicMenu, vtable 0x007A2B3C, 0x70 bytes): a full-screen menu read from an INI section;
// its items (shared/graphic_menu.hpp) live in Items and draw through Engine. Unit 0x004DE240-0x004DEF2F
// (its header-static rect 0x004DE240, Load 0x004DE260, the members to 0x004DEEEF, then the INIClass and GraphicMenu
// scalar deleting destructors 0x004DEEF0/0x004DEF10).
// Layout from the constructor 0x004DE820; member and method names are hypotheses.
#ifndef RA2_SHARED_GRAPHIC_MENU_CLASS_HPP
#define RA2_SHARED_GRAPHIC_MENU_CLASS_HPP

#include "shared/graphic_menu.hpp"
#include "shared/wstring.hpp"

class INIClass;
class MSAnim;

class GraphicMenu {
public:
    GraphicMenu();                                                          // 0x004DE820
    virtual ~GraphicMenu();                                                 // 0x004DE880 (scalar deleting 0x004DEF10)

    // Reads the menu from section of the INI file (0 when the file or section is missing).
    static GraphicMenu *__fastcall Load(Wstring const &file, Wstring const &section);       // 0x004DE260
    static GraphicMenu *__fastcall Load(INIClass &ini, Wstring const &section);             // 0x004DE380
    void Set_Item_Visible(int id, bool visible);                            // 0x004DE960
    int Run();                                                              // 0x004DE9E0
    void Set_Anim(MSAnim *anim);                                            // 0x004DED20
    void Set_Theme(Wstring const &theme);                                   // 0x004DED60
    void Add_Item(GraphicMenuItem *item);                                   // 0x004DED70
    GraphicMenuItem *Item_At(Point2D const &point);                         // 0x004DEDC0 (slot 2 hit test)
    GraphicMenuItem *Item_For(int key);                                     // 0x004DEE50 (slot 1)
    void Set_Background(Wstring const &background);                         // 0x004DEEE0

    MSEngine Engine;                                                        // +0x04
    Wstring Background;                                                     // +0x4C "Title.PCX"
    Wstring Theme;                                                          // +0x50 "Intro"
    MSAnim *Anim;                                                           // +0x54 the background animation
    DynamicVectorClass<GraphicMenuItem *> Items;                            // +0x58
};

#endif
