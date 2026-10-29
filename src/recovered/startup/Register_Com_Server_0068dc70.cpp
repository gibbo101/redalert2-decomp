// int __fastcall Register_Com_Server() (0x0068DC70)
// Registers the game's COM server under HKEY_CLASSES_ROOT: the ProgIDs
// WW.TiberianSun.1 and WW.TiberianSun (with CurVer and CLSID), and the class
// key with its ProgIDs, module path and type library; then loads RA2.TLB.
// The first five keys inline Set_Class_Root_Key; the inline budget leaves
// the class key calls out of line.
#include "shared/com_registration.hpp"
#include "shared/win32_window.hpp"
// @ref ??_C@_01PCFE@?2?$AA@=007cc944
// @ref ??_C@_05FGFK@CLSID?$AA@=007f4d9c
// @ref ??_C@_06CMNK@ProgID?$AA@=007f4d7c
// @ref ??_C@_06GIIO@CurVer?$AA@=007f4d84
// @ref ??_C@_06HFAC@CLSID?2?$AA@=007f4dc8
// @ref ??_C@_07GICL@Typelib?$AA@=007f4d38
// @ref ??_C@_0BB@PJMD@WW?4TiberianSun?41?$AA@=007f4db4
// @ref ??_C@_0BJ@LMLI@VersionIndependentProgID?$AA@=007f4d60
// @ref ??_C@_0N@BBON@Tiberian?5Sun?$AA@=007f4da4
// @ref ??_C@_0O@GBJK@NotInsertable?$AA@=007f4d50
// @ref ??_C@_0P@ICEP@WW?4TiberianSun?$AA@=007f4d8c
// @ref ??_C@_0P@IIOA@InprocServer32?$AA@=007f4d40
// @ref ??_C@_1BA@KIKB@?$AAR?$AAA?$AA2?$AA?4?$AAT?$AAL?$AAB?$AA?$AA@=007f4d28
// @ref _CLSID_TiberianSun=007a1a90
// @ref _LIBID_TiberianSun=007a1a80
// @ref __imp__LoadTypeLib@8=0079a358
// @ref __imp__StringFromGUID2@12=0079a5d4

static void Guid_To_String(GUID const &guid, char *string, int length)
{
    wchar_t wide[40];

    StringFromGUID2(guid, wide, 39);
    WideCharToMultiByte(0, 0, wide, -1, string, length, 0, 0);
}

int __fastcall Register_Com_Server()
{
    char module_path[260];
    char libid_string[40];
    char class_key[48];
    char clsid_string[40];
    IUnknown *library;

    GetModuleFileNameA(ProgramInstance, module_path, sizeof(module_path));
    Guid_To_String(CLSID_TiberianSun, clsid_string, 39);
    Guid_To_String(LIBID_TiberianSun, libid_string, 39);
    lstrcpyA(class_key, "CLSID\\");
    lstrcatA(class_key, clsid_string);

    Set_Class_Root_Key("WW.TiberianSun.1", 0, "Tiberian Sun");
    Set_Class_Root_Key("WW.TiberianSun.1", "CLSID", clsid_string);
    Set_Class_Root_Key("WW.TiberianSun", 0, "Tiberian Sun");
    Set_Class_Root_Key("WW.TiberianSun", "CurVer", "WW.TiberianSun.1");
    Set_Class_Root_Key("WW.TiberianSun", "CLSID", clsid_string);
    Set_Class_Root_Key(class_key, 0, "Tiberian Sun");
    Set_Class_Root_Key(class_key, "ProgID", "WW.TiberianSun.1");
    Set_Class_Root_Key(class_key, "VersionIndependentProgID", "WW.TiberianSun");
    Set_Class_Root_Key(class_key, "NotInsertable", 0);
    Set_Class_Root_Key(class_key, "InprocServer32", module_path);
    Set_Class_Root_Key(class_key, "Typelib", libid_string);

    library = 0;
    LoadTypeLib(L"RA2.TLB", &library);
    if (library != 0) {
        library->Release();
    }
    return 0;
}
