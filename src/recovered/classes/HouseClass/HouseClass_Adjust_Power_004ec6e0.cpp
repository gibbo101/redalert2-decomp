// void HouseClass::Adjust_Power(int amount) (0x004EC6E0)
// Adds to the power output (only while 0x00A40958 is set); when the house
// turns under- or re-powered, every sink of its outgoing interface is told.
// @ref ?unknown_func_4ec9b0@HouseClass@@QAEXXZ=004ec9b0
// @ref _unknown_iid_7a1ac0=007a1ac0
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/com_persist.hpp"

void HouseClass::Adjust_Power(int amount)
{
    if (unknown_flag_a40958) {
        bool was_low = Power < Drain;
        Power += amount;
        unknown_func_4ec9b0();
        bool low = Power < Drain;
        if (!unknown_a40774 && was_low != low) {
            IConnectionPointContainer *container;
            QueryInterface(IID_IConnectionPointContainer, (void **)&container);
            IEnumConnectionPoints *points;
            container->EnumConnectionPoints(&points);
            IConnectionPoint *point;
            while (points->Next(1, &point, 0) >= 0) {
                GUID iid;
                point->GetConnectionInterface(&iid);
                if (iid == unknown_iid_7a1ac0) {
                    IEnumConnections *connections;
                    point->EnumConnections(&connections);
                    tagCONNECTDATA data;
                    while (connections->Next(1, &data, 0) >= 0) {
                        if (low) {
                            ((IUnknownHouseSink *)data.pUnk)->Power_Low();
                        } else {
                            ((IUnknownHouseSink *)data.pUnk)->Power_Restored();
                        }
                        data.pUnk->Release();
                    }
                    connections->Release();
                    break;
                }
                point->Release();
            }
            container->Release();
            points->Release();
        }
    }
}
