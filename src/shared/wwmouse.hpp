// Mouse and WWMouseClass: the software mouse cursor drawn over the game's
// surfaces (Westwood's wwmous.cpp, "D:\Ra2\wwmous.cpp", 0x007717A0-0x0077372E).
//
// Names from RTTI (vtables 0x007AFC38 Mouse, 0x007AFBEC WWMouseClass, 18
// slots). Slot meanings are evidenced by the implementations: the debug
// strings "Capture_Mouse()", "Release_Mouse()" and
// "Calc_Confining_Rect(%d,%d,%d,%d)", the ShowCursor loops of Show/Hide,
// the forwarding Conditional_* slots and the accessors. Layout from the
// constructor 0x00771A20 and the destructor 0x00771BC0.
//
// A worker thread (0x00771900) calls Process_Mouse every 16 ms; cursor state
// is guarded by a mutex (Block_Mouse/Unblock_Mouse, whose deadlock warning
// names line 1277 of the original file; they are defined last).
//
// Not evidenced (names are descriptive hypotheses): the non-virtual helpers
// (Has_Cursor .. Move_Cursor), the thread functions, the member names DrawX/
// DrawY (where the cursor is drawn) versus MouseX/MouseY (what the game
// reads), and every unknown_ global.
#ifndef RA2_SHARED_WWMOUSE_HPP
#define RA2_SHARED_WWMOUSE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/mouse.hpp"
#include "shared/shape_file.hpp"
#include "shared/surface.hpp"
#include "shared/win32_api.hpp"

// Mouse (the abstract interface) is declared in shared/mouse.hpp.

class WWMouseClass : public Mouse {
public:
    WWMouseClass(Surface *surface, HWND window);                                // 0x00771A20
    virtual ~WWMouseClass();                                                    // 0x00771BC0

    virtual void Set_Cursor(Point2D const &hotspot, ShapeFileStruct const *cursor, int frame);  // 0x00771CF0
    virtual bool Is_Hidden() const { return MouseState < 0; }                   // 0x00773690
    virtual void Hide_Mouse();                                                  // 0x00772CA0
    virtual void Show_Mouse();                                                  // 0x00772AC0
    virtual void Release_Mouse();                                               // 0x00772FA0
    virtual void Capture_Mouse();                                               // 0x00772DD0
    virtual bool Is_Captured() const { return IsCaptured; }                     // 0x007736A0
    virtual void Conditional_Hide_Mouse(Rect region);                           // 0x007730E0
    virtual void Conditional_Show_Mouse();                                      // 0x007730F0
    virtual int Get_Mouse_State() const;                                        // 0x00771CE0
    virtual int Get_Mouse_X() const { return MouseX; }                          // 0x007736B0
    virtual int Get_Mouse_Y() const { return MouseY; }                          // 0x007736C0
    virtual Point2D Get_Mouse_XY() const { return Point2D(MouseX, MouseY); }    // 0x007736D0
    virtual void Set_Mouse_XY(int x, int y) { MouseX = x; MouseY = y; }         // 0x007736F0
    virtual void Draw_Mouse(Surface *surface, bool issidebar = false);          // 0x00772410
    virtual void Erase_Mouse(Surface *surface, bool issidebar = false);         // 0x00772620
    virtual void Convert_Coordinate(int &x, int &y) const;                      // 0x00773100

    void Calc_Confining_Rect();                                                 // 0x00771C50
    bool Has_Cursor() const;                                                    // 0x00771F40
    bool Validate_Backgrounds();                                                // 0x00771F50
    Rect Get_Cursor_Rect();                                                     // 0x00772170
    void Save_Background();                                                     // 0x00772250
    void Restore_Background();                                                  // 0x00772390
    void Draw_Cursor(Surface *surface, int xoffset, int yoffset);               // 0x00772740
    void Low_Show_Mouse();                                                      // 0x007728A0
    void Low_Hide_Mouse();                                                      // 0x00772A00
    void Get_Cursor_Position(int &x, int &y);                                   // 0x00773160
    void Move_Cursor(int x, int y, bool force);                                 // 0x007731A0
    void Process_Mouse();                                                       // 0x00773400

protected:
    ShapeFileStruct const *MouseCursor;  // +0x04 cursor shape (null: no cursor)
    int MouseFrame;                      // +0x08 frame of MouseCursor
    int MouseState;                      // +0x0C 0 shown, negative hidden (nesting count)
    bool IsCaptured;                     // +0x10 drawn in software instead of the Windows cursor
    int DrawX;                           // +0x14 position the cursor is drawn at
    int DrawY;                           // +0x18
    int MouseX;                          // +0x1C position reported to the game
    int MouseY;                          // +0x20
    Surface *ScreenSurface;              // +0x24 surface the cursor is drawn on
    HWND Window;                         // +0x28
    Rect ConfiningRect;                  // +0x2C client area in screen coordinates
    int HotspotX;                        // +0x3C cursor hotspot within the shape (two ints:
    int HotspotY;                        // +0x40  a Point2D member reorders the constructor's stores)
    BSurface *Background;                // +0x44 saved pixels under the cursor on ScreenSurface
    Rect BackgroundRect;                 // +0x48 cursor rectangle relative to ConfiningRect
    BSurface *SurfaceBackground;         // +0x58 saved pixels for Draw_Mouse on another surface
    Rect SurfaceBackgroundRect;          // +0x5C
    BSurface *SidebarBackground;         // +0x6C same for the sidebar surface
    Rect SidebarBackgroundRect;          // +0x70
    Rect unknown_80;                     // +0x80 initialized empty, otherwise unused here
    int unknown_90;                      // +0x90 initialized to -1, otherwise unused here
    int unknown_94;                      // +0x94 initialized to 0, otherwise unused here
};

// Shared state of the mouse thread (0x00B2AF30; the thread's parameter).
// Volatile: the loops re-read it and the 64-bit delay is read in full.
struct MouseThreadInfoStruct {
    volatile int Quit;                   // +0x00 set to stop the thread
    volatile int Count;                  // +0x04 iterations run
    volatile int Done;                   // +0x08 set by the thread when it ends
    int unknown_0C;                      // +0x0C
    volatile __int64 Delay;              // +0x10 milliseconds between updates (16)
    volatile int Started;                // +0x18 set by the thread when it starts
};

extern MouseThreadInfoStruct MouseThreadInfo;   // 0x00B2AF30
extern HANDLE MouseThread;                      // 0x00B2AF4C
extern DWORD MouseThreadID;                     // 0x00B2AF50
extern bool unknown_flag_b2af58;                // 0x00B2AF58 lets Convert_Coordinate keep negative y
extern WWMouseClass *_Mouse;                    // 0x00B2AF5C the mouse the thread updates
extern HANDLE MouseMutex;                       // 0x00B2AF60
extern int MouseThreadActive;                   // 0x00B2AF64
extern bool unknown_flag_b2af68;                // 0x00B2AF68 position pending while the surface is unavailable

void Process_Mouse_Unthreaded();                // 0x007717C0
void Start_Mouse_Thread();                      // 0x007717E0
DWORD WINAPI Mouse_Thread(LPVOID parameter);    // 0x00771900
void __fastcall Kill_Mouse_Thread();            // 0x007719A0 (fastcall: Prog_End reaches it by a tail jump after restoring registers)
void Block_Mouse();                             // 0x00773630
void Unblock_Mouse();                           // 0x00773660

// Outside wwmous.cpp.
#include "shared/debug_printf.hpp"
// Returns the global 0x00A522AC; when nonzero the mouse keeps its position (0x00522E80).
int unknown_function_522e80();
// Draws source through convert onto dest at destpoint clipped to destclip (0x0049F3A0).
void __fastcall unknown_blit_49f3a0(Surface &dest, void *convert, Surface &source, Rect const &sourcerect,
                                    TPoint2D const &destpoint, Rect const &destclip, int unknown1, int unknown2,
                                    int unknown3, int unknown4, int unknown5, int unknown6);
extern void *unknown_convert_8323c8;            // drawer passed to unknown_blit_49f3a0; no cursor without it

#endif
