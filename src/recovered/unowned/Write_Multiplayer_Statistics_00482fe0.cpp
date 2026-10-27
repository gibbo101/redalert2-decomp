#include "shared/winsock_interface.hpp"
#include "shared/ipx_address.hpp"
#include "shared/options.hpp" // Options.GameSpeed
struct _iobuf;
extern "C" _iobuf *__cdecl fopen(char const *name, char const *mode);
extern "C" int __cdecl fprintf(_iobuf *file, char const *format, ...);
extern "C" int __cdecl fclose(_iobuf *file);
// @ref _fopen=00783a45
// @ref _fprintf=007839d8
// @ref _fclose=0078395b
// @ref ?As_String_00523840@IPXAddressClass@@=00523840
// @ref ?PacketTransport@@=00839c50
// @ref ?Frame@@=00a40d2c
// @ref ?Options@@=00a40b18
extern int unknown_game_mode_a3d298;
extern unsigned int accumulated_fps_00a6eb20;
extern unsigned int fps_sample_count_00a6eb24;
extern int max_max_ahead_00a3d578;
extern int latency_setting_00a3fba4;
// @ref ?unknown_game_mode_a3d298@@=00a3d298
// @ref ?accumulated_fps_00a6eb20@@=00a6eb20
// @ref ?fps_sample_count_00a6eb24@@=00a6eb24
// @ref ?max_max_ahead_00a3d578@@=00a3d578
// @ref ?latency_setting_00a3fba4@@=00a3fba4

#include "shared/network_statistics.hpp"
// @ref ?player_statistics_00a3d584@@=00a3d584
extern char const stats_filename[];
// @ref ?stats_filename@@=007d37cc
extern char const stats_mode[];
// @ref ?stats_mode@@=007d37d8
extern char const stats_frames[];
// @ref ?stats_frames@@=007d37c0
extern char const stats_average_fps[];
// @ref ?stats_average_fps@@=007d37ac
extern char const stats_max_ahead[];
// @ref ?stats_max_ahead@@=007d3798
extern char const stats_latency[];
// @ref ?stats_latency@@=007d3780
extern char const stats_speed[];
// @ref ?stats_speed@@=007d3768
extern char const stats_local_address[];
// @ref ?stats_local_address@@=007d374c
extern char const stats_name[];
// @ref ?stats_name@@=007d3740
extern char const stats_address[];
// @ref ?stats_address@@=007d3730
extern char const stats_max_average_round_trip[];
// @ref ?stats_max_average_round_trip@@=007d3718
extern char const stats_max_round_trip[];
// @ref ?stats_max_round_trip@@=007d3704
extern char const stats_resends[];
// @ref ?stats_resends@@=007d36f4
extern char const stats_frame_sync_stalls[];
// @ref ?stats_frame_sync_stalls@@=007d36dc
extern char const stats_command_count_stalls[];
// @ref ?stats_command_count_stalls@@=007d36c0
extern char const stats_lost[];
// @ref ?stats_lost@@=007d36b4
extern char const stats_percent_lost[];
// @ref ?stats_percent_lost@@=007d36a0

void __cdecl Write_Multiplayer_Statistics_00482fe0()
{
    if (unknown_game_mode_a3d298 == 4) {
        _iobuf *file = fopen(stats_filename, stats_mode);
        if (file) {
            fprintf(file, stats_frames, Frame);
            unsigned int average = fps_sample_count_00a6eb24 ? accumulated_fps_00a6eb20 / fps_sample_count_00a6eb24 : 0;
            fprintf(file, stats_average_fps, average);
            fprintf(file, stats_max_ahead, max_max_ahead_00a3d578);
            fprintf(file, stats_latency, latency_setting_00a3fba4);
            fprintf(file, stats_speed, Options.GameSpeed);
            if (PacketTransport) {
                for (int index=0; index<PacketTransport->unknown_slot18(); ++index) {
                    unsigned int *address=(unsigned int *)PacketTransport->unknown_slot19(index);
                    if (address) {
                        unsigned int ip=*address;
                        fprintf(file,stats_local_address,ip&255,(ip>>8)&255,(ip>>16)&255,ip>>24);
                    }
                }
            }
            for (int player=0; player<8; ++player) {
                UnknownNetworkPlayerStatistics &statistics=player_statistics_00a3d584[player];
                if (statistics.unknown_00[0]) {
                    fprintf(file,stats_name,statistics.unknown_00);
                    fprintf(file,stats_address,statistics.Address.As_String_00523840(0));
                    fprintf(file,stats_max_average_round_trip,statistics.MaxAverageRoundTrip);
                    fprintf(file,stats_max_round_trip,statistics.MaxRoundTrip);
                    fprintf(file,stats_resends,statistics.Resends);
                    fprintf(file,stats_frame_sync_stalls,statistics.FrameSyncStalls);
                    fprintf(file,stats_command_count_stalls,statistics.CommandCountStalls);
                    fprintf(file,stats_lost,statistics.Lost);
                    fprintf(file,stats_percent_lost,statistics.PercentLost);
                }
            }
            fclose(file);
        }
    }
}
