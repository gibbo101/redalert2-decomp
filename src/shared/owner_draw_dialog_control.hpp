#ifndef RA2_OWNER_DRAW_DIALOG_CONTROL_HPP
#define RA2_OWNER_DRAW_DIALOG_CONTROL_HPP
#include "shared/win32_api.hpp"
// RTTI establishes this hierarchy; 0x6010c0 clears +4 and +8.
// The fields are placed in SimpleDialogControl as an ownership hypothesis;
// no base-field ownership claim is made from constructor omission alone.
// Slot1 stores the second argument at +4, then looks up the first as a registry key.
class Surface;
namespace OwnerDraw {
class DialogControl {
public:
    virtual ~DialogControl();
    virtual void Set_Window_006010f0(unsigned int key, HWND window) = 0;
    virtual bool unknown_slot2() = 0;
    virtual HWND Get_Window_00601180() = 0;
    virtual bool unknown_slot4() = 0;
};
class SimpleDialogControl : public DialogControl {
public:
    SimpleDialogControl();
    virtual void Set_Window_006010f0(unsigned int key, HWND window);
    virtual bool unknown_slot2();
    virtual HWND Get_Window_00601180();
    virtual bool unknown_slot4();
    HWND window; // +0x04
    bool unknown_08; // +0x08, read by slot2
};
// Descriptive recovery names for the integer-keyed OwnerDraw registry.
// Only the used prefix is declared; this is not a full global-size claim.
struct UnknownControlRecord {
    char unknown_00[0x6c];
    int unknown_6c;     // +0x6C the control's kind (0x005DF8E0 tests it against a list)
    char unknown_70[0xd4 - 0x70];
    bool unknown_d4;
    char unknown_d5[0x200 - 0xd5];
};
class UnknownControlIndex {
public:
    struct Node { unsigned int Key; UnknownControlRecord Value; Node *Next; };
    Node **Buckets; // +0x00
    unsigned int Count; // +0x04
    unsigned int unknown_08;
    unsigned int Bits; // +0x0c
    char unknown_10[8];
    unsigned int (__fastcall *Hash)(unsigned int const &key); // +0x18
    UnknownControlRecord *Find(unsigned int key) const {
        if (!Count) return 0;
        unsigned int hash = Hash(key);
        unsigned int bucket = (1u << Bits) - 1;
        bucket &= hash;
        Node *node = Buckets[bucket];
        while (node && node->Key != key) node = node->Next;
        return node ? &node->Value : 0;
    }
};
extern UnknownControlIndex unknown_registry_a73640;
// Whether the control is in the registry (0x005E4720; the skirmish preview paint skips one that is).
bool __fastcall unknown_5e4720(HWND control);
// Gives a registered control an image to draw (0x005E1F30; GDlgSupp.cpp ping and flag controls).
void __fastcall unknown_5e1f30(HWND control, Surface *image);

}
#endif
