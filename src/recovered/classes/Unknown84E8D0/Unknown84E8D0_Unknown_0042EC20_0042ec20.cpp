// Unknown84E8D0::Unknown_0042EC20 (0x0042EC20): sets the text of the beacon in the house's slot (house
// and slot -1: the edited one). The player's own final text goes to the other players as packet 0x22;
// another visible house's beacon raises a radar event (kind 11).
#include "shared/beacon.hpp"
#include "shared/house.hpp"
#include "shared/session_state.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/debug_printf.hpp"
#include "shared/radar_event.hpp"
#include "shared/gadget.hpp"
#include "shared/text_print.hpp"
// @ref ??_C@_0BL@HAJF@Sending?5beacon?5text?5to?5?$CFs?6?$AA@=007cf4bc
// @ref ?unknown_string_83c55c@@3PADA=0083c55c

void Unknown84E8D0::Unknown_0042EC20(unsigned short const *text, int house, int slot, bool done)
{
    bool edited;
    UnknownBeacon *beacon;
    edited = house == -1 && slot == -1;
    if (edited) {
        beacon = Unknown_0042E940(-1);
    } else {
        beacon = unknown_00[house][slot];
    }
    if (beacon) {
        beacon->Unknown_0042DDF0(text);
        if (unknown_session_a3d298.Type != 0 && unknown_session_a3d298.Type != 5) {
            if (edited && beacon->unknown_house == unknown_player_a35db4->ArrayIndex && done) {
                UnknownBeaconTextPacket packet;
                packet.Type = 0x22;
                strcpy(packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
                if (text) {
                    wcsncpy(packet.Text, text, 0x80);
                } else {
                    wcscpy(packet.Text, Unknown_006FA180(unknown_string_83c55c));
                }
                packet.House = (char)unknown_player_a35db4->ArrayIndex;
                packet.Slot = -1;
                for (int index = 0; index < 3; index++) {
                    if (unknown_00[packet.House][index] == beacon) {
                        packet.Slot = (char)index;
                    }
                }
                if (packet.Slot != -1) {
                    for (int player = 1; player < unknown_players_a3fa7c.Count(); player++) {
                        Debug_Printf("Sending beacon text to %s\n", unknown_players_a3fa7c[player]);
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x1C7, 1, &unknown_players_a3fa7c[player]->Address, 0, 0);
                    }
                }
            } else if (beacon->unknown_house != unknown_player_a35db4->ArrayIndex && beacon->Unknown_0042E080()) {
                CoordStruct coord = beacon->unknown_coord;
                Unknown_0063B5B0(11, Cell(coord.X / 256, coord.Y / 256));
            }
        }
    }
}
