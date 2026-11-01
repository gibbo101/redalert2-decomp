// TabClass: the command-bar layer of the screen chain (Tab.cpp, from the
// header statics at 0x006A0270; RTTI vtable 0x007A64E4, 55 slots), derived
// from SidebarClass (MouseClass < ScrollClass < TabClass < SidebarClass).
//
// Most of Tab.cpp's state is static: 25 shape buttons with their shapes,
// load flags and a slot-to-button map, two more shape buttons, the bar's
// metrics and the command names. Static functions are named by address
// (owners and meanings are hypotheses noted per declaration).
#ifndef RA2_SHARED_TAB_HPP
#define RA2_SHARED_TAB_HPP
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/sidebar.hpp"

// The notice interface TabClass implements at +0x4EE8 (vtable 0x0079AE44
// for the interface itself).
#include "shared/notice.hpp"
#include "shared/mouse.hpp"

// A 16-byte member at TabClass +0x4EEC (constructor 0x00494510 clears it).
struct UnknownTab4EEC {
    UnknownTab4EEC();
    void Unknown_00494650(bool forced);    // 0x00494650 (TabClass::AI, every frame; TibSun CreditClass::AI)
    void Unknown_00494530(bool arg);   // 0x00494530 (TabClass::Draw_It, after the background)
    UnknownTab4EEC(NoInitClass const &noinit) {}
    int unknown_00;
    int unknown_04;     // +0x04 (TabClass +0x4EF0, cleared by slot 53)
    bool unknown_08;
    bool unknown_09;
    bool unknown_0a;
    int unknown_0c;
};

// Draw_It's function-local static: where the mouse was last seen over the bar
// (0x00ABE348, with an empty destructor registered at exit, 0x006A1700).
struct UnknownTabSpot {
    UnknownTabSpot() : X(0), Y(0) {}
    ~UnknownTabSpot() {}
    int X;
    int Y;
};

class TabClass : public SidebarClass, public INoticeSink {
public:
    TabClass();                                                 // 0x006A06E0
    // Restore-in-place form (the copy the linker kept is 0x0059FF60, Mouse.cpp).
    TabClass(NoInitClass const &noinit)
        : SidebarClass(noinit), unknown_4eec(noinit), unknown_4efc(noinit), unknown_4f08(noinit)
    {
    }
    virtual bool INoticeSink_Unknown(int code, int arg);        // 0x006A2020 (secondary vtable 0x007A64DC)
    virtual void One_Time();                                    // slot 5  0x006A0B20
    virtual void Init_IO();                                     // slot 8  0x006A0C50
    virtual void AI(int &input, Point2D const &xy);             // slot 10 0x006A0F30
    virtual void Draw_It(bool complete = false);                // slot 16 0x006A12D0
    virtual wchar_t const *unknown_slot33(int id);              // slot 33 0x006A20B0
    virtual void unknown_slot50();                              // slot 50 0x006A0B30 (frees shapes)
    virtual void unknown_slot53();                              // slot 53 0x006A0B70 (loads shapes)
    virtual bool unknown_slot54(int control);                   // slot 54 0x006A0DA0 (the sidebar shown or hidden: updates the side buttons and help regions)

    // Frees button shape index when it was loaded (0x006A0540, __fastcall).
    static void __fastcall Unknown_006A0540(int index);
    // Index of a command name in CommandNames, else NoCommand (0x006A0580).
    static int __fastcall Unknown_006A0580(char const *name);
    // The slot-to-button map (0x006A05E0 set, 0x006A05F0 get).
    static void __fastcall Unknown_006A05E0(int slot, int button);
    static int __fastcall Unknown_006A05F0(int slot);
    // The button shown in slot, or null (0x006A0600).
    static ShapeButtonClass *__fastcall Unknown_006A0600(int slot);
    // Screen rectangle of slot (0x006A0620).
    static Rect __fastcall Unknown_006A0620(int slot);
    // Sets the bar's row count and its top edge (0x006A0670).
    static void __fastcall Unknown_006A0670(int rows);
    // Whether value lies in [unknown_int_abe370, unknown_int_abe468] (0x006A06B0).
    static int __fastcall Unknown_006A06B0(int value);
    // value relative to unknown_int_abe370, from 1 (0x006A06D0).
    static int __fastcall Unknown_006A06D0(int value);

    // Registers a control's help region under its ID with a label
    // (0x006A1270, __fastcall; nothing for no control).
    static void __fastcall Unknown_006A1270(ControlClass *control, char const *label);
    // Flags the bar for a redraw (0x006A1770): +0x4F15 set and the timer at
    // +0x4F08 restarted at 7 frames.
    void Unknown_006A1770();
    void Unknown_006A17B0();                // 0x006A17B0 (sets +0x4F15 and flags a redraw)
    // Draws the bar's background shape (0x00AC10F8) at the sidebar surface's
    // origin (0x006A1710).
    void Unknown_006A1710();
    // Sets up the two side buttons (ids 0xF0 and 0xF1); inlined into Init_IO, whose copy of the
    // code this is (0x006A19E0, no callers).
    static void Unknown_006A19E0();
    void Unknown_006A1AB0();                                    // 0x006A1AB0 (slot 54 when the bar is open and the sidebar shows)
    void Unknown_006A1880();                                    // 0x006A1880 (Init_IO, before the two side buttons)
    void Unknown_006A1DA0();                                    // 0x006A1DA0 removes the open bar's buttons and help regions
    void Unknown_006A1E20();                                    // 0x006A1E20 shows the closed bar's thumb button
    void Unknown_006A1EA0();                                    // 0x006A1EA0 hides the thumb button
    void Unknown_006A1EC0();                                    // 0x006A1EC0 opens the bar
    void Unknown_006A1F10();                                    // 0x006A1F10 closes the bar
    // Adds (0x006A0D50) or removes (0x006A0D80) the 25 buttons.
    void Unknown_006A0D50();
    void Unknown_006A0D80();

    static ShapeButtonClass Buttons[25];                // 0x00ABD918
    static ShapeButtonClass unknown_button_abe400;      // 0x00ABE400
    static ShapeButtonClass unknown_button_abe390;      // 0x00ABE390
    static void const *ButtonShapes[25];                // 0x00ABD8A0
    static bool ButtonShapeAllocated[25];               // 0x00ABE32C
    static int SlotButton[25];                          // 0x00ABE2C8

    // +0x4EE8 INoticeSink vptr
    UnknownTab4EEC unknown_4eec;                        // +0x4EEC
    CDTimerClass<FrameTimerClass> unknown_4efc;         // +0x4EFC
    CDTimerClass<FrameTimerClass> unknown_4f08;         // +0x4F08
    bool unknown_4f14;                                  // +0x4F14
    bool unknown_4f15;                                  // +0x4F15
    bool unknown_4f16;                                  // +0x4F16
};

// Makes the planning mode's notice sink the object (0x00613E00, __fastcall).
void __fastcall Unknown_Set_Sink_00613e00(INoticeSink *sink);

// Command names the buttons map to (0x007F67F8, 11 entries: "Team01" ..
// "Cheer") and the value returned for an unknown name (0x007F67F4, -1).
extern int unknown_no_command_7f67f4;
extern char const *unknown_command_names_7f67f8[11];

// Tab.cpp metrics.
extern int unknown_int_abe2a8;      // 0x00ABE2A8 the button shapes' height (slot 53)
extern int unknown_int_abe2ac;      // 0x00ABE2AC rows
extern int unknown_int_abe370;      // 0x00ABE370
extern int unknown_int_abe378;      // 0x00ABE378
extern int unknown_int_abe374;      // 0x00ABE374 slot top
extern int unknown_int_abe37c;      // 0x00ABE37C bar top
extern int unknown_int_abe388;      // 0x00ABE388 slot pitch
extern int unknown_int_abe460;      // 0x00ABE460 the slot width less the button width (slot 53)
extern int unknown_int_abe478;      // 0x00ABE478 the button shapes' width (slot 53)
extern int unknown_int_abe468;      // 0x00ABE468
// The shell art shape of the two side buttons (0x00AC1098) and whether the
// shell art is loaded (0x006F4590, __fastcall).
extern void *unknown_buffer_ac1098;
bool __fastcall Unknown_Get_Art_006f4590();
// The bar's background shape (0x00AC10F8; a shell art buffer, as the
// art loaders name it).
extern void *unknown_buffer_ac10f8;
// The bar's other shell art: the left cap (0x00AC1048), the tile of the open
// bar (0x00AC10A4, repeated 0x00AC0FF4 times) and the right cap (0x00AC10B0).
extern void *unknown_buffer_ac1048;
extern void *unknown_buffer_ac10a4;
extern void *unknown_buffer_ac10b0;
extern int unknown_int_ac0ff4;
// The button numbers of the bar's commands (0x00ABE464, 0x00ABE294,
// 0x00ABD910, 0x00ABE278, 0x00ABE2B8, 0x00ABE36C, 0x00ABE2BC, 0x00ABE290;
// TabClass::AI compares the pressed button with them).
extern int unknown_int_abe464;
extern int unknown_int_abe294;
extern int unknown_int_abd910;
extern int unknown_int_abe278;
extern int unknown_int_abe2b8;
extern int unknown_int_abe36c;
extern int unknown_int_abe2bc;
extern int unknown_int_abe290;
// The commands the buttons run (UICmnds.cpp; __fastcall where they take an
// argument; names in src/recovered/unowned where accepted).
void Unknown_006F6570();
void Unknown_006F64B0();
void Unknown_006F5C50();
void Unknown_006F5940();
void __fastcall Unknown_006F5B10();    // 0x006F5B10 guard command; __fastcall: its slot 200 call sets ecx before the pushes
void __fastcall Unknown_006F64D0(bool arg);
void __fastcall Unknown_006F64F0(bool arg);
void Unknown_006F5BC0();
int __fastcall Unknown_006F5870(int group);
void __fastcall Unknown_006F5D90(int group);
bool __fastcall Unknown_006F5800(int group);
void __fastcall Unknown_006F60D0(int group);
void __fastcall Unknown_006F5F00(int group);
void Unknown_006F7360();
void __fastcall Unknown_006F5E10(int group);
// Screen layout rectangles (0x00AC11FC, 0x00AC1204, 0x00AC120C, 0x00AC1210).
extern Rect const *unknown_rect_ac11fc;
extern Rect const *unknown_rect_ac1204;
extern Rect const *unknown_rect_ac1208;
extern Rect const *unknown_rect_ac120c;
extern Rect const *unknown_rect_ac1210;

#endif
