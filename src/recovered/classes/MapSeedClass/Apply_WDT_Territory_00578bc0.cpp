#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/map_seed.hpp"
#include "shared/reference_counted.hpp"
class WDTTerritory;
template <> bool VectorClass<rc_ptr<WDTTerritory> >::Resize(int newsize, rc_ptr<WDTTerritory> const *array);
#include "shared/world_domination_tour.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/random2.hpp"
rc_ptr<WDTTerritory> __fastcall Get_WDT_Territory_00769690(int value);
// @ref ?Get_WDT_Territory_00769690@@=00769690
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
void MapSeedClass::Apply_WDT_Territory_00578bc0()
{
    rc_ptr<WDTTerritory> territory;
    if(unknown_game_mode_a3d298==4 && *(int const*)&unknown_session_a3d298.unknown_00[0x0c]==2)
        territory=Get_WDT_Territory_00769690(*(int const*)&unknown_session_a3d298.unknown_00[8]);
    if(territory.Get()) {
        unsigned short fixed_seed=*(unsigned short const*)territory->unknown_0c;
        Seed=fixed_seed==0 ? unknown_random_839218(0,0xffff) : fixed_seed;
        switch(territory->unknown_12) {
        case 0: Width=0; break;
        case 2: Width=2; break;
        case 3: Width=3; break;
        case 1: Width=1; break;
        default: Width=1; break;
        }
        switch(territory->unknown_13) {
        case 0: Height=0; break;
        case 2: Height=2; break;
        case 3: Height=3; break;
        case 1: Height=1; break;
        default: Height=1; break;
        }
        NumPlayers=4;
        switch((unsigned char)territory->unknown_15[0x1e-0x15]) {
        case 2: Time=0; break;
        case 1: Time=2; break;
        case 3: Time=3; break;
        case 0: Time=1; break;
        default: Time=1; break;
        }
        MapType=(unsigned char)territory->unknown_15[0x1c-0x15];
        Theater=(unsigned char)territory->unknown_15[0x1d-0x15];
        RegionSize=(unsigned char)territory->unknown_15[0x21-0x15];
        Accessibility=(unsigned char)territory->unknown_15[0x24-0x15];
        Ruggedness=(unsigned char)territory->unknown_15[0x27-0x15];
        WaterAmount=(unsigned char)territory->unknown_15[0x2a-0x15];
        Tiberium=(unsigned char)territory->unknown_15[0x2d-0x15];
        TiberiumLayout=(unsigned char)territory->unknown_15[0x30-0x15];
        Vegetation=(unsigned char)territory->unknown_15[0x33-0x15];
        UrbanPresence=(unsigned char)territory->unknown_15[0x36-0x15];
        Resources=*(int const*)&territory->unknown_15[0x18-0x15];
    }
}

// Real original auxiliary: VectorClass<rc_ptr<WDTTerritory>>::Resize
// RTTI table7AF2E8 slot2=72CBD0, zero source credit.
// Ordinary definition of the real RTTI-rooted Resize specialization. Its
// body is the unchanged shared implementation; no whole-class instantiation.
template <>
bool VectorClass<rc_ptr<WDTTerritory> >::Resize(int newsize, rc_ptr<WDTTerritory> const *array)
{
    typedef rc_ptr<WDTTerritory> T;
    if (newsize) {
        T *newptr;
        IsValid = false;
        if (!array) {
            newptr = new T[newsize];
        } else {
            newptr = new ((void *)array) T[newsize];
        }
        IsValid = true;
        if (!newptr) {
            return false;
        }
        if (Vector) {
            int copycount = (newsize < VectorMax) ? newsize : VectorMax;
            for (int index = 0; index < copycount; index++) {
                newptr[index] = Vector[index];
            }
            if (IsAllocated) {
                delete[] Vector;
                Vector = 0;
            }
        }
        Vector = newptr;
        VectorMax = newsize;
        IsAllocated = (Vector && !array);
    } else {
        Clear();
    }
    return true;
}
