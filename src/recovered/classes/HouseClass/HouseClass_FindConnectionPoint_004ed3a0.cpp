// HRESULT __stdcall HouseClass::FindConnectionPoint(GUID const &iid, IConnectionPoint **point) (0x004ED3A0)
// The connection point for an outgoing interface (IConnectionPointContainer).
#include "shared/techno.hpp"

HRESULT __stdcall HouseClass::FindConnectionPoint(GUID const &iid, IConnectionPoint **point)
{
    if (point == 0) {
        return E_POINTER;
    }
    *point = 0;
    for (int index = 0; index < ConnectionPoints.Count(); index++) {
        IConnectionPoint *connection = ConnectionPoints[index];
        GUID id;
        connection->GetConnectionInterface(&id);
        if (id == iid) {
            *point = connection;
            connection->AddRef();
            return S_OK;
        }
    }
    return CONNECT_E_CANNOTCONNECT;
}
