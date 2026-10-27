// ColorListClass: a list gadget that draws each entry in its own colour
// (ColorList.cpp, unit 0x0047D7A0-0x0047DFC6; RTTI vtable 0x0079DC6C,
// derived from ListClass, build/class-work/Gadgets/shared/gadget.hpp; it
// adds slots 51 and 52).
//
// Layout (from the constructor 0x0047D7C0 and the destructor 0x0047D850):
//   +0x000  ListClass (0x174)
//   +0x174  DynamicVectorClass<int> Colors   one colour scheme per entry
//   +0x18C  int Style                        selection style (1)
//   +0x190  int SelectColor                  selection colour (0)
//   size 0x194
// Westwood names (COLRLIST.CPP: Colors, Style, SelectColor).
#ifndef RA2_SHARED_COLOR_LIST_HPP
#define RA2_SHARED_COLOR_LIST_HPP

#include "shared/gadget.hpp"

class ColorListClass : public ListClass {
public:
    ColorListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down);   // 0x0047D7C0
    virtual ~ColorListClass();                                      // 0x0047D850

    virtual int Add_Item(wchar_t *text) { return Add_Item(text, 0); }   // slot 34 0x0047DF40 (inline)
    virtual void Remove_Item(wchar_t *text);                        // slot 43 0x0047D910 (overloads: last slot first)
    virtual void Remove_Item(int index);                            // slot 42 0x0047D970
    virtual void Draw_Entry(int index, int x, int y, int width, int selected);   // slot 50 0x0047D9E0
    virtual int Add_Item(wchar_t *text, int color);                 // slot 51 0x0047D8B0
    virtual void Set_Selected_Style(int style, int color);          // slot 52 0x0047D9C0

    DynamicVectorClass<int> Colors;         // +0x174
    int Style;                              // +0x18C
    int SelectColor;                        // +0x190
};

#endif
