// BlowfishEngine: client of the Blowfish COM server (Blowfish.dll) that
// encrypts and decrypts 8-byte blocks.
//
// No RTTI; the name is Westwood's (the pipe and straw members are "BF").
// Methods at 0x00435580-0x00435660, before BlowPipe.cpp. The object holds
// only the COM interface pointer; the constructor creates the server
// (CoCreateInstance + OleRun + QueryInterface, as a VC6 _com_ptr_t does) and
// the methods forward to the interface, raising E_POINTER without one.
#ifndef RA2_SHARED_BLOWFISH_ENGINE_HPP
#define RA2_SHARED_BLOWFISH_ENGINE_HPP

#include "shared/com_api.hpp"

// The Blowfish server's interface. Slots 4 and 5 are not used by the game.
struct IBlowfish : public IUnknown {
    virtual HRESULT __stdcall Submit_Key(long length, unsigned char const *key) = 0;     // +0x0C
    virtual HRESULT __stdcall unknown_10() = 0;                                         // +0x10
    virtual HRESULT __stdcall unknown_14() = 0;                                         // +0x14
    virtual HRESULT __stdcall Encrypt(long length, unsigned char const *plaintext,
                                      unsigned char *cyphertext) = 0;                   // +0x18
    virtual HRESULT __stdcall Decrypt(long length, unsigned char const *cyphertext,
                                      unsigned char *plaintext) = 0;                    // +0x1C
};

extern "C" GUID const CLSID_Blowfish;  // 0x007A1A70
extern "C" GUID const IID_IBlowfish;   // 0x007CF5B0

class BlowfishEngine {
public:
    BlowfishEngine();                                               // 0x00435580
    ~BlowfishEngine();                                              // 0x004355F0

    // Sets the cipher key (up to 56 bytes).
    void Submit_Key(void const *key, int length);                   // 0x00435600
    // Process whole 8-byte blocks; return length.
    int Encrypt(void const *plaintext, int length, void *cyphertext);   // 0x00435630
    int Decrypt(void const *cyphertext, int length, void *plaintext);   // 0x00435660

    IBlowfish *Interface;   // +0x00 COM interface (null when creation failed)

private:
    // The interface, raising E_POINTER when there is none.
    IBlowfish *Server() const
    {
        if (Interface == 0) {
            _com_issue_error(E_POINTER);
        }
        return Interface;
    }
};

#endif
