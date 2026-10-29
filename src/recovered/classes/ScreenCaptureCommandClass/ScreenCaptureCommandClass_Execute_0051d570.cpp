// void ScreenCaptureCommandClass::Execute(int key) const -- 0x0051D570
// Copies the game window's client area into the 0x00839954 surface and
// writes it to the first free SCRN%04d.pcx (Write_PCX_File).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/dsurface.hpp"
#include "shared/mouse.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/palette.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Write_PCX_File@@YIHAAVFileClass@@AAVSurface@@PAVPaletteClass@@@Z=007698c0
// @ref _sprintf=007820f4
// @ref ??_C@_0N@EBC@SCRN?$CF04d?4pcx?$AA@=007dd488

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
int __fastcall Write_PCX_File(FileClass &file, Surface &pic, PaletteClass *palette);

void ScreenCaptureCommandClass::Execute(int key) const
{
    RECT client;
    if (GetClientRect(MainWindow, &client)) {
        POINT topleft;
        topleft.x = client.left;
        topleft.y = client.top;
        if (ClientToScreen(MainWindow, &topleft)) {
            POINT bottomright;
            bottomright.x = client.right;
            bottomright.y = client.bottom;
            if (ClientToScreen(MainWindow, &bottomright)) {
                Rect area(topleft.x, topleft.y, client.right + 1, client.bottom + 1);
                if (area.Width >= unknown_surface_839954->Get_Width()) {
                    area.Width = unknown_surface_839954->Get_Width();
                }
                if (area.Height >= unknown_surface_839954->Get_Height()) {
                    area.Height = unknown_surface_839954->Get_Height();
                }
                WWMouse->Hide_Mouse();
                int width = unknown_surface_839954->Get_Width();
                int height = unknown_surface_839954->Get_Height();
                Rect full(0, 0, width, height);
                unknown_surface_839954->Copy_From(full, *unknown_surface_839950, area, false, true);
                WWMouse->Show_Mouse();
                char filename[128];
                int index = -1;
                bool exists;
                do {
                    index++;
                    sprintf(filename, "SCRN%04d.pcx", index);
                    exists = CCFileClass(filename).Is_Available();
                } while (exists);
                CCFileClass file(filename);
                Write_PCX_File(file, *unknown_surface_839954, &unknown_palette_837e10);
            }
        }
    }
}
