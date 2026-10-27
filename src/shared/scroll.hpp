// ScrollClass: the scrolling layer of the screen chain (Scroll.cpp, from the
// header statics at 0x006693A0; RTTI vtable 0x007A9444, 55 slots, with the
// TabClass INoticeSink at +0x4EE8 re-pointed to 0x007A943C), derived from
// TabClass.
//
// Layout from the constructor 0x006695E0 (+0x4F18..+0x4F2A). Names are
// hypotheses or unknown_.
#ifndef RA2_SHARED_SCROLL_HPP
#define RA2_SHARED_SCROLL_HPP
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/tab.hpp"

class ScrollClass : public TabClass {
public:
    ScrollClass();                                              // 0x006695E0
    // Restore-in-place form, inline (MouseClass's load constructor reaches TabClass's, 0x0059FF60).
    ScrollClass(NoInitClass const &noinit) : TabClass(noinit) {}

    // Inline; the copy the linker kept is 0x0040D140.
    virtual void Init_IO() { TabClass::Init_IO(); }             // slot 8
    virtual void AI(int &input, Point2D const &xy);             // slot 10 0x00669630
    virtual bool unknown_slot26();                              // slot 26 0x0066A3C0
    virtual void unknown_slot35();                              // slot 35 0x0066AC20 (aborts a drag select)
    virtual void unknown_slot44(Point2D const &point);          // slot 44 0x0066ABE0
    virtual void unknown_slot49(int unknown);                   // slot 49 0x0066ABA0

    // Scrolls by the mouse and keyboard (0x0066A290, called first by AI).
    void Unknown_0066A290();

    // Scroll rate timer (0x00AB7048; TS ScrollClass::Counter).
    static CDTimerClass<SystemTimerClass> Counter;

    int unknown_4f18;                                           // +0x4F18
    bool unknown_4f1c;                                          // +0x4F1C
    Point2D unknown_4f20;                                       // +0x4F20 the last point (slot 44)
    bool unknown_4f28;                                          // +0x4F28
    bool unknown_4f29;                                          // +0x4F29 true at construction
    bool unknown_4f2a;                                          // +0x4F2A drag-select in progress
};

// user32 mouse capture (not yet in shared/win32_api.hpp).
WIN32_IMPORT HWND WINAPI GetCapture();
WIN32_IMPORT BOOL WINAPI ReleaseCapture();

// Unidentified flag tested by the scroll slots (0x00A40D44).
extern bool unknown_flag_a40d44;
// Mouse shape size flag passed to Set_Default_Mouse (0x0083740C).
extern bool unknown_flag_83740c;

#endif
