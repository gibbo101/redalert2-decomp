// void Audio_Device_Dump(AudioDevice *device, void (__fastcall *print)(char const *), int with_names) (0x00403A80)
// Prints the device (driver name and index), its mixer and level timing, the frame counters and one line per channel
// (index, type, state, format, priority, volume, name) through the print function (name hypothesis).
// @ref ??_C@_0CI@ONHE@?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9@=007cc99c
// @ref ??_C@_0BO@FFP@?$CD?$CF2d?5?3?$CFs?3?$CFs?3?$CFs?3?$CF4d?3?$CF3d?3?$CF?410s?6?$AA@=007cc9c4
// @ref ??_C@_0BA@KCCG@?$CF02d?9?$CF2d?9?$CFc?$CFc?$CFc?$AA@=007cc9e4
// @ref ??_C@_04FLDM@?$DP?$DP?$DP?5?$AA@=007cc9f4
// @ref ??_C@_04CACH@STD?5?$AA@=007cc9fc
// @ref ??_C@_04FMHO@USER?$AA@=007cca04
// @ref ??_C@_07FDEC@FREE?5?5?5?$AA@=007cca0c
// @ref ??_C@_07MJHB@PAUSED?5?$AA@=007cca14
// @ref ??_C@_07KHIP@PLAYING?$AA@=007cca1c
// @ref ??_C@_0CH@CEHA@Chan?3TYPE?3?5STATE?5?3?5FORMAT?5?5?3PRI?5@=007cca24
// @ref ??_C@_0CM@EFID@Chan?3TYPE?3?5STATE?5?3?5FORMAT?5?5?3PRI?5@=007cca4c
// @ref ??_C@_0CA@IHB@Frames?3?5?$CFd?5Oversamp?3?5?$CFd?5Lag?3?5?$CFd?$AA@=007cca78
// @ref ??_C@_08HEKE@level?3?$CFs?$AA@=007cca98
// @ref ??_C@_08ICON@mixer?3?$CFs?$AA@=007ccaa4
// @ref ??_C@_08NDLN@?$CFs?5?$CI?$CFd?$CJ?6?$AA@=007ccab0
// @ref ??_C@_0CJ@LPLO@Audio?5Device?5Dump?5?9?9?9?9?9?9?9?9?9?9?9?9?9?9@=007ccabc
// @ref ?Format@AudioTimeSpan@@QAIXPAD@Z=004039c0
#include "shared/crt_string.hpp"
#include "shared/audio.hpp"

void __fastcall Audio_Device_Dump(AudioDevice *device, void (__fastcall *print)(char const *), int with_names)
{
    char line[200];
    char span[100];
    char name[200];
    char format[200];

    print("Audio Device Dump ---------------------\n");
    sprintf(line, "%s (%d)\n", device->Driver->Info->Name, device->Id);
    print(line);
    device->Span.Format(span);
    sprintf(line, "mixer:%s", span);
    print(line);
    device->LevelSpan.Format(span);
    sprintf(line, "level:%s", span);
    print(line);
    sprintf(line, "Frames: %d Oversamp: %d Lag: %d", device->unknown_1d8, device->unknown_1dc, device->unknown_1e0);
    print(line);
    if (with_names) {
        sprintf(line, "Chan:TYPE: STATE : FORMAT  :PRI :VOL: NAME\n");
    } else {
        sprintf(line, "Chan:TYPE: STATE : FORMAT  :PRI :VOL:\n");
    }
    print(line);
    AudioListCursor cursor;
    cursor.First(&device->ChannelList);
    int index = 0;
    for (AudioChannel *channel = (AudioChannel *)cursor.Node; channel != 0; channel = (AudioChannel *)cursor.Next()) {
        char const *state;
        if (channel->Flags & AUDIO_CHANNEL_PLAYING) {
            state = "PLAYING";
        } else if (channel->Flags & AUDIO_CHANNEL_PAUSED) {
            state = "PAUSED ";
        } else {
            state = "FREE   ";
        }
        char const *type;
        if (channel->unknown_0c >= 0x1000) {
            type = "USER";
        } else if (channel->unknown_0c == 1) {
            type = "STD ";
        } else {
            type = "??? ";
        }
        name[0] = '\0';
        sprintf(format, "%02d-%2d-%c%c%c", channel->Format.Rate / 1000,
                channel->Format.Type == AUDIO_FORMAT_PCM ? channel->Format.BytesPerSample * 8 : 4,
                channel->Format.Channels == 1 ? 'M' : 'S', channel->FormatChanged ? '*' : ' ',
                channel->unknown_1a0 ? '+' : ' ');
        sprintf(line, "#%2d :%s:%s:%s:%4d:%3d:%.10s\n", index, type, state, format, channel->unknown_a0,
                ((channel->Settings.Volume.Current >> 16) * 100) >> 14, name);
        print(line);
        index++;
    }
    print("--------------------------------------\n");
}
