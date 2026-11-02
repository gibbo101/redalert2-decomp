// bool SuperClass::Discharged(bool player, Cell const &cell) (0x0069D090)
// Fires the super weapon at cell and starts the next charge, or removes a
// one-time weapon (TS SuperClass::Discharged; the charge-drain weapon toggles).
#include "shared/house.hpp"
#include "shared/lightning_storm.hpp"
// @ref ?Is_Storm_Pending_Bool_0051FC30@@YI_NXZ=0051fc30
// @ref ?Place@SuperClass@@QAEXABVCell@@_N@Z=0069d850

// This unit tests only AL of Is_Storm_Pending_0051FC30 (whose own unit returns an
// int in EAX): the unit's declaration returns bool (explicit hypothesis).
bool __fastcall Is_Storm_Pending_Bool_0051FC30();

bool SuperClass::Discharged(bool player, Cell const &cell)
{
    if (Type->UseChargeDrain) {
        if (House->Unknown_004F52F0()) {
            if (unknown_0x60 == 2) {
                unknown_0x60 = 1;
                RechargeTimer = Type->RechargeTime - RechargeTimer.Value() / Rules->ChargeToDrainRatio;
                return false;
            }
            if (unknown_0x60 == 1) {
                unknown_0x60 = 2;
                RechargeTimer = (Type->RechargeTime - RechargeTimer.Value()) * Rules->ChargeToDrainRatio;
                Place(cell, player);
                return false;
            }
        } else {
            if (!House->unknown_142) {
                Place(cell, player);
            }
        }
        return false;
    }

    if ((RechargeTimer.Is_Active() && unknown_0x55 && unknown_0x57) || Type->PostClick) {
        if (Type->Type == 2 && Is_Storm_Pending_Bool_0051FC30()) {
            if (player) {
                Storm_Active_Message_00520BF0();
                return false;
            }
        } else {
            Place(cell, player);
            if (!Type->PostClick) {
                unknown_0x57 = false;
            }
            if (unknown_0x56) {
                unknown_0x56 = false;
                return Remove();
            } else {
                if (Type->ManualControl) {
                    RechargeTimer = Type->RechargeTime;
                    unknown_0x5C = -1;
                    RechargeTimer.Stop();
                } else if (!Type->PreClick && !Type->PostClick) {
                    Recharge(player);
                }
            }
        }
    }
    return false;
}
