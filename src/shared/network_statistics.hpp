#ifndef RA2_SHARED_NETWORK_STATISTICS_HPP
#define RA2_SHARED_NETWORK_STATISTICS_HPP
#include "shared/ipx_address.hpp"
// Observed 104-byte per-player record, eight entries. The first byte starts
// a narrow name string; other fields in the first64bytes remain unknown.
struct UnknownNetworkPlayerStatistics {
    char unknown_00[0x40];
    unsigned int MaxRoundTrip;
    unsigned int Resends;
    unsigned int Lost;
    unsigned int PercentLost;
    unsigned int MaxAverageRoundTrip;
    unsigned int FrameSyncStalls;
    unsigned int CommandCountStalls;
    IPXAddressClass Address;
};
typedef char NetworkPlayerStatistics_stride_check[(sizeof(UnknownNetworkPlayerStatistics)==104)?1:-1];
extern UnknownNetworkPlayerStatistics player_statistics_00a3d584[8];
#endif
