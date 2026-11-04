// void __fastcall Motion_Capture() -- 0x0053F490
// Purpose: with motion capture on, grabs the game window's client area (less
// the screen shake) into the next surface of a Rules MovieTime minute
// sequence; when the sequence is full, writes every frame as capNNNN.pcx.
// @ref ?Debug_MotionCapture@@3_NA=00a40d09
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Write_PCX_File@@YIHAAVFileClass@@AAVSurface@@PAVPaletteClass@@@Z=007698c0
// @ref _sprintf=007820f4
// @ref ??_C@_0M@CBID@cap?$CF04d?4pcx?$AA@=007dfb78
// @ref _?$S50@?4??Motion_Capture@@YIXXZ@4EA=00a6eb80
// @ref _?_array@?4??Motion_Capture@@YIXXZ@4PAPAVSurface@@A=00a6ebd4
// @ref _?_seqsize@?4??Motion_Capture@@YIXXZ@4HA=00a6ebb0
// @ref _?_sequence@?4??Motion_Capture@@YIXXZ@4HA=00a6ebd8
// @ref ?Can_Lock@Surface@@UAE_NHH@Z=00411270
// @ref ?Unknown_Slot26@Surface@@UAE_NUPoint2D@@@Z=00411280
// @ref ?Get_Rect@Surface@@UAE?AVRect@@XZ=00411290
// @ref ?Get_Width@Surface@@UAEHXZ=004112c0
// @ref ?Get_Height@Surface@@UAEHXZ=004112d0
// @ref ?Lock@XSurface@@UAEPAXUPoint2D@@@Z=004112e0
// @ref ?Unlock@XSurface@@UAE_NXZ=004112f0
// @ref ?Is_Locked@XSurface@@UAE_NXZ=00411300
// @ref ?Is_Direct_Draw@XSurface@@UAE_NXZ=00411310
// @ref ??_GXSurface@@UAEPAXI@Z=00411320
// @ref ?Is_Direct_Draw@Surface@@UAE_NXZ=00411340
// @ref ??_GSurface@@UAEPAXI@Z=00411350
// @ref ?Lock@BSurface@@UAEPAXUPoint2D@@@Z=00411370
// @ref ?Bytes_Per_Pixel@BSurface@@UAEHXZ=004113b0
// @ref ?Stride@BSurface@@UAEHXZ=004113c0
// @ref ??_GBSurface@@UAEPAXI@Z=004113d0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_string.hpp"
#include "shared/rules.hpp"
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/palette.hpp"

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
int __fastcall Write_PCX_File(FileClass &file, Surface &pic, PaletteClass *palette);
extern bool Debug_MotionCapture;

void __fastcall Motion_Capture()
{
    if (Debug_MotionCapture) {
        static Surface **_array = 0;
        static int _sequence = 0;
        static int _seqsize = Rules->MovieTime * 900.0;

        if (_array == 0) {
            _array = new Surface *[_seqsize];
            memset(_array, '\0', _seqsize * sizeof(Surface *));
        }

        if (_array == 0) {
            Debug_MotionCapture = false;
        }

        RECT client_rect;
        GetClientRect(MainWindow, &client_rect);

        POINT screen_pt;
        screen_pt.x = client_rect.left;
        screen_pt.y = client_rect.top;
        if (!ClientToScreen(MainWindow, &screen_pt)) {
            return;
        }

        POINT screen_pt2;
        screen_pt2.x = client_rect.right;
        screen_pt2.y = client_rect.bottom;
        if (!ClientToScreen(MainWindow, &screen_pt2)) {
            return;
        }

        Rect rect(screen_pt.x, screen_pt.y, client_rect.right, client_rect.bottom);

        if (Map.ShakeX != 0 || Map.ShakeY != 0) {
            if (Map.ShakeX > 0) {
                rect.X += Map.ShakeX;
                rect.Width -= Map.ShakeX;
            } else if (Map.ShakeX < 0) {
                rect.Width += Map.ShakeX;
            }
            if (Map.ShakeY > 0) {
                rect.Y += Map.ShakeY;
                rect.Height -= Map.ShakeY;
            } else if (Map.ShakeY < 0) {
                rect.Height += Map.ShakeY;
            }
        }

        if (_sequence < _seqsize) {
            if (_array[_sequence] == 0) {
                _array[_sequence] = new BSurface(rect.Width, rect.Height, 2);
            }

            if (_array[_sequence] != 0) {
                _array[_sequence]->Copy_From(Rect(0, 0, rect.Width, rect.Height), *unknown_surface_839950, rect, false, true);
            }
            _sequence++;

        } else {
            Debug_MotionCapture = false;

            DSurface temp_page(rect.Width, rect.Height, false);

            for (int index = 0; index < _sequence; index++) {
                char filename[30];
                sprintf(filename, "cap%04d.pcx", index);
                CCFileClass file(filename);
                temp_page.Copy_From(*_array[index], false, true);
                Write_PCX_File(file, temp_page, &unknown_palette_837e10);
            }

            _sequence = 0;
        }
    }
}
