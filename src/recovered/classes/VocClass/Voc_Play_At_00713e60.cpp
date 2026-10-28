// AudioEvent *Voc_Play_At(int voc, CoordStruct const &coord, AudioEventHandle *handle)
// (0x00713E60): plays a sound effect at a coordinate with the volume and pan
// 0x00713F30 gives it there; a silent result stops the handle's event (name
// hypothesis).
#include "shared/voc_class.hpp"
// @ref ?Audio_Event_Create@@YIPAUAudioEvent@@PAUAudioEventType@@@Z=00405170
// @ref ?Audio_Event_Stop@@YIXPAUAudioEvent@@@Z=00405300
// @ref ?Audio_Event_Set_Volume@@YIXPAUAudioEvent@@H@Z=004061e0
// @ref ?Audio_Event_Set_Pan@@YIXPAUAudioEvent@@H@Z=00406280
// @ref ?Audio_Event_Type_Of@@YIPAUAudioEventType@@PAUAudioEvent@@@Z=00406320
// @ref ?Audio_Event_Handle_Event@@YIPAUAudioEvent@@PAUAudioEventHandle@@@Z=00406140
// @ref ?Audio_Event_Handle_Set@@YIXPAUAudioEventHandle@@PAUAudioEvent@@PAUAudioEventType@@@Z=00406100
// @ref ?Voc_Volume_At@@YIMABUCoordStruct@@PAHPAUAudioEventType@@@Z=00713f30

AudioEvent *__fastcall Voc_Play_At(int voc, CoordStruct const &coord, AudioEventHandle *handle)
{
    AudioEvent *event = 0;
    AudioEventType *type = 0;
    if (voc >= 0 && voc < unknown_VocClass_list_00ad0818.Count()) {
        type = unknown_VocClass_list_00ad0818[voc]->Event;
    }
    if (handle != 0) {
        event = Audio_Event_Handle_Event(handle);
        if (event != 0 && Audio_Event_Type_Of(event) != type) {
            Audio_Event_Stop(event);
            event = 0;
        }
    }
    if (type != 0) {
        int pan;
        float volume = Voc_Volume_At(coord, &pan, type);
        if (volume > 0) {
            unsigned int level = (unsigned int)(volume * 16384.0f);
            if (level >= 0x4000) {
                level = 0x4000;
            }
            if (event != 0 || (event = Audio_Event_Create(type)) != 0) {
                Audio_Event_Set_Volume(event, level);
                Audio_Event_Set_Pan(event, pan);
            }
        } else if (event != 0) {
            Audio_Event_Stop(event);
            event = 0;
        }
    }
    if (handle != 0) {
        Audio_Event_Handle_Set(handle, event, type);
    }
    return event;
}
