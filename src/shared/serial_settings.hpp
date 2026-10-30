// The serial and modem settings (Westwood's SerialSettingsType, 0x70 bytes) and a
// phone book entry (PhoneEntryClass: settings, name and number). Layout from
// SessionClass's Write_MultiPlayer_Settings 0x00670380 (the session's defaults at
// +0x2830 and its PhoneBook entries); names after Red Alert's SESSION.H.
#ifndef RA2_SHARED_SERIAL_SETTINGS_HPP
#define RA2_SHARED_SERIAL_SETTINGS_HPP

struct SerialSettingsType {
    int Port;                           // +0x00 the port address, or 1 for a registry modem
    int IRQ;                            // +0x04
    int Baud;                           // +0x08
    int DialMethod;                     // +0x0C (index into the dial method letters, T or P)
    int InitStringIndex;                // +0x10
    int CallWaitStringIndex;            // +0x14
    int Compression;                    // +0x18
    int ErrorCorrection;                // +0x1C
    char CallWaitString[16];            // +0x20
    char ModemName[64];                 // +0x30 (length a hypothesis)
};

class PhoneEntryClass {
public:
    ~PhoneEntryClass() {}

    SerialSettingsType Settings;        // +0x00
    unsigned short Name[21];                      // +0x70
    char Number[22];                    // +0x9A (length a hypothesis)
};

#endif
