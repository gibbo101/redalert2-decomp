// Destroys all audio devices and their channels; original00403210.
#include "shared/audio.hpp"
void __cdecl operator delete(void *block);
// @ref ?Audio_System_Instance@@3PAUAudioSystem@@A=007cc968
void __fastcall Audio_Destroy_Devices_00403210()
{
    Audio_System_Instance->Busy++;
    AudioListCursor cursor;
    Audio_First_Device(&cursor);
    AudioDevice *device = (AudioDevice *)cursor.Node;
    while (device != 0) {
        Audio_Cursor_Advance(&cursor);
        Audio_System_Instance->Busy++;
        Audio_List_Remove(device);
        if (--Audio_System_Instance->Busy < 0) Audio_System_Instance->Busy = 0;
        AudioListCursor channels;
        channels.First(&device->ChannelList);
        AudioChannel *node = (AudioChannel *)channels.Node;
        AudioChannel *channel = node;
        while (node != 0) {
            node = (AudioChannel *)channels.Next();
            Audio_Channel_Destroy(channel);
            channel = node;
        }
        device->Driver->Info->Close(device);
        device->Driver->Devices[device->DriverIndex] = 0;
        if ((device->Driver->DeviceCount -= 1) < 0) device->Driver->DeviceCount = 0;
        operator delete(device);
        device = (AudioDevice *)cursor.Node;
    }
    if (--Audio_System_Instance->Busy < 0) Audio_System_Instance->Busy = 0;
}
