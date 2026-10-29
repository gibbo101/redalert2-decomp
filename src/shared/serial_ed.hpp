// The serial settings dialog (SerialEd.cpp; resource 0xED, hypothesis: Red
// Alert's Com_Settings_Dialog). A stack object of Select_Serial_Dialog (0x005CDF00).
#ifndef RA2_SHARED_SERIAL_ED_HPP
#define RA2_SHARED_SERIAL_ED_HPP

#include "shared/win32_api.hpp"
#include "shared/serial_settings.hpp"

class SerialEdDialog {
public:
    // Runs the dialog on settings; true when it ended with 1 (the edited
    // settings, kept at +0x88, are copied back) (0x0066CA70).
    bool Dialog_0066ca70(SerialSettingsType *settings);
    // The dialog procedure (DWL_USER holds the object) (0x0066CB00).
    static int __stdcall Dialog_Proc_0066cb00(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
    // Reads the controls into Settings; false (with a message) when the port is invalid (0x0066CF60).
    bool Read_Settings_0066cf60();
    // Copies settings into Settings and fills the controls (0x0066D370).
    void Init_0066d370(SerialSettingsType const *settings);
    // Fills the port combo box (0x657): COM1-COM4, the registry modems (data 5..), the
    // custom entry (data 4), and selects Settings.ModemName or Settings.Port (0x0066D5A0).
    void Fill_Port_0066d5a0();
    // Fills the baud rate combo box (0x658) and selects Settings.Baud (0x0066D860).
    void Fill_Baud_0066d860();
    // Fills the call-waiting combo box (0x659) with the session's strings and
    // selects Settings.CallWaitStringIndex (0x0066D930).
    void Fill_Call_Wait_0066d930();
    // Fills the init string list (0x65E) with the session's init strings and
    // selects Settings.InitStringIndex, made valid first (0x0066D9B0).
    void Fill_Init_Strings_0066d9b0();
    // Checks radio button 0x65C when Settings.DialMethod is 0, 0x65B otherwise (0x0066DA70).
    void Update_Radio_0066da70();
    // Shows, enables and focuses edit box id with the text after the '-' of Buffer (0x0066DAE0).
    void Show_Text_0066dae0(int id);
    // Takes the custom port from the hidden edit box 0x65F into Buffer: a known
    // address or COM1-COM4 selects that port, other text becomes the custom entry
    // of 0x657; a bad COM number shows TXT_INVALID_PORT_ADDRESS (0x0066DB50).
    void Read_Custom_Port_0066db50();
    // Takes the custom call-waiting text from the hidden edit box 0x65A into
    // CustomText and shows it as the custom entry of 0x659 (0x0066DCF0).
    void Read_Custom_Call_Wait_0066dcf0();
    // Renames the entry of combo box id holding data to "<TXT_CUSTOM> text"
    // when its text after the '-' differs, and selects it (0x0066DD60).
    void Set_Custom_Entry_0066dd60(int id, int data, char const *text);
    // Adds the text of edit box 0x65D (upper case) to the init string list 0x65E and the
    // session's init strings unless listed, and selects it (0x0066DE80).
    void Add_Init_String_0066de80();
    // Removes the selected entry of the init string list 0x65E and from the session's
    // init strings, and selects the next one (0x0066DFE0).
    void Delete_Init_String_0066dfe0();

    HWND Window;                    // +0x00 the dialog
    int Result;                     // +0x04 -1 while running
    char Buffer[0x80];              // +0x08 control text (the custom call-waiting text: 16)
    SerialSettingsType Settings;    // +0x88 the edited settings
    int ModemCount;                 // +0xF8 the registry modems listed
    char ModemNames[10][63];        // +0xFC their names
    char unknown_372[0x374 - 0x372];
};

#endif
