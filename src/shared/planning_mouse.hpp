// Planning mode's mouse hooks (planning.cpp): the screen layers call them
// before their own mouse handling, so they live apart from planning.hpp's
// class declarations (which need the full techno and house headers).
#ifndef RA2_SHARED_PLANNING_MOUSE_HPP
#define RA2_SHARED_PLANNING_MOUSE_HPP

// The left button went down / came up, the mouse moved, at a tactical point;
// true when planning mode took the event (0x00617340, 0x00617680, 0x00617900).
bool __stdcall Planning_Left_Down_00617340(int x, int y);
bool __stdcall Planning_Left_Up_00617680(int x, int y);
// The mouse button went down / came up at a screen point (0x00617860, 0x006178A0).
void __stdcall Planning_Mouse_Down(int x, int y);
void __stdcall Planning_Mouse_Up(int x, int y);
bool __stdcall Planning_Mouse_Move_00617900(int x, int y);

#endif
