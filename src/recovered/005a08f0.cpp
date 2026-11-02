// void __fastcall Unknown_Movie_Message_005a08f0(int movie) (0x005A08F0)
// The subtitle callback of the radar's queued movies: shows the subtitle's text in the session's message
// list for its display duration (the argument is the SubTitle the movie's companion reached).
#include "shared/movie_queue.hpp"
#include "shared/subtitle.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?Add_Message@MessageListClass@@QAEPAVTextLabelClass@@PBGH0HIH_N@Z=005b4da0

void __fastcall Unknown_Movie_Message_005a08f0(int movie)
{
    SubTitle *subtitle = (SubTitle *)movie;
    if (subtitle != 0) {
        unknown_session_a3d298.Messages.Add_Message(0, 0, subtitle->Get_Text(), 0, 0x4046, subtitle->Get_Display_Duration(), false);
    }
}
