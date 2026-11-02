// LinkClass and GadgetClass: Westwood's doubly linked gadget list (RTTI
// vtables 0x007A18B4 LinkClass, 10 slots; 0x007A182C GadgetClass, 33 slots).
//
// Only the call interface the screen layer uses is declared here; slot
// names follow the TS/RA1 GadgetClass vocabulary where the calls in
// GScreen.cpp (0x004E09D0-0x004E0C50) match it, unknown_slotNN otherwise.
// LinkClass is defined in Link.cpp (0x00538670 unit): Westwood's link.cpp
// shape (Next at +4, Prev at +8).
#ifndef RA2_SHARED_GADGET_HPP
#define RA2_SHARED_GADGET_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/text_print.hpp"

class LinkClass {
public:
    LinkClass() : Next(0), Prev(0) {}
    LinkClass(LinkClass &link);                             // 0x00538F60 (joins link's list)
    virtual ~LinkClass();                                   // slot 0  (+0x00) 0x00538FA0
    LinkClass &operator=(LinkClass &link);                  // 0x00539000 (moves to link's list)
    virtual LinkClass *Get_Next() const;                    // slot 1  (+0x04) 0x00539020
    virtual LinkClass *Get_Prev() const;                    // slot 2  (+0x08) 0x00539030
    virtual LinkClass &Add(LinkClass &object);              // slot 3  (+0x0C) 0x005390A0
    virtual LinkClass &Add_Tail(LinkClass &object);         // slot 4  (+0x10) 0x005390E0 GScreenClass::Add_A_Button
    virtual LinkClass &Add_Head(LinkClass &object);         // slot 5  (+0x14) 0x005390C0
    virtual LinkClass &Head_Of_List();                      // slot 6  (+0x18) 0x00539040 GScreenClass::Is_Button_List
    virtual LinkClass &Tail_Of_List();                      // slot 7  (+0x1C) 0x00539070
    virtual void Zap();                                     // slot 8  (+0x20) 0x00538FF0
    virtual LinkClass *Remove();                            // slot 9  (+0x24) 0x00539110 GScreenClass::Remove_A_Button

    LinkClass *Next;    // +0x04
    LinkClass *Prev;    // +0x08
};

// GadgetClass (Gadget.cpp, unit 0x004CEC20-0x004CF72D): Westwood's gadget
// base. Layout (constructor 0x004CEFE0, copy constructor 0x004CF030):
//   +0x0C  int X, +0x10 int Y, +0x14 int Width, +0x18 int Height
//   +0x1C  bool IsToRepaint
//   +0x1D  bool IsSticky
//   +0x1E  bool IsDisabled
//   +0x20  unsigned Flags        LEFTPRESS 1, LEFTHELD 2, LEFTRELEASE 4, ...,
//                                KEYBOARD 0x100
//   size 0x24
// Names follow Westwood's gadget.h; slots 28 and 29 (empty here, called by
// Input when the mouse enters and leaves a gadget) are RA2 additions.
// Key codes are 4-byte values here (ControlClass::Action stores whole words);
// shared/keyboard.hpp types the keyboard queue as unsigned short, so the
// gadget interface uses unsigned rather than that KeyNumType.

class ControlClass;

class GadgetClass : public LinkClass {
public:
    enum {
        LEFTPRESS = 0x01,
        LEFTHELD = 0x02,
        LEFTRELEASE = 0x04,
        KEYBOARD = 0x100
    };

    GadgetClass(int x, int y, int w, int h, unsigned flags, bool sticky = false);   // 0x004CEFE0
    GadgetClass &operator=(GadgetClass const &gadget); // 004a5730, copy ABI hypothesis
    GadgetClass(GadgetClass const &gadget);                         // 0x004CF030
    virtual ~GadgetClass();                                         // 0x004CF080

    virtual LinkClass *Get_Next() const;                            // slot 1  0x004CF190
    virtual LinkClass *Get_Prev() const;                            // slot 2  0x004CF1A0
    virtual LinkClass *Remove();                                    // slot 9  0x004CF170
    virtual int Input();                                            // slot 10 (+0x28) 0x004CF330
    virtual void Draw_All(bool forced = true);                      // slot 11 (+0x2C) 0x004CF260
    virtual void Delete_List();                                     // slot 12 0x004CF1B0
    virtual ControlClass *Extract_Gadget(unsigned id);              // slot 13 0x004CF560
    virtual void Flag_List_To_Redraw() { LastList = 0; }            // slot 14 (kept copy 0x0047D6F0)
    virtual void Disable();                                         // slot 15 0x004CF150
    virtual void Enable();                                          // slot 16 0x004CF140
    virtual unsigned Get_ID() const { return 0; }                   // slot 17 (kept copy 0x0049ECD0)
    virtual void Flag_To_Redraw();                                  // slot 18 0x004CF5A0
    virtual void Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom) {}  // slot 19 (kept copy 0x00483560)
    virtual void Set_Focus();                                       // slot 20 0x004CF5E0
    virtual void Clear_Focus();                                     // slot 21 0x004CF610
    virtual bool Has_Focus();                                       // slot 22 0x004CF630
    virtual int Is_List_To_Redraw();                                // slot 23 (+0x5C) 0x004CF640 GScreenClass::Get_Input
    virtual bool Is_To_Redraw() { return IsToRepaint; }             // slot 24 (kept copy 0x0047D700)
    virtual void Set_Position(int x, int y);                        // slot 25 0x004CF660
    virtual void Set_Size(int w, int h);                            // slot 26 0x004CF680
    virtual int Draw_Me(int forced = false);                        // slot 27 0x004CF240
    virtual void Mouse_Enter();                                     // slot 28 0x004CF200 (name hypothesis)
    virtual void Mouse_Leave();                                     // slot 29 0x004CF210 (name hypothesis)
    virtual void Sticky_Process(unsigned flags);                    // slot 30 0x004CF5B0
    virtual int Action(unsigned flags, unsigned &key);            // slot 31 0x004CF220
    virtual int Clicked_On(unsigned &key, unsigned flags, int x, int y);   // slot 32 0x004CF0E0

#ifdef RA2_GADGET_SET_FLAGS
    // Westwood GadgetClass flag setter (TibSun gadget.h); layout is unchanged.
    void Set_Flags(unsigned flags) { Flags = flags; }
#endif
    bool Is_Enabled();                                              // 0x004CF160 !IsDisabled (Sidebar copy; name hypothesis)
    GadgetClass *Extract_At(int x, int y);                          // 0x004CF290 (smallest enabled gadget at x, y; name hypothesis; near miss)

    int X;                  // +0x0C
    int Y;                  // +0x10
    int Width;              // +0x14
    int Height;             // +0x18
    bool IsToRepaint;       // +0x1C
    bool IsSticky;          // +0x1D
    bool IsDisabled;        // +0x1E
    unsigned Flags;         // +0x20

    static GadgetClass *StuckOn;        // 0x00865FF0
    static GadgetClass *LastList;       // 0x00865FF4
    static GadgetClass *Focused;        // 0x00865FF8
    static GadgetClass *MouseOver;      // 0x00865FFC (name hypothesis)
};

// ControlClass (Control.cpp, unit 0x004831A0): a gadget with an ID that
// reports itself as a button key and can drive a peer gadget.
//   +0x24  unsigned ID
//   +0x28  GadgetClass *Peer
//   size 0x2C
class ControlClass : public GadgetClass {
public:
    enum { KN_BUTTON = 0x8000 };

    ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags = 0, bool sticky = false);   // 0x00483430
    ControlClass(ControlClass const &control);                      // 0x00483480

    virtual void Make_Peer(GadgetClass &gadget);                    // slot 33 0x00483510
    virtual unsigned Get_ID() const;                                // slot 17 0x00483520
    virtual int Draw_Me(int forced = false);                        // slot 27 0x00483530
    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x004834B0

    unsigned ID;            // +0x24
    GadgetClass *Peer;      // +0x28
};

// ToggleClass (unit 0x006EAD70): a sticky button that tracks whether the
// mouse is pressed on it and whether it is switched on.
//   +0x2C  bool IsPressed
//   +0x2D  bool IsOn
//   +0x30  int ToggleType        0
//   size 0x34
class ToggleClass : public ControlClass {
public:
    ToggleClass(unsigned id, int x, int y, int w, int h);          // 0x006EB120

    void Turn_On();                                                 // 0x006EB160
    void Turn_Off();                                                // 0x006EB170

    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x006EB180

    bool IsPressed;         // +0x2C
    bool IsOn;              // +0x2D
    int ToggleType;         // +0x30
};

// CheckBoxClass (unit 0x0047D150, after Cell.CPP; TibSun checkbox.cpp): a toggle
// drawn as a sunken box, filled when on. Its vtable is not in the executable
// (no constructor is linked); the two members are unreferenced.
class CheckBoxClass : public ToggleClass {
public:
    virtual int Draw_Me(int forced = false);                        // 0x0047D150
    virtual int Action(unsigned flags, unsigned &key);              // 0x0047D270
};

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

// The text font, Font_For_Style (0x00497A50), Draw_Box (0x004973D0) and
// the text printers: shared/text_print.hpp.

// TextButtonClass (unit 0x006E7550 region, 0x006E7240-0x006E754D): a toggle
// button showing a string.
//   +0x34  bool IsBlackBorder
//   +0x35  bool IsBordered        (skips the background when set; hypothesis)
//   +0x38  wchar_t const *String
//   +0x3C  int PrintFlags         text style; 2 by default
//   size 0x40
class TextButtonClass : public ToggleClass {
public:
    TextButtonClass(unsigned id, wchar_t const *text, int style, int x, int y, int w = -1, int h = -1,
                    bool blackborder = false, bool bordered = false);   // 0x006E7240
    TextButtonClass();                                              // 0x006E72D0

    virtual int Draw_Me(int forced = false);                        // slot 27 0x006E7300
    virtual void Set_Text(wchar_t const *text, bool resize = false);   // slot 34 0x006E7340
    virtual void Set_Style(int style);                              // slot 35 0x006E7520
    virtual void Draw_Background();                                 // slot 36 0x006E7390
    virtual void Draw_Text(wchar_t const *text);                    // slot 37 0x006E7460

    bool IsBlackBorder;     // +0x34
    bool IsBordered;        // +0x35
    wchar_t const *String;  // +0x38
    int PrintFlags;         // +0x3C
};

// ShapeButtonClass (unit 0x00675000-0x006753FF): a toggle button drawn from
// a shape file (frames by state).
//   +0x34  bool unknown_34        +0x38 int unknown_38     +0x3C int unknown_3c
//   +0x40  bool unknown_40        (selects the on/off frames in Draw_Me)
//   +0x44  int OffsetX            +0x48 int OffsetY        (drawing offset)
//   +0x4C  bool unknown_4c
//   +0x50  void *unknown_50       the global at 0x008323C4 (drawer; hypothesis)
//   +0x54  bool unknown_54        set by Draw_Me
//   +0x55  bool unknown_55        constructor argument (draw flag 0x800)
//   +0x58  void const *Shape      shape file; its header gives the size
//   +0x5C  bool IsShapeAllocated  the button owns (and frees) the shape
extern ConvertClass *unknown_drawer_8323c4;     // 0x008323C4 (the GUI palette converter)

class ShapeButtonClass : public ToggleClass {
public:
    ShapeButtonClass();                                             // 0x00675020
    ShapeButtonClass(unsigned id, void const *shape, int x, int y, int w = 0, int h = 0,
                     bool flag = false);                            // 0x00675060
    virtual ~ShapeButtonClass();                                    // 0x006750F0

    virtual int Draw_Me(int forced = false);                        // slot 27 0x006751E0
    virtual void Set_Shape(void const *shape, int w = 0, int h = 0);   // slot 34 0x00675130
    bool Unknown_006752D0(int start, int length, bool flag);        // 0x006752D0 starts the +0x38/+0x3C span (Sidebar)
    bool Unknown_00675300();                                        // 0x00675300 clears it (Sidebar)
    bool Unknown_00675320();                                        // 0x00675320 advances it; true when it needs a redraw (Sidebar)
    bool Unknown_00675360() const;                                  // 0x00675360 whether the span runs (+0x38 set)
    bool Unknown_00675370() const;                                  // 0x00675370 returns +0x34
    void Free_Shape();                                              // 0x006751A0 frees an allocated shape (Sidebar slot 50; name hypothesis)
    void Set_Allocated(bool allocated);                             // 0x006751D0 sets IsShapeAllocated (Sidebar slot 53)

    bool unknown_34;            // +0x34
    int unknown_38;             // +0x38
    int unknown_3c;             // +0x3C
    bool unknown_40;            // +0x40
    int OffsetX;                // +0x44
    int OffsetY;                // +0x48
    bool unknown_4c;            // +0x4C
    void *unknown_50;           // +0x50
    bool unknown_54;            // +0x54
    bool unknown_55;            // +0x55
    void const *Shape;          // +0x58
    bool IsShapeAllocated;      // +0x5C
};

extern "C" unsigned int __cdecl wcslen(unsigned short const *string);   // 0x00783605 (as msfont.hpp)
// The colour scheme of the gadgets (non-member in Gadget.cpp, 0x004CEFC0;
// name hypothesis).
int __cdecl Gadget_Color_Scheme();      // 0x004CEFC0

// EditClass (unit 0x004B2950-0x004B2F45): a single-line text entry field.
//   +0x2C  unsigned TextFlags     the style without KEYBOARD (0x100)
//   +0x30  int EditFlags
//   +0x34  wchar_t *String
//   +0x38  int MaxLength          capacity - 1
//   +0x3C  int Length
//   +0x40  int Color              Gadget_Color_Scheme() when constructed
//   +0x44  int IsReadOnly         0; Action ignores input when set
//   size 0x48
class EditClass : public ControlClass {
public:
    EditClass(unsigned id, wchar_t *text, int max_len, unsigned flags, int x, int y,
              int w = -1, int h = -1, int editflags = 0);           // 0x004B2970
    virtual ~EditClass();                                           // 0x004B2A60

    virtual void Set_Focus();                                       // slot 20 0x004B2F20
    virtual int Draw_Me(int forced = false);                        // slot 27 0x004B2AC0
    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x004B2B40
    virtual void Set_Text(wchar_t *text, int max_len);              // slot 34 0x004B2A90
    virtual wchar_t *Get_Text() { return String; }                  // slot 35 (kept copy 0x004A5550)
    virtual void Draw_Background();                                 // slot 36 0x004B2C50
    virtual void Draw_Text(wchar_t const *text);                    // slot 37 0x004B2C90
    virtual bool Handle_Key(int ascii);                             // slot 38 0x004B2DD0

    unsigned TextFlags;     // +0x2C
    int EditFlags;          // +0x30
    wchar_t *String;        // +0x34
    int MaxLength;          // +0x38
    int Length;             // +0x3C
    int Color;              // +0x40
    int IsReadOnly;         // +0x44
};

// GaugeClass and TriColorGaugeClass (Gauge.cpp, unit 0x004CF730-0x004D0CEE).
// GaugeClass layout (constructor 0x004D00F0):
//   +0x2C  bool IsColorized      true
//   +0x2D  bool HasThumb         true
//   +0x2E  bool IsHorizontal     width > height
//   +0x30  int MaxValue          255
//   +0x34  int CurValue          0
//   +0x38  int ClickDiff         0
//   size 0x3C
// TriColorGaugeClass adds +0x3C RedLimit and +0x40 YellowLimit (size 0x44).
class GaugeClass : public ControlClass {
public:
    GaugeClass(unsigned id, int x, int y, int w, int h);           // 0x004D00F0

    virtual int Draw_Me(int forced = false);                        // slot 27 0x004D0280
    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x004D0420
    virtual int Set_Maximum(int value);                             // slot 34 0x004D0170
    virtual int Set_Value(int value);                               // slot 35 0x004D0190
    virtual int Get_Value() const { return CurValue; }              // slot 36 0x004D0C80 (inline)
    virtual void Use_Thumb(int value) { HasThumb = value ? true : false; }   // slot 37 0x004D0C90 (inline)
    virtual int Thumb_Pixels() { return 4; }                        // slot 38 0x004D0CA0 (inline)
    virtual void Draw_Thumb();                                      // slot 39 0x004D0580
    virtual int Pixel_To_Value(int pixel);                          // slot 40 0x004D01C0
    virtual int Value_To_Pixel(int value);                          // slot 41 0x004D0240

    bool IsColorized;       // +0x2C
    bool HasThumb;          // +0x2D
    bool IsHorizontal;      // +0x2E
    int MaxValue;           // +0x30
    int CurValue;           // +0x34
    int ClickDiff;          // +0x38
};

class TriColorGaugeClass : public GaugeClass {
public:
    TriColorGaugeClass(unsigned id, int x, int y, int w, int h);   // 0x004D0630

    virtual int Draw_Me(int forced = false);                        // slot 27 0x004D0730
    virtual int Set_Red_Limit(int value);                           // slot 42 0x004D06D0
    virtual int Set_Yellow_Limit(int value);                        // slot 43 0x004D0700

    int RedLimit;           // +0x3C
    int YellowLimit;        // +0x40
};

// SliderClass (unit 0x006846C0-0x00684D4F): a gauge with a thumb and,
// unless built without them, plus/minus shape buttons.
//   +0x3C  ShapeButtonClass *PlusGadget
//   +0x40  ShapeButtonClass *MinusGadget
//   +0x44  bool NoButtons         (hypothesis: the constructor's last argument)
//   +0x48  int Thumb              thumb length in values
//   +0x4C  int ThumbSize          pixels (at least 4)
//   +0x50  int ThumbStart         pixels from the start
//   size 0x54
class Rect;

class SliderClass : public GaugeClass {
public:
    SliderClass(unsigned id, int x, int y, int w, int h, int no_buttons = false);   // 0x006846E0
    virtual ~SliderClass();                                         // 0x006848C0

    virtual void Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom);   // slot 19 0x00684D10
    virtual int Draw_Me(int forced = false);                        // slot 27 0x00684CA0
    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x00684B10
    virtual int Set_Maximum(int value);                             // slot 34 0x00684900
    virtual int Set_Value(int value);                               // slot 35 0x00684A10
    virtual int Thumb_Pixels() { return ThumbSize; }                // slot 38 (kept copy 0x0053AAE0)
    virtual void Draw_Thumb();                                      // slot 39 0x00684C20
    virtual void Set_Thumb_Size(int value);                         // slot 42 0x00684980
    virtual int Bump(int up);                                       // slot 43 0x00684BB0
    virtual int Step(int up);                                       // slot 44 0x00684BF0

    void Recalc_Thumb();                                            // 0x00684AA0

    ShapeButtonClass *PlusGadget;   // +0x3C
    ShapeButtonClass *MinusGadget;  // +0x40
    bool NoButtons;                 // +0x44
    int Thumb;                      // +0x48
    int ThumbSize;                  // +0x4C
    int ThumbStart;                 // +0x50
};

// ListClass (List.cpp, unit 0x00539BD0-0x0053AEEF): a text list with up and
// down buttons and a scroll bar that appears when the items do not fit.
//   +0x2C  unsigned TextFlags
//   +0x30  int const *Tabs
//   +0x34  DynamicVectorClass<wchar_t *> List
//   +0x4C  int LineHeight
//   +0x50  int LineCount
//   +0x54  bool IsScrollActive
//   +0x58  ShapeButtonClass UpGadget
//   +0xB8  ShapeButtonClass DownGadget
//   +0x118 SliderClass ScrollGadget
//   +0x16C int SelectedIndex
//   +0x170 int CurrentTopIndex
//   size 0x174; 51 virtual slots (the RTTI scan lists 37)
class ListClass : public ControlClass {
public:
    ListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down);   // 0x00539BF0
    ListClass(ListClass const &list);                               // 0x00539D40
    virtual ~ListClass();                                           // 0x00539FC0

    virtual LinkClass &Add(LinkClass &object);                      // slot 3  0x0053A7D0
    virtual LinkClass &Add_Tail(LinkClass &object);                 // slot 4  0x0053A870
    virtual LinkClass &Add_Head(LinkClass &object);                 // slot 5  0x0053A820
    virtual LinkClass *Remove();                                    // slot 9  0x0053A8C0
    virtual void Flag_To_Redraw();                                  // slot 18 0x0053A990
    virtual void Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom);   // slot 19 0x0053A4D0
    virtual void Set_Position(int x, int y);                        // slot 25 0x00539F30
    virtual int Draw_Me(int forced = false);                        // slot 27 0x0053A2E0
    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x0053A1F0
    virtual int Add_Item(wchar_t *text);                            // slot 34 0x0053A060
    virtual int Add_Scroll_Bar();                                   // slot 35 0x0053A5A0
    virtual void Bump(int up);                                      // slot 36 0x0053A3E0
    virtual int Count() const { return List.Count(); }              // slot 37 (kept copy 0x0047D710)
    virtual int Current_Index() const;                              // slot 38 0x0053A4C0
    virtual wchar_t *Current_Item() const;                          // slot 39 0x0053A4A0
    virtual wchar_t *Get_Item(int index) const;                     // slot 40 0x0053A480
    virtual int Step_Selected_Index(int forward);                   // slot 41 0x0053A970
    virtual void Remove_Item(wchar_t *text);                        // slot 43 0x0053A1C0 (overloads: last slot first)
    virtual void Remove_Item(int index);                            // slot 42 0x0053A0F0
    virtual int Remove_Scroll_Bar();                                // slot 44 0x0053A670
    virtual void Set_Selected_Index(int index);                     // slot 46 0x0053A900
    virtual void Set_Selected_Index(wchar_t *text);                 // slot 45 0x0053A9D0
    virtual void Set_Tabs(int const *tabs);                         // slot 47 0x0053A6D0
    virtual int Set_View_Index(int index);                          // slot 48 0x0053A530
    virtual void Step(int up);                                      // slot 49 0x0053A430
    virtual void Draw_Entry(int index, int x, int y, int width, int selected);   // slot 50 0x0053A6E0

    unsigned TextFlags;                     // +0x2C
    int const *Tabs;                        // +0x30
    DynamicVectorClass<wchar_t *> List;     // +0x34
    int LineHeight;                         // +0x4C
    int LineCount;                          // +0x50
    bool IsScrollActive;                    // +0x54
    ShapeButtonClass UpGadget;              // +0x58
    ShapeButtonClass DownGadget;            // +0xB8
    SliderClass ScrollGadget;               // +0x118
    int SelectedIndex;                      // +0x16C
    int CurrentTopIndex;                    // +0x170
};

extern "C" int __cdecl _wcsicmp(unsigned short const *left, unsigned short const *right);   // 0x00796318
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);   // 0x00783622
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);   // 0x00783689

// DropListClass (DropList.cpp, unit 0x004A4DA0-0x004A584B): an edit field
// with a button that drops a list of choices below it.
//   +0x48  bool IsDropped
//   +0x4C  int ListHeight
//   +0x50  ShapeButtonClass DropButton
//   +0xB0  ListClass List
//   size 0x224
class DropListClass : public EditClass {
public:
    DropListClass(int id, wchar_t *text, int max_len, unsigned flags, int x, int y, int w, int h,
                  void const *up, void const *down);                // 0x004A4DC0
    DropListClass(DropListClass const &list); // 0x004A5390; original const spelling hypothesis
    virtual ~DropListClass() {}                                     // (inlined into 0x004A55A0)

    DropListClass &operator=(DropListClass &list);                  // 0x004A51C0 (near miss)
    void Expand();                                                  // 0x004A5140
    void Collapse();                                                // 0x004A51A0

    virtual LinkClass &Add(LinkClass &object);                      // slot 3  0x004A4ED0
    virtual LinkClass &Add_Tail(LinkClass &object);                 // slot 4  0x004A4EF0
    virtual LinkClass &Add_Head(LinkClass &object);                 // slot 5  0x004A4F10
    virtual void Zap();                                             // slot 8  0x004A4E90
    virtual LinkClass *Remove();                                    // slot 9  0x004A4F30
    virtual void Peer_To_Peer(unsigned flags, unsigned &key, ControlClass &whom);   // slot 19 0x004A5070
    virtual void Clear_Focus();                                     // slot 21 0x004A5050
    virtual void Set_Position(int x, int y);                        // slot 25 0x004A5490
    virtual int Add_Item(wchar_t *text);                            // slot 39 0x004A4F60
    virtual wchar_t *Current_Item();                                // slot 40 0x004A4FA0
    virtual int Current_Index();                                    // slot 41 0x004A4FC0
    virtual void Set_Selected_Index(int index);                     // slot 43 0x004A4FE0 (overloads: last slot first)
    virtual void Set_Selected_Index(wchar_t *text);                 // slot 42 0x004A54E0
    virtual int Count() { return List.Count(); }                    // slot 44 0x004A5560 (inline)
    virtual wchar_t *Get_Item(int index) { return List.Get_Item(index); }   // slot 45 0x004A5580 (inline)

    bool IsDropped;                 // +0x48
    int ListHeight;                 // +0x4C
    ShapeButtonClass DropButton;    // +0x50
    ListClass List;                 // +0xB0
};

// StaticButtonClass (unit 0x00698740-0x00698ADB; RTTI vtable 0x007AC0D0,
// 36 slots, bases GadgetClass and LinkClass): a gadget showing a text in a
// style, saving the screen under itself so it can be redrawn over.
//   +0x24  Buffer Background      the saved screen area (allocated on the
//                                 first Draw_Background)
//   +0x30  wchar_t *Text          owned copy (operator new / delete)
//   +0x34  int Style              text print flags (0x100 centre, 0x200
//                                 right); 2 by default
//   size 0x38
// Names follow TS's StaticButtonClass; slot names are hypotheses.
#include "shared/buffer.hpp"

class StaticButtonClass : public GadgetClass {
public:
    StaticButtonClass(unsigned id, wchar_t const *text, int style, int x, int y,
                      int w = -1, int h = -1);                      // 0x00698760 (id unused)
    StaticButtonClass();                                            // 0x006987F0
    virtual ~StaticButtonClass();                                   // 0x00698830

    virtual int Draw_Me(int forced = false);                        // slot 27 0x00698860
    virtual void Set_Text(wchar_t const *text, bool resize = false);   // slot 33 0x006988A0
    virtual void Draw_Background();                                 // slot 34 0x00698960
    virtual void Draw_Text(wchar_t const *text);                    // slot 35 0x00698A10

    Buffer Background;      // +0x24
    wchar_t *Text;          // +0x30
    int Style;              // +0x34
};

#endif
