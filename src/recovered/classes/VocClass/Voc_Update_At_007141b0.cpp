// AudioEvent *Voc_Update_At(CoordStruct const &coord, AudioEventHandle *handle)
// (0x007141B0): sets a handle's event to the volume and pan of its type at a
// coordinate; stops it when silent, and starts a forever-looping type again
// when audible with no event (hypothesis).
#include "shared/voc_class.hpp"
#include "shared/audio.hpp"
// @ref ?Audio_Event_Create@@YIPAUAudioEvent@@PAUAudioEventType@@@Z=00405170
// @ref ?Audio_Event_Stop@@YIXPAUAudioEvent@@@Z=00405300
// @ref ?Audio_Event_Set_Volume@@YIXPAUAudioEvent@@H@Z=004061e0
// @ref ?Audio_Event_Set_Pan@@YIXPAUAudioEvent@@H@Z=00406280
// @ref ?Audio_Event_Handle_Event@@YIPAUAudioEvent@@PAUAudioEventHandle@@@Z=00406140
// @ref ?Audio_Event_Handle_Type@@YIPAUAudioEventType@@PAUAudioEventHandle@@@Z=00406180
// @ref ?Audio_Event_Handle_Set@@YIXPAUAudioEventHandle@@PAUAudioEvent@@PAUAudioEventType@@@Z=00406100
// @ref ?Audio_Event_Type_Loops_Forever@@YIHPAUAudioEventType@@@Z=00406660
// @ref ?Audio_Event_Set_Flag_8@@YIXPAUAudioEvent@@@Z=004052f0
// @ref ?Voc_Volume_At@@YIMABUCoordStruct@@PAHPAUAudioEventType@@@Z=00713f30

AudioEvent *__fastcall Voc_Update_At(CoordStruct const &coord, AudioEventHandle *handle)
{
    AudioEvent *event = 0;
    if (handle != 0) {
        event = Audio_Event_Handle_Event(handle);
        AudioEventType *type = Audio_Event_Handle_Type(handle);
        if (type != 0) {
            int pan;
            float volume = Voc_Volume_At(coord, &pan, type);
            if (volume > 0) {
                if (event == 0 && Audio_Event_Type_Loops_Forever(type)) {
                    event = Audio_Event_Create(type);
                    if (event != 0) {
                        Audio_Event_Set_Flag_8(event);
                    }
                }
                if (event != 0) {
                    unsigned int level = (unsigned int)(volume * 16384.0f);
                    if (level >= 0x4000) {
                        level = 0x4000;
                    }
                    Audio_Event_Set_Volume(event, level);
                    Audio_Event_Set_Pan(event, pan);
                }
            } else if (event != 0) {
                Audio_Event_Stop(event);
                event = 0;
            }
        }
        Audio_Event_Handle_Set(handle, event, type);
    }
    return event;
}
