// void __fastcall Audio_System_Shutdown() -- 0x00402990
// Purpose: when initialized, remove every device (channels destroyed, closed, unlinked from its driver, freed), then
// destroy every driver. The device cursor goes through Audio_First_Device/Audio_Cursor_Advance (inlined, the cursor stays
// in memory); the channels through AudioListIterator::Next 0x004035D0 (another unit, called).
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_System_Shutdown()
{
    if (Audio_Initialized != 0) {
        Audio_System_Instance->Busy++;
        AudioListCursor cursor;
        Audio_First_Device(&cursor);
        AudioDevice *device = (AudioDevice *)cursor.Node;
        while (device != 0) {
            Audio_Cursor_Advance(&cursor);
            Audio_System_Instance->Busy++;
            Audio_List_Remove(device);
            if (--Audio_System_Instance->Busy < 0) {
                Audio_System_Instance->Busy = 0;
            }
            AudioListIterator it;
            it.First(&device->ChannelList);
            AudioChannel *channel = (AudioChannel *)it.Node;
            while (channel != 0) {
                AudioChannel *following = (AudioChannel *)it.Next();
                Audio_Channel_Destroy(channel);
                channel = following;
            }
            device->Driver->Info->Close(device);
            device->Driver->Devices[device->DriverIndex] = 0;
            if ((device->Driver->DeviceCount -= 1) < 0) {
                device->Driver->DeviceCount = 0;
            }
            operator delete(device);
            device = (AudioDevice *)cursor.Node;
        }
        if (--Audio_System_Instance->Busy < 0) {
            Audio_System_Instance->Busy = 0;
        }
        cursor.First(&Audio_System_Instance->Drivers);
        AudioDriver *driver = (AudioDriver *)cursor.Node;
        while (driver != 0) {
            cursor.Next();
            Audio_Destroy_Driver(driver);
            driver = (AudioDriver *)cursor.Node;
        }
        Audio_Initialized = 0;
    }
}
