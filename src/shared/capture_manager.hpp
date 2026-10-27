// CaptureManagerClass (CaptureManager.cpp, 0x00467D30-0x00468406; RTTI
// vtables 0x0079D7B8 primary, 0x0079D79C at +4, 0x0079D794, 0x0079D78C).
// Layout from the constructors 0x00467DB0 / 0x00467E40, Compute_CRC
// 0x00468220 and Load 0x00468280: three object pointers (CRC'd by their
// IDs, fixed up on load); Size_Of 0x30, Kind_Of 0x42. Member names are
// placeholders. Every manager is listed in
// unknown_CaptureManagerClass_list_008505a0 (defined with the unit's header statics).
#ifndef RA2_SHARED_CAPTURE_MANAGER_HPP
#define RA2_SHARED_CAPTURE_MANAGER_HPP

#include "shared/abstract.hpp"
#include "shared/vector_class.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

extern "C" GUID const CLSID_CaptureManagerClass;   // 0x007A1DE0

class CaptureManagerClass : public AbstractClass {
public:
    CaptureManagerClass(AbstractClass *owner);                  // 0x00467DB0
    CaptureManagerClass();                                      // 0x00467E40
    CaptureManagerClass(NoInitClass const &noinit);             // 0x00467ED0
    virtual ~CaptureManagerClass();                             // 0x00467F00

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x00468320
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x00468280
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00468300
    virtual int Kind_Of() const;                                // 0x00468370
    virtual int Size_Of() const;                                // 0x00468360
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x00468220

    AbstractClass *unknown_24;      // +0x24
    AbstractClass *unknown_28;      // +0x28
    AbstractClass *Owner;           // +0x2C (constructor argument; hypothesis)
};

extern DynamicVectorClass<CaptureManagerClass *> unknown_CaptureManagerClass_list_008505a0;   // 0x008505A0

#endif
