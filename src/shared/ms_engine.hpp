// MSEngine: the main-screen animation engine (RTTI vtable 0x007A7028, three
// slots; WorldDominationTour::Selection derives from it). Unit 0x005B2BC0-
// 0x005B3F1F (MSEngine.cpp by the link order): `_$E` of the per-unit empty
// rect, the class, then its DynamicVectorClass<MSAnim *> and
// DynamicVectorClass<MSSfx *> instances.
//
// It owns the animations (deleted through the virtual destructor) and the
// named sound effects, and keeps a list of up to 20 dirty rectangles that
// Draw collects from the animations, Add_Rect merges (an overlapping
// rectangle is replaced by the union; when full, the entry whose union with
// the new one is smallest), and Blit_Rects copies to the screen surface at
// the window's client origin with the mouse drawn over it.
//
// Evidenced: layout (constructor 0x005B2BE0, destructor 0x005B2C70), the
// debug strings "MSEngine - Pausing animations" / "Sleeping" / "Resuming
// animations". Method names other than those implied by the strings, and
// every unknown_ global, are hypotheses.
#ifndef RA2_SHARED_MS_ENGINE_HPP
#define RA2_SHARED_MS_ENGINE_HPP

#include "shared/mouse.hpp"
#include "shared/rect.hpp"
#include "shared/surface.hpp"
// The engine's lists use the full container implementation (members are
// emitted where used, as in the original unit).
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/ms_anim.hpp"
#include "shared/wwmouse.hpp"
#include "shared/win32_api.hpp"

// A named sound effect (0x0C bytes; MSSfx.cpp at 0x005B69B0).
class MSSfx {
public:
    MSSfx(char const *name, int unknown2);   // 0x005B69B0 (copies the name only when sound is available)
    ~MSSfx();                                // 0x005B69E0
    void Play(int volume);                   // 0x005B69F0

    char *Name;             // +0x00
    int unknown_04;         // +0x04
    bool unknown_08;        // +0x08
};

class MSEngine {
public:
    MSEngine();                                                 // 0x005B2BE0
    virtual ~MSEngine();                                        // slot 0 (+0x00) 0x005B2C70
    virtual void Unknown_Slot1(Surface *surface) {}             // slot 1 (+0x04) after a full redraw; kept copy 0x0058FD90
    virtual void Unknown_Slot2();                               // slot 2 (+0x08) 0x005B3830 once per frame

    int Add_Anim(MSAnim *anim);                                 // 0x005B2D60 index, or -1
    void Replace_Anim(MSAnim *anim, MSAnim *old);               // 0x005B2DD0 inserts after old, then removes old
    void Remove_Anim(MSAnim *anim);                             // 0x005B2EC0
    void Wait_For(MSAnim *anim, unsigned time);                 // 0x005B2F30
    void Redraw();                                              // 0x005B2F90
    void Draw(Surface *surface);                                // 0x005B2FB0
    void Add_Rect(Rect const &rect);                            // 0x005B3110
    void Blit_Rects(Surface *surface);                          // 0x005B33A0
    void Blit_Rect(Surface *surface, Rect const &rect);         // 0x005B3490
    void Run(int frames);                                       // 0x005B3550
    void Check_Focus();                                         // 0x005B3670
    bool Add_Sfx(char const *name, int unknown2);               // 0x005B3710
    void Play_Sfx(char const *name, int volume);                // 0x005B3790
    void Broadcast(int unknown1);                               // 0x005B3800 slot 8 of every animation

    int RectCount;                          // +0x04 dirty rectangles in use
    VectorClass<Rect> Rects;                // +0x08 20 entries
    DynamicVectorClass<MSAnim *> Anims;     // +0x18
    DynamicVectorClass<MSSfx *> Sfx;        // +0x30
};

extern bool unknown_redraw_8523dc;              // 0x008523DC set by Redraw: Draw clears and repaints everything
extern bool unknown_flag_a40d28;                // 0x00A40D28 application active (focus)
extern float unknown_volume_a40b44;             // 0x00A40B44 sound effect volume scale
extern Surface *unknown_surface_839950;         // 0x00839950 screen
extern Surface *unknown_surface_839958;         // 0x00839958 background
extern HWND MainWindow;                         // 0x00B263D8

void unknown_481fb0();                          // 0x00481FB0 once per frame
void unknown_4961d0();                          // 0x004961D0 once per frame
void unknown_5b5ee0();                          // 0x005B5EE0 once per frame and while inactive
#include "shared/sound_available.hpp"
#include "shared/debug_printf.hpp"
extern "C" int __cdecl _stricmp(char const *left, char const *right);  // 0x00781F20

#endif
