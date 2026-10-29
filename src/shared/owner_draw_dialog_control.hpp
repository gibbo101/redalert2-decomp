#ifndef RA2_OWNER_DRAW_DIALOG_CONTROL_HPP
#define RA2_OWNER_DRAW_DIALOG_CONTROL_HPP
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"
#include "shared/rect.hpp"
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
    char unknown_00[0x10];
    Surface *surface_10; // +0x10 a BSurface (0x005FE490 creates it; 0x005FF380 deletes it)
    Surface *image_14;  // +0x14 image set by 0x005E1F30
    char unknown_18[0x68 - 0x18];
    int unknown_68;     // +0x68 nonzero skips the owner-draw tests (0x005E7230)
    int unknown_6c;     // +0x6C the control's kind (0x005DF8E0 tests it against a list)
    int unknown_70;     // +0x70 0x005E1F30 sets 2 with an image
    int unknown_74;
    char unknown_78[0xb0 - 0x78];
    int unknown_b0;     // +0xB0 set to 2 by 0x005EA230 for the listed dialog kinds
    char unknown_b4[0xbc - 0xb4];
    bool unknown_bc;
    bool unknown_bd;
    char unknown_be[2];
    int unknown_c0;
    int unknown_c4;
    int unknown_c8;     // +0xC8 0xC0 for edit, list and combo controls of the listed dialog kinds (0x005E1CA0, 0x005E8720)
    char unknown_cc[0xd4 - 0xcc];
    bool unknown_d4;
    bool unknown_d5;
    bool unknown_d6;
    bool unknown_d7;
    bool unknown_d8;
    char unknown_d9[0xdc - 0xd9];
    int unknown_dc;     // +0xDC 0x25 or 0xE by the dialog's kind and the control ID (0x005E8720)
    int unknown_e0;
    int unknown_e4;
    char unknown_e8[0x200 - 0xe8];
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
    // 0x00602020 when not inlined.
    unsigned int Bucket_Index(unsigned int const &key) const {
        unsigned int hash = Hash(key);
        unsigned int bucket = (1u << Bits) - 1;
        bucket &= hash;
        return bucket;
    }
    UnknownControlRecord *Find(unsigned int key) const {
        if (!Count) return 0;
        Node *node = Buckets[Bucket_Index(key)];
        while (node && node->Key != key) node = node->Next;
        return node ? &node->Value : 0;
    }
    // 0x00601710 when not inlined.
    bool Get(unsigned int const &key, UnknownControlRecord *&value) const {
        if (!Count) return false;
        Node *node = Buckets[Bucket_Index(key)];
        while (node && node->Key != key) node = node->Next;
        if (!node) return false;
        value = &node->Value;
        return true;
    }
};
extern UnknownControlIndex unknown_registry_a73640;
// The two-word key of the hash table at 0x00A73398 (compared by 0x005DE990 in 0x005EFCB0's removal).
struct UnknownPairKey {
    int unknown_00;
    int unknown_04;
    bool operator==(UnknownPairKey const &other) const;
};
// The text request owner-drawn controls answer for message 0x4E9 (0x005E2100, 0x005E2160, 0x005E21C0).
struct UnknownTextRequest {
    int unknown_00;
    int unknown_04;
    WideString text;
};
WideString __fastcall unknown_5e2100(HWND window, int a, int b);
// The tooltip label ("STT:...") of a control by its dialog's kind and control ID (0x005E22B0, not yet recovered).
char const *__fastcall unknown_5e22b0(unsigned int key, HWND window);
// Whether the control is in the registry (0x005E4720; the skirmish preview paint skips one that is).
bool __fastcall unknown_5e4720(HWND control);
// Gives a registered control an image to draw (0x005E1F30; GDlgSupp.cpp ping and flag controls).
void __fastcall unknown_5e1f30(HWND control, Surface *image);
// 0x25 or 0xE by the dialog's kind and the control ID (0x005E12A0).
int __fastcall unknown_5e12a0(unsigned int key, HWND window);
// 0xC0 for an edit, list or combo control of the listed dialog kinds; sets the dialog's +0xB0 (0x005E1CA0).
int __fastcall unknown_5e1ca0(HWND dialog, HWND window);
// A second per-dialog control test (0x005E72C0, not yet recovered), beside 0x005E6860.
bool __fastcall unknown_5e72c0(unsigned int key, HWND window);
// Visible owner-drawn controls counted by the EnumChildWindows callbacks 0x005E7D00 and 0x005E7DD0.
extern int unknown_visible_count_a737e4;
extern int unknown_visible_count_a763b4;
// Surfaces held by records at +0x10 (0x005FE490 counts up, 0x005FF380 down).
extern int unknown_surface_count_a763d8;
// Set once 0x005EAC30 has registered the "ComboDropWin" and "NewEdit" window classes.
extern int unknown_classes_registered_a763f0;
// The window procedures of those classes (not yet recovered).
LRESULT __stdcall unknown_combo_drop_proc_5ead20(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_new_edit_proc_5ead00(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void unknown_5eac30();
// The tooltip shown over owner-drawn controls (0x00A737F0; constructor 0x005EDFA0, static
// initializer 0x005EDF60). surface_10 holds the screen area the tooltip covers.
struct UnknownTooltipState {
    UnknownTooltipState();
    Rect rect_00;
    Surface *surface_10;
    unsigned short text_14[128];
    int shown_114;
    int drawn_118;
    int unknown_11c;
};
extern UnknownTooltipState unknown_tooltip_a737f0;
bool unknown_5ee310();
bool unknown_5ee3b0();
// A Win32 colour as a screen pixel (0x005FDA40) and back (0x005FDAA0).
int __fastcall unknown_5fda40(unsigned long color);
unsigned long __fastcall unknown_5fdaa0(unsigned short pixel);
// Sizes the dialog placement 0x005E8BA0 centres against (not yet named).
extern int unknown_7add6c;
// Owner-draw colours and sizes set by 0x005DE880 (not yet named).
extern int unknown_color_a73928;
extern int unknown_color_a7613c;
extern int unknown_color_a76158;
extern int unknown_color_a733d0;
extern int unknown_color_a733e4;
extern int unknown_color_a737e8;
extern int unknown_color_a76150;
extern int unknown_color_a7338c;
extern int unknown_color_a7615c;
extern int unknown_color_a763b0;
extern int unknown_color_a73910;
extern int unknown_color_a737ec;
extern int unknown_color_a7363c;
extern int unknown_color_a737e0;
extern int unknown_color_a76154;
extern int unknown_color_a763b8;
extern int unknown_color_a76140;
extern int unknown_color_a763d4;
extern int unknown_color_a736d0;
void unknown_5de880();
extern int unknown_7add78;
BOOL __stdcall unknown_5e7dd0(HWND window, LPARAM);

}
// A test of an owner-drawn dialog control by the dialog's registered kind and the control ID.
bool __fastcall OwnerDraw_Control_Test_005e6860(unsigned int key, HWND window);
#endif
