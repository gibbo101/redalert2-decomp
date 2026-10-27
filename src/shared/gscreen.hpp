// GScreenClass: the root of the game's screen/map chain (GScreen.cpp,
// 0x004E06E0-0x004E1130; RTTI vtable 0x007A2C3C, 22 slots).
//
// Chain (RTTI): MouseClass < ScrollClass < TabClass < SidebarClass <
// PowerClass < RadarClass < DisplayClass < MapClass < GScreenClass < IGameMap.
//
// Layout from the constructor 0x004E08D0 (+0x04 = +0x08 = 0, +0x0C = 2) and
// AI 0x004E10C0, which damps +0x04/+0x08 toward zero every other frame (the
// screen shake offsets that Blit_Display 0x004E0C90 applies through the map
// object's +0x04/+0x08). Slot names follow the TS/RA1 GScreenClass vocabulary
// where the code matches it (Init calls Init_Clear and Init_IO, Render calls
// Draw_It and Blit_Display, the button list is the static Buttons).
#ifndef RA2_SHARED_GSCREEN_HPP
#define RA2_SHARED_GSCREEN_HPP
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/com_persist.hpp"
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/gadget.hpp"
#include "shared/win32_api.hpp"

class Surface;
class NoInitClass;

// The map interface the game objects query (IID 0x007A2C28
// {96F02EC7-6FE8-11D1-B6FD-00A024DDAFD1}); MapClass implements Is_Visible
// (0x00547FA0, __stdcall, one 4-byte Cell).
struct __declspec(novtable) IGameMap : public IUnknown {
    virtual long __stdcall Is_Visible(Cell cell) = 0;                    // slot 3 (+0x0C)
};

extern "C" GUID const IID_IGameMap;     // 0x007A2C28

class GScreenClass : public IGameMap {
public:
    GScreenClass();                                                             // 0x004E08D0
    // Installs the vtable only (inlined into MapClass(NoInitClass const &) 0x00547A60).
    GScreenClass(NoInitClass const &noinit) {}

    // IUnknown: the screen is a static object, so AddRef/Release are fixed.
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);  // slot 0 0x004E08F0
    virtual unsigned long __stdcall AddRef() { return 1; }                      // slot 1 0x0040D100 (kept elsewhere)
    virtual unsigned long __stdcall Release() { return 1; }                     // slot 2 0x0040D110 (kept elsewhere)

    virtual ~GScreenClass() {}                                                  // slot 4 (??_G 0x004E1110)
    virtual void One_Time();                                                    // slot 5  0x004E0950
    virtual void Init(int theater);                                             // slot 6  0x004E0960
    virtual void Init_Clear();                                                  // slot 7  0x004E0980
    virtual void Init_IO();                                                     // slot 8  0x004E0990
    virtual void Get_Input(int &input, int &x, int &y);                         // slot 9  0x004E09D0
    virtual void AI(int &input, Point2D const &xy);                             // slot 10 0x004E10C0
    // Whether gadget belongs to the button list (Buttons is the head of its list).
    virtual bool Is_Button_Listed(GadgetClass &gadget);                         // slot 11 0x004E0AA0
    virtual bool Add_A_Button(GadgetClass &gadget);                             // slot 12 0x004E0AC0
    virtual bool Remove_A_Button(GadgetClass &gadget);                          // slot 13 0x004E0B00
    virtual void Flag_To_Redraw(int complete = false);                          // slot 14 0x004E09A0
    virtual void Render();                                                      // slot 15 0x004E0B30
    virtual void Draw_It(bool complete = false) {}                              // slot 16 0x0049ED00 (kept elsewhere)
    virtual void Blit_Display();                                                // slot 17 0x004E0C50
    // The mouse shape interface MouseClass implements (TS names; argument
    // counts from MouseClass 0x0059F060/0x0059F250/0x0059F080/0x0059F090).
    virtual void Set_Default_Mouse(int mouse, bool wsmall = false) = 0;         // slot 18 (+0x48)
    virtual bool Override_Mouse_Shape(int mouse, bool wsmall = false) = 0;      // slot 19 (+0x4C)
    virtual void Revert_Mouse_Shape() = 0;                                      // slot 20 (+0x50)
    virtual void Mouse_Small(bool wsmall) = 0;                                  // slot 21 (+0x54)

    // Copies area (the whole surface when null) of surface to the window's
    // client area, offset by the screen shake and clipped against the sidebar
    // and the zoom; mouse draws the cursor over it for the copy (0x004E0C90,
    // __fastcall, called from about 40 sites).
    static void __fastcall Blit(bool mouse, Surface *surface, Rect const *area = 0);

    // The gadgets processed by Get_Input and drawn by Render (0x00A40EEC).
    static GadgetClass *Buttons;

    int ShakeX;         // +0x04 screen shake offsets (AI damps them)
    int ShakeY;         // +0x08
    int IsToRedraw;     // +0x0C 0 none, 1 changed parts, 2 complete
};

// The game's screen (0x008324E0) is `Map`, a MouseClass: shared/map_view.hpp.

// The tactical view (0x0083996C): shared/tactical.hpp.
#include "shared/tactical.hpp"

// 3D device used when unknown_flag_852fd7 is set (0x00852FE0; Blit_Display runs
// an empty scene on it): shared/direct3d.hpp's unknown_device_852fe0.
#include "shared/direct3d.hpp"
extern bool unknown_flag_852fd7;                // shared/dsurface.hpp

// Drawn by Render after the buttons (0x00A3DC70, method 0x005B5B30).
class UnknownObjectA3DC70 {
public:
    void Unknown_005B5B30();
    // Places the list (0x005B4C60; DisplayClass slot 42 passes the view's
    // X + 3, Y, 6, 0x62, 0xE, -1, -1, 0, 0x14, 0x62 and its width - 6) and
    // sets its width (0x005B5C60).
    void Unknown_005B4C60(int x, int y, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int width);
    void Unknown_005B5C60(int width);
};
extern UnknownObjectA3DC70 unknown_object_a3dc70;

// The game's tooltip manager (RTTI CCToolTip, shared/tool_tip.hpp): the object
// at 0x008399B0. Render calls its slot 3 with false, Blit asks
// ToolTipManager::Is_Active (0x006EBEE0) whether to keep the bottom strip.
class CCToolTip;
extern CCToolTip *ToolTips;                     // 0x008399B0


// Bottom strip height source of Blit (0x00AC11FC, +0x0C).
struct UnknownStruct_AC11FC {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
};
extern UnknownStruct_AC11FC *unknown_ac11fc;

void __fastcall Unknown_005419E0(bool unknown);              // 0x005419E0 Render, when unknown_flag_a3d8c4
extern bool unknown_flag_a3d8c4;
extern bool unknown_flag_abcd85;                // Render erases the mouse from the sidebar once
extern bool unknown_flag_a40d13;
extern bool unknown_flag_a40b30;                // shared/wwmouse.hpp
extern bool unknown_flag_a40380;
extern bool unknown_flag_8373f6;
extern int unknown_int_839648;                  // shared/wwmouse.hpp (screen width)
extern int unknown_int_a40d34;                  // Blit copies with the last Copy_From flag when zero

extern HWND MainWindow;                     // 0x00B263D8
extern Surface *unknown_surface_839948;     // 0x00839948 (sidebar surface; shared/wwmouse.hpp)
extern Surface *unknown_surface_839950;     // 0x00839950 screen (shared/movie.hpp)
extern Surface *unknown_surface_839954;     // 0x00839954 (Get_Input draws the buttons on it)
extern Surface *unknown_surface_83995c;     // 0x0083995C current drawing surface
extern Surface *unknown_surface_839964;     // 0x00839964 the surface Render composes

#endif
