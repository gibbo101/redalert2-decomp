#ifndef RA2_RECOVERED_SHARED_COM_COLLECTION_HPP
#define RA2_RECOVERED_SHARED_COM_COLLECTION_HPP

// Original-target x86 views, not recovered original class declarations.
// All interface pointers intentionally share one opaque view: preserving aliasing
// between stream, element and queried interface is necessary for exact recovery.
struct ComInterface32 {
    unsigned int* slots;
};

// Only items (+4) and signed count (+16) are observed in this family.
// The meanings of the intervening words and concrete collection types are unknown.
struct ComCollection32 {
    unsigned int unknown_0x00;
    ComInterface32** items;
    unsigned int unknown_0x08;
    unsigned int unknown_0x0C;
    int count;
};

// Stack arguments and callee cleanup are observed in the original. Slots 4/0/2
// agree with IStream::Write / IUnknown::QueryInterface / IUnknown::Release.
// These bounded views retain the existing machine-level widths and alias types.
typedef int (__stdcall *ComWriteCountCall)(
    ComInterface32*, int*, unsigned int, unsigned int);
typedef int (__stdcall *ComQueryInterfaceCall)(
    ComInterface32*, const unsigned char*, ComInterface32**);
// Release conventionally returns ULONG. The original treats its EAX as signed
// and exits when negative; retain int here rather than normalizing that quirk.
typedef int (__stdcall *ComReleaseStatusCall)(ComInterface32*);

// GUID at target VA 0x007afcd0: 00000109-0000-0000-c000-000000000046.
// Supplied VC6 UUID.LIB independently labels those bytes _IID_IPersistStream.
extern "C" unsigned char ra2_iid_ipersist_stream[];
// PE import IAT VA 0x0079a5e8: ole32.dll!OleSaveToStream.
extern "C" int (__stdcall *ra2_ole_save_to_stream)(
    ComInterface32*, ComInterface32*);

#endif
