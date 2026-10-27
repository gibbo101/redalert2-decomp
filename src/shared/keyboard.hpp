// WWKeyboardClass: the keyboard and mouse-button input queue (Westwood's
// keyboard.cpp; the object behind the pointer at 0x00832468).
//
// Name and method vocabulary from Westwood's published WWKeyboardClass
// (Check, Get, Put, Put_Key_Message, Put_Mouse_Message, To_ASCII, Down,
// Clear, Message_Handler, Buff_Get, Fetch/Peek/Put_Element, Is_Buffer_Full/
// Empty, Fill_Buffer_From_System); verified against behaviour only.
//
// Layout from the constructor 0x00532130: a 256-entry ring of 16-bit key
// codes (Buffer, Head, Tail; indices wrap with signed % 256). A mouse-button
// key (low byte VK_LBUTTON/VK_RBUTTON/VK_MBUTTON) is followed in the ring by
// its x and y; key 0x0A by a character. RA2 adds the fields at +0x08..+0x10
// to the earlier Westwood layout.
#ifndef RA2_SHARED_KEYBOARD_HPP
#define RA2_SHARED_KEYBOARD_HPP

#include "shared/rect.hpp"
#include "shared/crt_memory.hpp"
#include "shared/win32_api.hpp"

typedef unsigned short KeyNumType;

class WWKeyboardClass {
public:
    WWKeyboardClass();                                  // 0x00532130

    KeyNumType Check();                                 // 0x005322D0 next key without removing it (0: none)
    KeyNumType Get();                                   // 0x00532320 waits for and removes the next key
    bool Put(KeyNumType key);                           // 0x00532490
    // Queues a key with the shift/control/alt bits (0x100/0x200/0x400) and
    // the release bit (0x800); ignored while unknown_flag_a40d44 is set
    // except for VK_ESCAPE; alt+tab is dropped.
    bool Put_Key_Message(KeyNumType key, bool release = false);                 // 0x005324D0
    // Queues a mouse key followed by its position (needs three free slots).
    bool Put_Mouse_Message(KeyNumType key, int x, int y, bool release = false);  // 0x005325C0
    // Queues the 0x0A marker followed by a character (no callers).
    bool Put_Char(KeyNumType character);                      // 0x005326A0 (name hypothesis)
    // The character of a key through ToAscii with the key's shift state.
    char To_ASCII(KeyNumType key);                      // 0x00532720
    // The character of a queued key without ToAscii (name hypothesis).
    char To_Char(KeyNumType key);                       // 0x00532800
    // Whether the key is held now (mouse buttons follow SM_SWAPBUTTON).
    bool Down(KeyNumType key);                          // 0x00532890 (callers test al: GadgetClass::Input)
    void Clear();                                       // 0x005329F0
    // Queues the keyboard and mouse-button window messages (mouse positions
    // in game coordinates) and passes them on to DefWindowProcA; 0 for the
    // messages it does not handle.
    int Message_Handler(HWND window, UINT message, WPARAM wparam, LPARAM lparam);  // 0x00532A60
    // Free slots.
    int Available();                                    // 0x00532E60

    int MouseQX;                    // +0x000 position queued with the last mouse key
    int MouseQY;                    // +0x004
    unsigned short unknown_08;      // +0x008 character queued after a 0x0A key
    Point2D unknown_0C;             // +0x00C copy of MouseQX/MouseQY
    unsigned char KeyState[256];    // +0x014 key state array passed to ToAscii

private:
    KeyNumType Buff_Get();                              // 0x00532160
    static int __fastcall Is_Mouse_Key(KeyNumType key); // 0x00532290
    static int __fastcall Is_Char_Key(KeyNumType key);  // 0x005322C0 (name hypothesis)
    KeyNumType Fetch_Element();                         // 0x005328E0
    KeyNumType Peek_Element();                          // 0x00532920
    bool Put_Element(KeyNumType key);                   // 0x00532940
    bool Is_Buffer_Full();                              // 0x00532980
    bool Is_Buffer_Empty();                             // 0x005329A0
    void Fill_Buffer_From_System();                     // 0x005329C0

    unsigned short Buffer[256];     // +0x114
    int Head;                       // +0x314 next key to read
    int Tail;                       // +0x318 next free slot
};

extern WWKeyboardClass *WWKeyboard;    // 0x00832468

// Set while the keyboard is ignored (hypothesis; set elsewhere).
extern bool unknown_flag_a40d44;       // 0x00A40D44
// Whether WM_CHAR characters are queued (hypothesis; set elsewhere).
extern bool unknown_flag_a3dc89;       // 0x00A3DC89

// Key-state wrappers that replay recorded input (hypotheses): records a key
// as down or up; GetKeyState and GetAsyncKeyState or the recorded state.
void __fastcall Unknown_005233A0(int key, bool release);   // 0x005233A0
short __fastcall Unknown_005233D0(int key);                 // 0x005233D0
short __fastcall Unknown_005233F0(int key);                 // 0x005233F0

// Pumps the window messages that fill the queue (hypothesis; it reads the
// main window handle 0x00B263D8).
void Unknown_005B5EE0();               // 0x005B5EE0

// The modifier keys the action code tests (two bindings each; runtime-set
// .bss words; declared as 32-bit ints: the callers push them as dwords,
// while WWKeyboardClass keeps 16-bit KeyNumType keys). Names from behaviour: in TechnoClass slot 27 (0x006CCCE0) the
// 0x00A40BAC/0x00A40BB0 pair is the only way to an attack action (5) on a
// plain cell, and the 0x00A40BB4/0x00A40BB8 pair returns a move (1);
// InfantryClass slot 28 (0x00505390) refuses to enter buildings while the
// first pair is down. The third pair's role is not settled (with force fire
// it yields actions 0x1A/0x33 in slot 27).
extern int KeyForceFire1;        // 0x00A40BAC
extern int KeyForceFire2;        // 0x00A40BB0
extern int KeyForceMove1;        // 0x00A40BB4
extern int KeyForceMove2;        // 0x00A40BB8
extern int unknown_key_a40ba4;   // 0x00A40BA4
extern int unknown_key_a40ba8;   // 0x00A40BA8

#endif
