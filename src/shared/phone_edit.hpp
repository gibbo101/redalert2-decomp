// PhoneEd.cpp (unit 0x0060D780-0x0060EA5F; TibSun phoneed.cpp): the null-modem phone book dialog
// (PhoneEdit, dialog 0xEE) and the phone entry editor (PhoneEntryEdit). The serial dialog
// (NullDlg.CPP 0x005CDF00) runs PhoneEdit::Dialog on a stack object. Neither class is polymorphic;
// names and member order follow TibSun.
#ifndef RA2_SHARED_PHONE_EDIT_HPP
#define RA2_SHARED_PHONE_EDIT_HPP

#include "shared/win32_api.hpp"
#include "shared/serial_settings.hpp"

class PhoneEdit {
public:
    PhoneEdit() {}
    bool Dialog();                      // 0x0060D970

    bool Dial();                        // 0x0060DC80
    void Build_Phone_Listbox();         // 0x0060DE40
    void Select();                      // 0x0060E0E0
    void Add();                         // 0x0060E160
    void Edit();                        // 0x0060E2E0
    void Delete();                      // 0x0060E420

    HWND _Dialog;                       // +0x00
    int RC;                             // +0x04
    bool Changed;                       // +0x08
    char Number[21];                    // +0x09
};

class PhoneEntryEdit {
public:
    PhoneEntryEdit() {}
    bool Dialog(PhoneEntryClass *phone);    // 0x0060E4C0

    void Save();                        // 0x0060E7A0
    void Init();                        // 0x0060E900

    HWND _Dialog;                       // +0x00
    int RC;                             // +0x04
    PhoneEntryClass *Phone;             // +0x08
    SerialSettingsType TempSettings;    // +0x0C
};

BOOL __stdcall Phone_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);       // 0x0060D9F0
BOOL __stdcall Edit_Phone_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // 0x0060E540

#endif
