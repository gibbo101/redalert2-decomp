// UnknownPathEstimator::Unknown_0042A590() (0x0042A590): records, for each
// layer, the subzone pairs around the start cell.
#include "shared/path_estimator.hpp"
#include "shared/map_view.hpp"
// @ref ??0?$VectorClass@G@@QAE@IPBG@Z=0042b620
// @ref ??_7?$DynamicVectorClass@G@@6B@=0079c554
// @ref ??_7?$VectorClass@G@@6B@=0079c534
// @ref ??_E?$DynamicVectorClass@G@@UAEPAXI@Z=0042b4c0
// @ref ??_G?$DynamicVectorClass@G@@UAEPAXI@Z=0042b4c0
// @ref ??8?$VectorClass@G@@UBE_NABV0@@Z=0042b170
// @ref ?Resize@?$DynamicVectorClass@G@@UAE_NHPBG@Z=0042b2f0
// @ref ?Clear@?$DynamicVectorClass@G@@UAEXXZ=0042ae60
// @ref ?ID@?$DynamicVectorClass@G@@UAEHABG@Z=0042b3a0
// @ref ?ID@?$DynamicVectorClass@G@@UAEHPBG@Z=0042ae90
// @ref ?Fetch@?$VectorClass@G@@UBEGH@Z=0042aeb0
// @ref ??_E?$VectorClass@G@@UAEPAXI@Z=0042b470
// @ref ??_G?$VectorClass@G@@UAEPAXI@Z=0042b470
// @ref ?Resize@?$VectorClass@G@@UAE_NHPBG@Z=0042b1b0
// @ref ?Clear@?$VectorClass@G@@UAEXXZ=0042b260
// @ref ?ID@?$VectorClass@G@@UAEHABG@Z=0042b290
// @ref ?ID@?$VectorClass@G@@UAEHPBG@Z=0042b2d0
// @ref ?Unknown_00565EB0@MapClass@@QAE_NAAVCellClass@@HPAV?$DynamicVectorClass@G@@H@Z=00565eb0

// The cell's element of Map's +0x6C array: its subzone in each path estimator layer (a MapClass
// member inline here changes the scheduling of units that only see shared/map_view.hpp).
inline unsigned short *Cell_Subzones(Cell const &cell)
{
    return (unsigned short *)(Map.unknown_6c + Map.Unknown_0054FAB0(cell) * 10);
}

void UnknownPathEstimator::Unknown_0042A590(int arg)
{
    unsigned short *subzones = Cell_Subzones(unknown_70);
    for (int layer = 0; layer < 3; layer++) {
        unsigned short subzone = subzones[layer];
        DynamicVectorClass<unsigned short> list;
        list.Clear();
        if (Map.Unknown_00565EB0(Map[unknown_70], layer, &list, arg)) {
            Unknown_0042A840(Cell_Subzones(unknown_70)[layer], layer);
            continue;
        }
        for (int index = list.Count() - 1; index >= 0; index--) {
            Unknown_0042A7D0(subzone, list[index], layer);
        }
    }
}
