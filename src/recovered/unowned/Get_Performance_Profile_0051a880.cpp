// int __fastcall Get_Performance_Profile() -- 0x0051A880
#include "shared/win32_api.hpp"
#include "shared/directdraw.hpp"
#include "shared/dsurface.hpp"
#include "shared/surface.hpp"
#include "shared/cpu_info.hpp"
#include "shared/event.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_performance_profile_7db564@@3HA=007db564
// @ref ?unknown_profile_cpu_text_a411fc@@3PADA=00a411fc
// @ref ?unknown_profile_ram_text_a41388@@3PADA=00a41388
// @ref ?unknown_profile_vram_text_a41308@@3PADA=00a41308
// @ref ?unknown_profile_blit_text_a41408@@3PADA=00a41408
// @ref ?unknown_profile_text_a4127c@@3PADA=00a4127c
// @ref ?unknown_surface_839944@@3PAVSurface@@A=00839944
// @ref ?Get_CPU_Type@@YAHXZ=004d2a60
// @ref ?Get_CPU_Type_Name@@YIPBDXZ=004d2b80
// @ref ?Get_CPU_Speed@@YAHXZ=005abf70
// @ref ??_C@_0BM@OCEF@Profile?3?5CPU?3?$CFd?5?$CI?$CFdMhz?5?$CFs?$CJ?6?$AA@=007ddaac
// @ref ??_C@_0P@ICDP@CPU?3?5?$CFd?5Mhz?5?$CFs?$AA@=007dda9c
// @ref ??_C@_0BI@FAMN@Profile?3?5RAM?3?$CFd?5?$CI?$CFdMb?$CJ?6?$AA@=007dda84
// @ref ??_C@_0BE@MAAP@RAM?5reported?3?5?$CFd?5Mb?$AA@=007dda70
// @ref ??_C@_0BJ@OCBA@Profile?3?5VRAM?3?$CFd?5?$CI?$CFdMb?$CJ?6?$AA@=007dda54
// @ref ??_C@_0BF@IIGP@VRAM?5reported?3?5?$CFd?5Mb?$AA@=007dda3c
// @ref ??_C@_0CO@IOGA@Profile?3?5VRAM?5speed?3?$CFd?5?$CI?$CFd?5blits@=007dda0c
// @ref ??_C@_0BF@DKGK@?$CFd?5blits?5per?5second?6?$AA@=007dd9f4
// @ref ??_C@_0CC@HNIH@Overall?5performance?5profile?5?$DN?5?$CFd@=007dd9d0
// @ref ??_C@_0N@JEHA@Profile?3?5?$CFd?6?$AA@=007dd9c0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0

// Rates the machine once from 1 to 10 by the lowest of its CPU, RAM, video memory and video
// blit speed ratings, writing each finding into the system texts; later calls return the rating.
int __fastcall Get_Performance_Profile()
{
    if (unknown_performance_profile_7db564 == -1) {
        unknown_profile_text_a4127c[0] = 0;
        unknown_profile_cpu_text_a411fc[0] = 0;
        unknown_profile_ram_text_a41388[0] = 0;
        unknown_profile_vram_text_a41308[0] = 0;
        unknown_profile_blit_text_a41408[0] = 0;

        int type = Get_CPU_Type();
        int mhz = Get_CPU_Speed();
        int cpu = 5;
        switch (type) {
        case -1:
            break;
        case 3:
        case 5:
            cpu = mhz / 100 + 1;
            break;
        case 4:
        case 7:
            cpu = mhz / 100 + 2;
            break;
        case 6:
            cpu = mhz / 100 + 3;
            break;
        default:
            cpu = 1;
            break;
        }
        Debug_Printf("Profile: CPU:%d (%dMhz %s)\n", cpu, mhz, Get_CPU_Type_Name());
        sprintf(unknown_profile_cpu_text_a411fc, "CPU: %d Mhz %s", mhz, Get_CPU_Type_Name());

        MEMORYSTATUS status;
        status.dwLength = sizeof(status);
        GlobalMemoryStatus(&status);
        int ram = 2;
        unsigned int megabytes = (status.dwTotalPhys + 0xA0000) >> 20;
        if (megabytes >= 64) {
            ram = 5;
        }
        if (megabytes >= 128) {
            ram += 2;
        }
        if (megabytes == 256) {
            ram += 2;
        } else if (megabytes > 256) {
            ram = 10;
        }
        Debug_Printf("Profile: RAM:%d (%dMb)\n", ram, megabytes);
        sprintf(unknown_profile_ram_text_a41388, "RAM reported: %d Mb", megabytes);

        megabytes = 4;
        int vram = 5;
        if (DirectDrawObject != 0) {
            DDCAPS caps;
            caps.dwSize = sizeof(caps);
            if (DirectDrawObject->GetCaps(&caps, 0) == 0) {
                unsigned int memory = caps.dwVidMemTotal > caps.dwVidMemFree ? caps.dwVidMemTotal : caps.dwVidMemFree;
                megabytes = (memory + 0xFFFFF) >> 20;
            }
        }
        if (megabytes >= 32) {
            vram = 10;
        } else if (megabytes >= 16) {
            vram = 9;
        } else if (megabytes >= 8) {
            vram = 7;
        } else if (megabytes >= 4) {
            vram = 5;
        } else if (megabytes <= 2) {
            vram = 3;
        }
        Debug_Printf("Profile: VRAM:%d (%dMb)\n", vram, megabytes);
        sprintf(unknown_profile_vram_text_a41308, "VRAM reported: %d Mb", megabytes);

        int speed = 5;
        int blits = 0;
        if (unknown_surface_839944 != 0 && ((DSurface *)unknown_surface_839944)->Is_Video_Ram()
            && !((DSurface *)unknown_surface_839958)->Is_Video_Ram()) {
            Rect area = unknown_surface_839944->Get_Rect();
            Rect other = unknown_surface_839958->Get_Rect();
            if (area.Width >= other.Width) {
                area.Width = other.Width;
            }
            if (area.Height >= other.Height) {
                area.Height = other.Height;
            }
            if (area.Width >= 480) {
                area.Width = 480;
            }
            if (area.Height >= 400) {
                area.Height = 400;
            }
            for (int index = 0; index < 4; index++) {
                unknown_surface_839944->Copy_From(area, *unknown_surface_839958, area, false, true);
                unknown_surface_839958->Copy_From(area, *unknown_surface_839944, area, false, true);
                Sleep(0);
            }
            DWORD start = timeGetTime();
            if ((start & 0xFF000000) != 0xFF) {
                unknown_surface_839944->Copy_From(area, *unknown_surface_839958, area, false, true);
                unknown_surface_839958->Copy_From(area, *unknown_surface_839944, area, false, true);
                blits++;
                while (timeGetTime() - start <= 1000 && blits <= 5000) {
                    unknown_surface_839944->Copy_From(area, *unknown_surface_839958, area, false, true);
                    unknown_surface_839958->Copy_From(area, *unknown_surface_839944, area, false, true);
                    blits++;
                }
                speed = blits / 4 < 1 ? 1 : blits / 4;
            }
        }
        Debug_Printf("Profile: VRAM speed:%d (%d blits per second)\n", speed, blits * 2);
        sprintf(unknown_profile_blit_text_a41408, "%d blits per second\n", blits * 2);

        unknown_performance_profile_7db564 = cpu;
        if (unknown_performance_profile_7db564 >= ram) {
            unknown_performance_profile_7db564 = ram;
        }
        if (unknown_performance_profile_7db564 >= vram) {
            unknown_performance_profile_7db564 = vram;
        }
        if (unknown_performance_profile_7db564 >= speed) {
            unknown_performance_profile_7db564 = speed;
        }
        Debug_Printf("Overall performance profile = %d\n", unknown_performance_profile_7db564);
        sprintf(unknown_profile_text_a4127c, "Profile: %d\n", unknown_performance_profile_7db564);
    }
    return unknown_performance_profile_7db564;
}
