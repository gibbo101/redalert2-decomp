// Cell FootClass::unknown_4cbb40(int radius) (0x004CBB40)
// TibSun Search_For_Tiberium_Weighted: the cells of each ring that pass
// 0x004CB6D0, weighted by their tiberium value scaled by the ring's share
// per harvester, then one weighted random pick.
// The local distribution's vector instantiation (COMDAT copies of the
// accepted members and vtables at 0x004CDF10-0x004CEB30, 0x007A17D4, 0x007A17FC):
// @ref ?Fetch@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UBE?AV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@H@Z=004cdf10
// @ref ??8?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UBE_NABV0@@Z=004ce4f0
// @ref ?Resize@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAE_NHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce550
// @ref ?Clear@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEXXZ=004ce660
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHABV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce6a0
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce6f0
// @ref ??0?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@QAE@IPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce710
// @ref ?Clear@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEXXZ=004ce7c0
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce800
// @ref ?Resize@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAE_NHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce820
// @ref ??1?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAE@XZ=004ce940
// @ref ?Add@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@QAE_NABV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce950
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHABV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce9b0
// @ref ??_G?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEPAXI@Z=004cea90
// @ref ??_E?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEPAXI@Z=004cea90
// @ref ??_E?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAEPAXI@Z=004ceaf0
// @ref ??_G?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEPAXI@Z=004ceb30
// @ref ??_E?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEPAXI@Z=004ceb30
// @ref ??_7?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@6B@=007a17d4
// @ref ??_7?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@6B@=007a17fc
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/discrete_distribution.hpp"

// The cell's tiberium value (CellClass::Get_Tiberium_Value 0x0047A230) read
// through the shared/techno.hpp cell view; the distribution holds CellClass
// pointers. One inline site per read, as the original's budget shows (the
// vector constructor 0x004CE710 and the early return's Clear 0x004CE660 stay
// out of line only with them).
inline int Tiberium_Value(CellClass *cell)
{
    return ((UnknownCellClass *)cell)->Unknown_0047A230();
}

Cell FootClass::unknown_4cbb40(int radius)
{
    DiscreteDistributionClass<CellClass> celldist;

    Cell center = Coord_Cell(Center_Coord());
    if (((UnknownCellClass *)&Map[center])->unknown_ec == 5) {
        return center;
    }

    int numharv = House->unknown_5470.unknown_func_491d10(House->Unknown_004EF6F0(Rules->unknown_9ec)->ArrayIndex);
    if (numharv < 1) {
        numharv = 1;
    }

    double weight;
    for (int ring = 1; ring < radius; ring++) {
        int ringspan = ring * 3;
        int share = ringspan / numharv;
        bool northrun = false;
        bool southrun = false;
        bool westrun = false;
        bool eastrun = false;
        int divisor = 1;
        if (share >= 1) {
            divisor = share;
        }
        double scale = 1.0 / (double)divisor;
        for (int x = -ring; x <= ring; x++) {
            Cell cell;
            cell = Cell(x, -ring) + center;
            if (unknown_4cb6d0(cell)) {
                if (!northrun) {
                    CellClass *cptr = &Map[cell];
                    if (Tiberium_Value(cptr) * scale < 1.0) {
                        weight = 1.0;
                    } else {
                        weight = Tiberium_Value(cptr) * scale;
                    }
                    int intweight = (int)weight;
                    northrun = true;
                    celldist.Add(cptr, intweight);
                }
            } else {
                northrun = false;
            }

            cell = Cell(x, ring) + center;
            if (unknown_4cb6d0(cell)) {
                if (!southrun) {
                    CellClass *cptr = &Map[cell];
                    if (Tiberium_Value(cptr) * scale < 1.0) {
                        weight = 1.0;
                    } else {
                        weight = Tiberium_Value(cptr) * scale;
                    }
                    int intweight = (int)weight;
                    southrun = true;
                    celldist.Add(cptr, intweight);
                }
            } else {
                southrun = false;
            }

            cell = Cell(-ring, x) + center;
            if (unknown_4cb6d0(cell)) {
                if (!westrun) {
                    CellClass *cptr = &Map[cell];
                    if (Tiberium_Value(cptr) * scale < 1.0) {
                        weight = 1.0;
                    } else {
                        weight = Tiberium_Value(cptr) * scale;
                    }
                    int intweight = (int)weight;
                    westrun = true;
                    celldist.Add(cptr, intweight);
                }
            } else {
                westrun = false;
            }

            cell = Cell(ring, x) + center;
            if (unknown_4cb6d0(cell)) {
                if (!eastrun) {
                    CellClass *cptr = &Map[cell];
                    if (Tiberium_Value(cptr) * scale < 1.0) {
                        weight = 1.0;
                    } else {
                        weight = Tiberium_Value(cptr) * scale;
                    }
                    int intweight = (int)weight;
                    eastrun = true;
                    celldist.Add(cptr, intweight);
                }
            } else {
                eastrun = false;
            }
        }
    }

    CellClass *cptr = celldist.Sample();
    if (cptr != 0) {
        return ((UnknownCellClass *)cptr)->unknown_24;
    }
    return unknown_geometry_k;
}
