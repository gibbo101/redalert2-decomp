// bool __fastcall Allocate_Surfaces(Rect *hidden, Rect *composite, Rect *tile, Rect *sidebar, bool hidden_first)
// -- 0x00519500. Body 0x00519500-0x0051995D (1118 bytes, nop padding to 0x00519960).
// Declared in shared/main_opt.hpp (its last parameter is named `clear` there).
#include "shared/rect.hpp"
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"
#include "shared/options.hpp"
#include "shared/main_opt.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_tile_sysmem_7f4cc4@@3_NA=007f4cc4
// @ref ??0DSurface@@QAE@HHE@Z=004aa4a0
// @ref ??_C@_0BI@EACK@TileSurface?5?$CI?$CFdx?$CFd?$CJ?5?$CFs?6?$AA@=007dd7a0
// @ref ??_C@_0BJ@CLI@Allocating?5new?5surfaces?6?$AA@=007dd890
// @ref ??_C@_0BK@BKHD@HiddenSurface?5?$CI?$CFdx?$CFd?$CJ?5?$CFs?6?$AA@=007dd7d8
// @ref ??_C@_0BL@MPDM@SidebarSurface?5?$CI?$CFdx?$CFd?$CJ?5?$CFs?6?$AA@=007dd748
// @ref ??_C@_0BN@KEIF@CompositeSurface?5?$CI?$CFdx?$CFd?$CJ?5?$CFs?6?$AA@=007dd7b8
// @ref ??_C@_0BN@PPPD@AlternateSurface?5?$CI?$CFdx?$CFd?$CJ?5?$CFs?6?$AA@=007dd728
// @ref ??_C@_0DM@OJEN@Moving?5TileSurface?5and?5Composite@=007dd764
// @ref ??_C@_0BG@PLCA@Deleting?5TileSurface?6?$AA@=007dd828
// @ref ??_C@_0BI@GOMM@Deleting?5HiddenSurface?6?$AA@=007dd85c
// @ref ??_C@_0BJ@GNMK@Deleting?5SidebarSurface?6?$AA@=007dd80c
// @ref ??_C@_0BL@BPEP@Deleting?5CompositeSurface?6?$AA@=007dd840
// @ref ??_C@_0BL@PKEH@Deleting?5AlternateSurface?6?$AA@=007dd874
// @ref ??_C@_04JDBJ@VRAM?$AA@=007dd804
// @ref ??_C@_0O@ODGN@SYSTEM?5MEMORY?$AA@=007dd7f4

extern bool unknown_tile_sysmem_7f4cc4;     // 0x007F4CC4 composite and tile surfaces may live in video memory

// The DSurface constructor's flag as the original passes it: an int 0 or 1 taken through an if.
static inline int Memory_Flag(bool system_memory)
{
    if (system_memory) {
        return 1;
    }
    return 0;
}

// Frees the five off-screen surfaces and makes new ones for the given rectangles: the hidden surface
// (before the others when hidden_first, else after the sidebar), composite and tile (both moved to system
// memory when only one of them got video memory), sidebar (video memory only with AllowVRAMSidebar)
// and the alternate surface in system memory (TS's Allocate_Surfaces).
bool __fastcall Allocate_Surfaces(Rect *hidden, Rect *composite, Rect *tile, Rect *sidebar, bool hidden_first)
{
    Debug_Printf("Allocating new surfaces\n");

    if (unknown_surface_839958 != 0) {
        Debug_Printf("Deleting AlternateSurface\n");
        delete unknown_surface_839958;
        unknown_surface_839958 = 0;
    }
    if (unknown_surface_839954 != 0) {
        Debug_Printf("Deleting HiddenSurface\n");
        delete unknown_surface_839954;
        unknown_surface_839954 = 0;
    }
    if (unknown_surface_839964 != 0) {
        Debug_Printf("Deleting CompositeSurface\n");
        delete unknown_surface_839964;
        unknown_surface_839964 = 0;
    }
    if (unknown_surface_839944 != 0) {
        Debug_Printf("Deleting TileSurface\n");
        delete unknown_surface_839944;
        unknown_surface_839944 = 0;
    }
    if (unknown_surface_839948 != 0) {
        Debug_Printf("Deleting SidebarSurface\n");
        delete unknown_surface_839948;
        unknown_surface_839948 = 0;
    }

    bool tile_sysmem = !unknown_tile_sysmem_7f4cc4;
    bool sidebar_sysmem = !Options.AllowVRAMSidebar;

    if (hidden_first && hidden->Is_Valid()) {
        unknown_surface_839954 = new DSurface(hidden->Width, hidden->Height, false);
        unknown_surface_839954->Fill(0);
        Debug_Printf("HiddenSurface (%dx%d) %s\n", hidden->Width, hidden->Height,
                     ((DSurface *)unknown_surface_839954)->Is_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
    }

    if (composite->Is_Valid()) {
        unknown_surface_839964 = new DSurface(composite->Width, composite->Height, Memory_Flag(tile_sysmem));
        unknown_surface_839964->Fill(0);
        Debug_Printf("CompositeSurface (%dx%d) %s\n", composite->Width, composite->Height,
                     ((DSurface *)unknown_surface_839964)->Is_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
    }

    if (tile->Is_Valid()) {
        unknown_surface_839944 = new DSurface(tile->Width, tile->Height, Memory_Flag(tile_sysmem));
        unknown_surface_839944->Fill(0);
        Debug_Printf("TileSurface (%dx%d) %s\n", tile->Width, tile->Height,
                     ((DSurface *)unknown_surface_839944)->Is_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
    }

    if (unknown_surface_839964 != 0 && unknown_surface_839944 != 0) {
        bool composite_vram = ((DSurface *)unknown_surface_839964)->Is_Video_Ram();
        bool tile_vram = ((DSurface *)unknown_surface_839944)->Is_Video_Ram();
        if (composite_vram ^ tile_vram) {
            delete unknown_surface_839964;
            delete unknown_surface_839944;
            Debug_Printf("Moving TileSurface and CompositeSurface into system memory\n");
            unknown_surface_839964 = new DSurface(composite->Width, composite->Height, true);
            unknown_surface_839944 = new DSurface(tile->Width, tile->Height, true);
        }
    }

    if (sidebar->Is_Valid()) {
        unknown_surface_839948 = new DSurface(sidebar->Width, sidebar->Height, Memory_Flag(sidebar_sysmem));
        unknown_surface_839948->Fill(0);
        Debug_Printf("SidebarSurface (%dx%d) %s\n", sidebar->Width, sidebar->Height,
                     ((DSurface *)unknown_surface_839948)->Is_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
    }

    if (!hidden_first && hidden->Is_Valid()) {
        unknown_surface_839954 = new DSurface(hidden->Width, hidden->Height, false);
        unknown_surface_839954->Fill(0);
        Debug_Printf("HiddenSurface (%dx%d) %s\n", hidden->Width, hidden->Height,
                     ((DSurface *)unknown_surface_839954)->Is_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
    }

    if (hidden->Is_Valid()) {
        unknown_surface_839958 = new DSurface(hidden->Width, hidden->Height, true);
        unknown_surface_839958->Fill(0);
        Debug_Printf("AlternateSurface (%dx%d) %s\n", hidden->Width, hidden->Height,
                     ((DSurface *)unknown_surface_839958)->Is_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
    }

    return true;
}
