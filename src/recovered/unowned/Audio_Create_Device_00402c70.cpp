// AudioDevice *__fastcall Audio_Create_Device(int driver_index, AudioFormat const *format) -- 0x00402C70
// Purpose: find the driver owning device slot driver_index, create and open the device on first use, add a reference.
// LevelSpan is set up inline (Reset/Set(33)/Set_08(165)/Set_20(165) stores), Span through the out-of-line methods.
// @ref ?Audio_Device_Update@@YIHPAUAudioDevice@@@Z=0x00402F60
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);

AudioDevice *__fastcall Audio_Create_Device(int driver_index, AudioFormat const *format)
{
    if (driver_index == -1) {
        driver_index = 0;
    }
    int slot = driver_index;
    AudioDevice *device;
    AudioListCursor cursor;
    cursor.First(&Audio_System_Instance->Drivers);
    AudioDriver *driver = (AudioDriver *)cursor.Node;
    while (driver != 0) {
        if (slot < driver->unknown_ready_18) {
            break;
        }
        slot -= driver->unknown_ready_18;
        driver = (AudioDriver *)cursor.Next();
    }
    if (driver == 0) {
        goto failed;
    }
    device = driver->Devices[slot];
    if (device == 0) {
        AudioDriverInfo *info = driver->Info;
        AudioDevice *created = (AudioDevice *)operator new(sizeof(AudioDevice));
        memset(created, 0, sizeof(AudioDevice));
        Audio_List_Init_Node(created);
        created->Driver = driver;
        created->DriverIndex = slot;
        created->RefCount = 0;
        driver->DeviceCount++;
        driver->Devices[slot] = created;
        created->ChannelDriver = info->ChannelDriver;
        Audio_List_Init(&created->ChannelList);
        created->Levels.Init();
        created->unknown_busy_104 = 0;
        created->unknown_update_10c = Audio_Device_Update;
        created->LevelSpan.unknown_00 = 0;
        created->LevelSpan.LateLimit = 0;
        created->LevelSpan.Elapsed = 0;
        created->LevelSpan.Peak = 0;
        created->LevelSpan.LastTime = 0;
        created->LevelSpan.TickCount = 0;
        created->LevelSpan.unknown_50 = 0;
        created->LevelSpan.unknown_40 = 5000;
        created->LevelSpan.Maximum = 0;
        created->LevelSpan.unknown_38 = 0;
        created->LevelSpan.unknown_54 = 0;
        created->LevelSpan.LateCount = 0;
        created->LevelSpan.unknown_00 = 33;
        created->LevelSpan.LateLimit = 33;
        created->LevelSpan.PeakWindow = created->LevelSpan.unknown_00 * 10;
        created->LevelSpan.LateLimit = 165;
        created->LevelSpan.PeakWindow = 165;
        created->Span.Reset();
        created->Span.Set(33);
        Audio_Format_Init(&created->DefaultFormat);
        Audio_Format_Init(&created->NativeFormat);
        if (format != 0) {
            created->DefaultFormat = *format;
        }
        if (info->Open(created) != 0) {
            if (created != 0) {
                Audio_Device_Destroy(created);
            }
            goto failed;
        }
        device = created;
        if (device == 0) {
            goto failed;
        }
        device->Id = driver_index;
        Audio_System_Instance->Busy++;
        Audio_List_Add_Tail(&Audio_System_Instance->Devices, device);
        if (--Audio_System_Instance->Busy < 0) {
            Audio_System_Instance->Busy = 0;
        }
    }
    device->RefCount++;
    return device;
failed:
    return 0;
}
