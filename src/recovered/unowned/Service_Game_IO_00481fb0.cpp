#include "shared/serial_progress.hpp"
#include "shared/wol_sink.hpp"
#include "shared/movie.hpp"
extern DynamicVectorClass<MovieHandle *> queued_movies_00af8fd8;
void __cdecl Audio_Update();
void __cdecl Service_Network_Handshake_00482110();
extern int unknown_login_state_00b2abe4;
extern long last_online_poll_00850e10;
extern "C" long __cdecl time(long *result);
// @ref ?queued_movies_00af8fd8@@=00af8fd8
// @ref ?Audio_Update@@=00406ea0
// @ref ?Service_Network_Handshake_00482110@@=00482110
// @ref ?unknown_login_state_00b2abe4@@=00b2abe4
// @ref ?last_online_poll_00850e10@@=00850e10
// @ref ?unknown_b2abda@@=00b2abda
// @ref ?unknown_chat_a72cfc@@=00a72cfc
// @ref ?unknown_ladder_client_a72d00@@=00a72d00
// @ref _time=0078387f

void __fastcall Service_Game_IO_00481fb0()
{
    Audio_Update();
    if (queued_movies_00af8fd8.Count()>0) {
        MovieHandle *movie=queued_movies_00af8fd8[0];
        if (movie) movie->Unknown_Slot2();
    }
    if (unknown_game_mode_a3d298==3 || unknown_game_mode_a3d298==4)
        Service_Network_Handshake_00482110();
    if (unknown_game_mode_a3d298!=1) {
        if (unknown_game_mode_a3d298!=2) goto online;
    } else if (!(serial_session_flags_00a3fac0&1)) return;
        {
            unsigned char packet[252];
            int length;
            serial_manager_00a40a28.Service();
            if (unknown_id_source_a3d290->unknown_22fc) {
                while (serial_manager_00a40a28.Get_Message(packet,&length)>0) {
                    if (*(int *)packet==108 &&
                        (*(unsigned int *)(packet+24)&255)!=serial_local_player_00a3fb38) {
                        ProgressScreen.Set_Progress_006201c0(
                            1,(double)*(int *)(packet+25),Point2D(-1,-1));
                    }
                }
            }
        }
online:
    if (unknown_game_mode_a3d298==4 && !unknown_b2abda && time(0)!=last_online_poll_00850e10) {
        if (unknown_chat_a72cfc && !unknown_login_state_00b2abe4)
            unknown_chat_a72cfc->unknown_slot03();
        if (unknown_ladder_client_a72d00)
            unknown_ladder_client_a72d00->unknown_slot07_004820dd();
        last_online_poll_00850e10=time(0);
    }
}
