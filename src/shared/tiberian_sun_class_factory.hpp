// TiberianSunClassFactory (RTTI; vtable 0x007A2AA4, constructor 0x004D4510 stores the
// vtable into the global at 0x00A4088C): the class factory of the scripting
// ApplicationClass. Its CreateInstance (0x00426B70) answers IApplication and IUnknown
// with the application object at 0x0084C7DC and a third interface with the map at
// 0x008324E0; the other slots are leaves (AddRef and Release return 1, LockServer 0).
#ifndef RA2_SHARED_TIBERIAN_SUN_CLASS_FACTORY_HPP
#define RA2_SHARED_TIBERIAN_SUN_CLASS_FACTORY_HPP

#include "shared/class_factory.hpp"
#include "shared/application.hpp"

extern ApplicationClass unknown_application_object_84c7dc;     // 0x0084C7DC

class TiberianSunClassFactory : public IClassFactory {
public:
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);            // 0x00426B10
    virtual unsigned long __stdcall AddRef();                                             // 0x004D4950
    virtual unsigned long __stdcall Release();                                            // 0x004D4960
    virtual HRESULT __stdcall CreateInstance(IUnknown *outer, GUID const &iid, void **object);   // 0x00426B70
    virtual HRESULT __stdcall LockServer(int lock);                                       // 0x004D4970
};

#endif
