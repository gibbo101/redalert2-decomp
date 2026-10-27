// CheckListClass: a list gadget whose entries carry a check mark
// (CheckList.cpp, unit 0x0047D2C0-0x0047D792; RTTI vtable 0x0079DB9C,
// derived from ListClass, build/class-work/Gadgets/shared/gadget.hpp).
//
// Layout (from the constructor 0x0047D2E0):
//   +0x000  ListClass (0x174)  its entries are CheckObject pointers
//   +0x174  bool IsReadOnly    Action ignores input while set
//   size 0x178
// Westwood names (CHECKLST.CPP); the CheckObject layout is from Add_Item
// 0x0047D370 (8 bytes: text, checked flag).
#ifndef RA2_SHARED_CHECK_LIST_HPP
#define RA2_SHARED_CHECK_LIST_HPP

#include "shared/gadget.hpp"

class CheckObject {
public:
    CheckObject(wchar_t *text = 0, bool checked = false) : Text(text), IsChecked(checked) {}

    wchar_t *Text;                          // +0x00
    bool IsChecked;                         // +0x04
};

class CheckListClass : public ListClass {
public:
    CheckListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down);   // 0x0047D2E0
    virtual ~CheckListClass();                                      // 0x0047D330

    virtual int Action(unsigned flags, unsigned &key);              // slot 31 0x0047D500
    virtual int Add_Item(wchar_t *text);                            // slot 34 0x0047D370
    virtual wchar_t *Current_Item() const;                          // slot 39 0x0047D3B0
    virtual wchar_t *Get_Item(int index) const;                     // slot 40 0x0047D3C0
    virtual void Remove_Item(wchar_t *text);                        // slot 43 0x0047D3E0 (overloads: last slot first)
    virtual void Remove_Item(int index) { ListClass::Remove_Item(index); }   // slot 42 0x0047D720 (inline)
    virtual void Set_Selected_Index(int index) { ListClass::Set_Selected_Index(index); }   // slot 46 0x0047D730 (inline)
    virtual void Set_Selected_Index(wchar_t *text);                 // slot 45 0x0047D450
    virtual void Draw_Entry(int index, int x, int y, int width, int selected);   // slot 50 0x0047D580

    void Check_Item(int index, bool checked);                       // 0x0047D4B0
    bool Is_Checked(int index) const;                               // 0x0047D4E0

    bool IsReadOnly;                        // +0x174
};

#endif
