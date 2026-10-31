// void IPXManagerClass::Store_Stats() (0x00526C90)
// Records each remote player's connection statistics: name and address
// once, the worst round trip, the worst average round trip, resends and
// losses.
#include "shared/ipx_manager.hpp"
#include "shared/house.hpp"
#include "shared/network_statistics.hpp"
#include "shared/modem_guest.hpp"
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?player_statistics_00a3d584@@3PAUUnknownNetworkPlayerStatistics@@A=00a3d584

void IPXManagerClass::Store_Stats()
{
    for (int i = 0; i < NumConnections; i++) {
        HouseClass *house = Houses[Connection[i]->ID];

        if (house != 0 && house != unknown_player_a35db4) {
            UnknownNetworkPlayerStatistics &stats = player_statistics_00a3d584[i];
            if (stats.unknown_00[0] == '\0') {
                Unknown_006FA0F0(stats.unknown_00, Connection[i]->Name, -1);
                stats.Address = Connection[i]->Address;
            }

            int maxtime = Connection[i]->Queue->Max_Delay();
            int maxround = 1000 * maxtime / 60;
            stats.MaxRoundTrip = ((int)stats.MaxRoundTrip > maxround) ? stats.MaxRoundTrip : maxround;

            unsigned int avgtime = Connection[i]->Queue->Avg_Delay();
            int avground = (int)(1000 * avgtime / 60);
            stats.MaxAverageRoundTrip = (avground > (int)stats.MaxAverageRoundTrip) ? avground : stats.MaxAverageRoundTrip;

            stats.Resends = Connection[i]->unknown_08;
            stats.Lost = Connection[i]->unknown_0c;
            stats.PercentLost = Connection[i]->unknown_10;
        }
    }
}
