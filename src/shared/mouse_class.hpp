// MouseClass: the top of the screen chain (Mouse.cpp, from the header
// statics at 0x0059EDE0; RTTI vtable 0x0079A954, 55 slots, INoticeSink at
// +0x4EE8 re-pointed to 0x0079A94C), derived from ScrollClass. The game's
// map/screen object at 0x008324E0 is a MouseClass.
//
// Layout from the constructor 0x0059F020 and Init_Clear 0x0059F510; the
// mouse shape table at 0x007E2AF8 (24-byte entries). TS names where the
// behaviour matches (Set_Default_Mouse, Override_Mouse_Shape, ...).
#ifndef RA2_SHARED_MOUSE_CLASS_HPP
#define RA2_SHARED_MOUSE_CLASS_HPP
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/scroll.hpp"

// The shape file header (shared/shape_file.hpp's ShapeFileStruct prefix;
// that header is not included because its file-static empty rectangle
// would add a dynamic initializer Mouse.cpp does not have).
struct MouseShapeHeader {
    short unknown_00;       // +0x00
    short Width;            // +0x02
    short Height;           // +0x04
    short FrameCount;       // +0x06
};

// One mouse shape (0x007E2AF8 + 24 * mouse). Hotspot values 12345 and 54321
// mean the shape's centre and far edge.
struct MouseStruct {
    int StartFrame;         // +0x00
    int FrameCount;         // +0x04
    int FrameRate;          // +0x08
    int SmallFrame;         // +0x0C -1: no small form
    int X;                  // +0x10 hotspot
    int Y;                  // +0x14
};

class MouseClass : public ScrollClass {
public:
    MouseClass();                                               // 0x0059F020
    // Restore-in-place form, inline in MouseClass::unknown_slot30.
    MouseClass(NoInitClass const &noinit) : ScrollClass(noinit) {}

    virtual void One_Time();                                    // slot 5  0x0059F4F0
    virtual void Init_Clear();                                  // slot 7  0x0059F510
    virtual void AI(int &input, Point2D const &xy);             // slot 10 0x0059F390
    virtual void Set_Default_Mouse(int mouse, bool wsmall = false);      // slot 18 0x0059F060
    virtual bool Override_Mouse_Shape(int mouse, bool wsmall = false);   // slot 19 0x0059F250
    virtual void Revert_Mouse_Shape();                          // slot 20 0x0059F080
    virtual void Mouse_Small(bool wsmall);                      // slot 21 0x0059F090
    virtual HRESULT unknown_slot30(IStream *stream);                              // slot 30 0x0059F530 load
    virtual HRESULT unknown_slot31(IStream *stream);                              // slot 31 0x0059FC80 save
    virtual int unknown_slot40() { return NormalMouseShape; }   // slot 40 0x0040D150

    // First frame of mouse (its small form when asked and present; 0x0059F170).
    int Get_Mouse_Start_Frame(int mouse, bool wsmall) const;
    // Current frame of mouse (0x0059F1A0).
    int Get_Mouse_Frame(int mouse, bool wsmall) const;
    // Hotspot of mouse in the shape file (0x0059F1D0).
    Point2D Get_Mouse_Hotspot(int mouse) const;
    // Table accessors (0x0059FF20, 0x0059FF40; no direct callers).
    int Get_Mouse_Start(int mouse) const;
    int Get_Mouse_Count(int mouse) const;
    // Frees MouseShapes when it was loaded (0x0059FEF0).
    static void Unknown_0059FEF0();

    static MouseShapeHeader const *MouseShapes;                    // 0x00A70F64 "MOUSE.SHP"
    static bool MouseShapesAllocated;                           // 0x00A70FA4
    static CDTimerClass<SystemTimerClass> Timer;                // 0x00A70F70 animation timer

    bool IsSmall;                                               // +0x4F2C
    int CurrentMouseShape;                                      // +0x4F30
    int NormalMouseShape;                                       // +0x4F34
    int Frame;                                                  // +0x4F38 animation frame
};

extern MouseStruct unknown_mouse_control_7e2af8[];

// The theater-dependent reinitializers the load runs (0x00529870 with true,
// 0x0052B650, 0x0052B2E0 with two false arguments); owners unknown.
void __fastcall Unknown_00529870(int theater, bool arg);
void Unknown_0052B650();
void __fastcall Unknown_0052B2E0(bool arg1, bool arg2);

// ole32 stream persistence (as shared/locomotion.hpp declares them).
WIN32_IMPORT HRESULT __stdcall OleLoadFromStream(IStream *stream, GUID const &iid, void **object);
WIN32_IMPORT HRESULT __stdcall OleSaveToStream(IPersistStream *object, IStream *stream);

#endif
