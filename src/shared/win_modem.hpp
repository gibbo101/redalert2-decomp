// WinModemClass: the Win32 serial port/modem layer (Westwood's wincomm.cpp;
// vtable 0x007AF4E0, ten slots; no RTTI) and the modem registry helpers.
#ifndef RA2_SHARED_WIN_MODEM_HPP
#define RA2_SHARED_WIN_MODEM_HPP

#include "shared/win32_api.hpp"

// The sub key of base_key named search_key (any case), opened for reading;
// base_key is closed when close is set; null if absent (0x007341C0).
HKEY __fastcall Get_Registry_Sub_Key(HKEY base_key, char const *search_key, bool close);
// The first modem's FriendlyName from HKLM\Enum\Root\Modem\0000 (0x00734310).
bool __fastcall Get_Modem_Name_From_Registry(char *buffer, int buffer_len);

enum {
    SIZE_OF_WINDOWS_SERIAL_BUFFER = 0x2000
};

class WinModemClass {
public:
    WinModemClass();                                                    // 0x00734120
    virtual ~WinModemClass();                                           // 0x00734170 (deleting 0x00735610, slot 0)
    virtual HANDLE Serial_Port_Open(char const *port_name, int baud, int parity, int wordlen,
                                    int stopbits);                      // 0x00734410 slot 1
    virtual void Set_Modem_Dial_Type(int method);                       // 0x007348A0 slot 2
    virtual unsigned Get_Modem_Status();                                // 0x007348B0 slot 3
    virtual void Set_Serial_DTR(bool state);                            // 0x00734900 slot 4
    virtual int Get_Modem_Result(int delay, char *buffer, int buffer_len, int timeout);   // 0x00734CD0 slot 5
    virtual void Dial_Modem(char const *dial_number);                  // 0x00734F50 slot 6 ("ATDT"/"ATDP")
    virtual int Send_Command_To_Modem(char const *command, char terminator, char *buffer, int buffer_len,
                                      int delay, int retries, int timeout);   // 0x00735110 slot 7
    virtual void Set_Echo_Function(void (__fastcall *func)(char c));             // 0x007354A0 slot 8
    virtual void Set_Abort_Function(int (*func)());                     // 0x007354B0 slot 9

    void Serial_Port_Close();                                           // 0x00734950
    bool Enter_Failsafe_Mode();                                         // 0x00734670 (9600 baud, 8N1)
    void Leave_Failsafe_Mode();                                         // 0x007347C0
    // Moves what the port has received into the circular buffer; true when
    // anything arrived (0x00734980).
    bool Read_Serial_Chars();
    int Read_From_Serial_Port(unsigned char *dest_ptr, int buffer_len); // 0x00734B30
    void Wait_For_Serial_Write();                                       // 0x00734BC0
    void Write_To_Serial_Port(unsigned char *buffer, int length);       // 0x00734C70
    // Counts the communication errors ClearCommError reported (0x007354D0).
    void Process_Errors(unsigned long errors, COMSTAT status);

    unsigned long FramingErrors;        // +0x04
    unsigned long IOErrors;             // +0x08
    unsigned long BufferOverruns;       // +0x0C
    unsigned long InBufferOverflows;    // +0x10
    unsigned long ParityErrors;         // +0x14
    unsigned long OutBufferOverflows;   // +0x18
    unsigned long InQueue;              // +0x1C
    unsigned long OutQueue;             // +0x20
    unsigned char *SerialBuffer;        // +0x24 circular receive buffer
    OVERLAPPED ReadOverlap;             // +0x28
    OVERLAPPED WriteOverlap;            // +0x3C
    bool WaitingForSerialCharRead;      // +0x50
    bool WaitingForSerialCharWrite;     // +0x51
    int SerialBufferReadPtr;            // +0x54
    int SerialBufferWritePtr;           // +0x58
    HANDLE PortHandle;                  // +0x5C
    int DialingMethod;                  // +0x60
    void (__fastcall *EchoFunction)(char c);   // +0x64
    int (*AbortFunction)();             // +0x68
    unsigned char TempSerialBuffer[SIZE_OF_WINDOWS_SERIAL_BUFFER];   // +0x6C
    DCB SerialSettings;                 // +0x206C
};

// The open serial port (0x00B25BB0; Westwood's SerialPort).
extern WinModemClass *SerialPort;

#endif
