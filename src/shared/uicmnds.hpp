// UICmnds.cpp (0x006F55F0-0x006F8BDF; assert string "D:\Ra2\UICmnds.cpp"): the
// user-interface commands over the selection and the control groups. Shared
// views and inline helpers of its functions; names are hypotheses.
#ifndef RA2_SHARED_UICMNDS_HPP
#define RA2_SHARED_UICMNDS_HPP

// Vector members stay declarations (their bodies are kept elsewhere) except the
// accessors and Add this unit expands; the guard keeps later headers from
// widening that.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/object.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/event.hpp"

// Whether a techno's house is the player's side (hypothesis): its flag +0x135 in a
// single-player game, else the house's slot 0x004F52B0 answer.
inline bool Is_Player_Side(TechnoClass *techno)
{
    if (unknown_game_mode_a3d298 == 0) {
        return techno->House->unknown_135;
    }
    return techno->House->Unknown_004F52B0();
}

// A pointer list as the callbacks see it (DynamicVectorClass<T *>: Items at +4,
// Count at +0x10).
struct UnknownPointerList {
    int unknown_00;
    void **Items;
    int unknown_08;
    int unknown_0c;
    int Count;
    // Removes the item at index, shifting the later ones down (inline in 0x006F7970).
    bool Delete(int index)
    {
        if (index < Count) {
            Count--;
            for (int shift = index; shift < Count; shift++) {
                Items[shift] = Items[shift + 1];
            }
            return true;
        }
        return false;
    }
};
typedef void (__fastcall *UnknownVisit)(void *item, int argument);
typedef bool (__fastcall *UnknownTest)(void *item, int argument);

// The screen object at 0x008324E0 is `Map` (shared/map_view.hpp); the
// command code calls DisplayClass members on it.

// The on-screen message list (0x00A3DC70).
struct UnknownMessageList {
    void Add_Message(int arg1, int arg2, wchar_t const *text, int color, int style, int delay, int arg7);
};
extern UnknownMessageList unknown_messages_a3dc70;

// Shows a message in the player's color (an inline copy of 0x006F58E0).
inline void Show_Message(wchar_t const *text, int delay)
{
    int color = 3;
    if (unknown_player_a35db4 != 0) {
        color = unknown_player_a35db4->ColorSchemeIndex;
    }
    unknown_messages_a3dc70.Add_Message(0, 0, text, color, 0x4046, delay, 1);
}

// The constructor of the techno list the command code builds: empty, growing by 10.
// The VectorClass part is expanded inline in the small functions and called
// (0x0040BC10) in the larger ones.
template <>
inline DynamicVectorClass<TechnoClass *>::DynamicVectorClass(unsigned size, TechnoClass *const *array)
    : VectorClass<TechnoClass *>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}

// The same for the name lists (DynamicVectorClass<char const *>).
template <>
inline DynamicVectorClass<char const *>::DynamicVectorClass(unsigned size, char const *const *array)
    : VectorClass<char const *>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}

// The selection list behind the pointer at 0x0083996C.
struct UnknownSelection {
    int Count();                        // 0x006AC7B0
    ObjectClass *Get(int index);        // 0x006AC7C0
    void Unknown_006AAD40();            // 0x006AAD40 (hypothesis: refreshes the selection display)
    void Unknown_006AAD70();            // 0x006AAD70 (called first by the select-combatants command 0x006F6D00)
};
extern UnknownSelection *unknown_selected_83996c;
// Whether the player-side technos in group (1-based) are exactly the selected ones (0x006F5E80).
bool __fastcall Unknown_006F5E80(int group);
// The frame before which the player may not cheer again (0x00AC134C).
extern int unknown_cheer_frame_ac134c;
// Whether a player-side techno in play has the type name (0x006F7190).
int __fastcall Unknown_006F7190(TechnoClass *techno, char const *name);

extern bool unknown_flag_ac1330;
extern bool unknown_flag_ac133c;

#endif
