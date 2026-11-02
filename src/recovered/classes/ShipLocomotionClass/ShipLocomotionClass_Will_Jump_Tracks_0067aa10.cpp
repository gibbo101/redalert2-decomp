// @ref ?ShipRawTracks@@3QBURawTrackStruct@@B=007aad20
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0
// @ref ?ShipRawTracks@@3QBURawTrackStruct@@B=007aad20
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0
// @ref ?ShipRawTracks@@3QBURawTrackStruct@@B=007aad20
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0
#include "shared/ship_locomotion.hpp"
bool __stdcall ShipLocomotionClass::Will_Jump_Tracks()
{
    int next_face=LinkedTo->Path[0];
    if (next_face>=-1 && next_face<=8) {
        TrackControlStruct const *track=&ShipTrackControl[unknown_58];
        int track_number;
        if (unknown_60) track_number=track->StartTrack;
        else track_number=track->Track;
        bool turn=false;
        if (next_face!=8 && next_face!=-1 && Dir_To_8(UnknownFacingDir((unsigned short)((unsigned char)track->Facing<<8)))!=next_face) turn=true;
        if (next_face!=8 && next_face!=-1 && turn && ShipRawTracks[track_number-1].Jump==unknown_5c && unknown_5c) {
            int next_track=Dir_To_8(UnknownFacingDir((unsigned short)((unsigned char)track->Facing<<8)))*8+next_face;
            TrackControlStruct const *jump=&ShipTrackControl[next_track];
            if (jump->Track && ShipRawTracks[jump->Track-1].Entry) return true;
        }
    }
    return false;
}
