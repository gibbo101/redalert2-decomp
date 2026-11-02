// @ref ?DriveRawTracks@@3QBURawTrackStruct@@B=007a00b0
// @ref ?DriveTrackControl@@3QBUTrackControlStruct@@B=007a0180
// @ref ?DriveRawTracks@@3QBURawTrackStruct@@B=007a00b0
// @ref ?DriveTrackControl@@3QBUTrackControlStruct@@B=007a0180
// @ref ?DriveRawTracks@@3QBURawTrackStruct@@B=007a00b0
// @ref ?DriveTrackControl@@3QBUTrackControlStruct@@B=007a0180
#include "shared/drive_locomotion.hpp"
bool __stdcall DriveLocomotionClass::Will_Jump_Tracks()
{
    int next_face=LinkedTo->Path[0];
    if (next_face>=-1 && next_face<=8) {
        TrackControlStruct const *track=&DriveTrackControl[unknown_58];
        int track_number;
        if (unknown_60) track_number=track->StartTrack;
        else track_number=track->Track;
        bool turn=false;
        if (next_face!=8 && next_face!=-1 && Dir_To_8(UnknownFacingDir((unsigned short)((unsigned char)track->Facing<<8)))!=next_face) turn=true;
        if (next_face!=8 && next_face!=-1 && turn && DriveRawTracks[track_number-1].Jump==unknown_5c && unknown_5c) {
            int next_track=Dir_To_8(UnknownFacingDir((unsigned short)((unsigned char)track->Facing<<8)))*8+next_face;
            TrackControlStruct const *jump=&DriveTrackControl[next_track];
            if (jump->Track && DriveRawTracks[jump->Track-1].Entry) return true;
        }
    }
    return false;
}
