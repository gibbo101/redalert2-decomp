// HRESULT __stdcall TClassFactory<TeamClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x006945B0
// Purpose: the COM class factory for TeamClass: validates the output pointer,
// refuses aggregation, constructs a TeamClass (0x9C bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x006B7430 stores the TeamClass vtables (RTTI); its
// parameters (type, house, a flag) are assumed from the three zero arguments. Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0TeamClass@@QAE@PAVTeamTypeClass@@PAVHouseClass@@H@Z=006b7430
#include "shared/class_factory.hpp"

class TeamTypeClass;
class HouseClass;

class TeamClass {
public:
    TeamClass(TeamTypeClass *type, HouseClass *house, int unknown_flag);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~TeamClass();

    unsigned char unknown_04[0x9C - 4];
};

template <>
HRESULT __stdcall TClassFactory<TeamClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    TeamClass *instance = new TeamClass(0, 0, 0);
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
