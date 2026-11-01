// Unknown84E8D0::Unknown_0042E990 (0x0042E990): removes the beacon in the house's slot (house and slot
// -1: the edited one). Cancelling the edit of another house's beacon only clears its flags; a visible
// beacon is erased from the radar first; the player's own removal sends packet 0x21 to the others.
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/beacon.hpp"
#include "shared/house.hpp"
#include "shared/session_state.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0BN@IONH@Sending?5beacon?5delete?5to?5?$CFs?6?$AA@=007cf49c

void Unknown84E8D0::Unknown_0042E990(int house, int slot)
{
    if (unknown_60) {
        bool edited;
        UnknownBeacon *beacon;
        edited = house == -1 && slot == -1;
        if (edited) {
            beacon = Unknown_0042E940(-1);
        } else {
            beacon = unknown_00[house][slot];
        }
        if (beacon) {
            int owner = beacon->unknown_house;
            if (owner != unknown_player_a35db4->ArrayIndex && edited) {
                beacon->unknown_flags &= 0xfc;
                return;
            }
            if (beacon->Unknown_0042E080()) {
                beacon->Unknown_0042DE20(Map.unknown_1218, Map.unknown_1218->Get_Rect(), true);
            }
            delete beacon;
            int index;
            for (index = 0; index < 3; index++) {
                if (beacon == unknown_00[owner][index]) {
                    goto found;
                }
            }
            return;
found:
            unknown_00[owner][index] = 0;
            unknown_60--;
            if (unknown_session_a3d298.Type != 0 && unknown_session_a3d298.Type != 5
                && owner == unknown_player_a35db4->ArrayIndex && edited) {
                UnknownBeaconPacket packet;
                packet.Type = 0x21;
                strcpy(packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
                packet.House = (unsigned char)owner;
                packet.Slot = (unsigned char)index;
                for (int player = 1; player < unknown_players_a3fa7c.Count(); player++) {
                    Debug_Printf("Sending beacon delete to %s\n", unknown_players_a3fa7c[player]);
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x3d, 1, &unknown_players_a3fa7c[player]->Address, 0, 0);
                }
            }
        }
    }
}
