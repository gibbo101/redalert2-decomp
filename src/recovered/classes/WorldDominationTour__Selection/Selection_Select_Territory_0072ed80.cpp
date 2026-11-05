#include "shared/wdt_selection.hpp"
WideString __fastcall operator+(unsigned short const *left, WideString const &right);

namespace WorldDominationTour {
bool Selection::Select_Territory(rc_ptr<Territory> const &territory)
{
    bool selected = unknown_50.Get() != 0;
    if (territory.Get() == unknown_464.Get()) return selected;
    if (unknown_464.Get()) {
        if (unknown_50.Get()) unknown_50.Set(0);
        unknown_464->Show_Highlight(false, this);
        MSShapeAnim *target = (MSShapeAnim *)unknown_464->Get_unknown_2c();
        if (target) {
            target->Set_End_Frame(TargetDividingFrame - 1);
            target->Set_Start_Frame(0);
            target->Set_Frame(0);
        }
    }
    unknown_464 = territory;
    if (!unknown_464.Get()) {
        Show_Campaign();
        TheVoices.Say_List(1, false, 30);
        return selected;
    }
    selected = false;
    WideString description;
    WideString options;
    int index = unknown_464->Get_Index();
    int owner = unknown_488->Owner_Of(index);
    int kind = 2;
    if (owner != 1 && owner != 0) kind = TheCampaign->Player_Faction() != owner;
    TheVoices.Say(3, kind, false, false, 30);
    switch (owner) {
    case 1: Set_Tooltip(StringTable::Load_String("WDT:TerritorySelDispToolTip", 0, "D:\\Ra2\\WDTSel.cpp", 0x2b5)); break;
    case 2: Set_Tooltip(StringTable::Load_String("WDT:AlliedHeldTooltip", 0, "D:\\Ra2\\WDTSel.cpp", 0x2ad)); break;
    case 3: Set_Tooltip(StringTable::Load_String("WDT:SovietHeldTooltip", 0, "D:\\Ra2\\WDTSel.cpp", 0x2b1)); break;
    default: Set_Tooltip(StringTable::Load_String("WDT:TerritorySelectToolTip", 0, "D:\\Ra2\\WDTSel.cpp", 0x2b9)); break;
    }
    unknown_464->Show_Highlight(true, this);
    if (TheCampaign->Properties->Last_Conflict() == unknown_450) {
        ConflictCursor cursor(TheCampaign->Conflicts);
        while (cursor) {
            rc_ptr<Conflict> const &conflict = *cursor;
            Conflict const *current = conflict.operator->();
            int id = unknown_464->Get_Index();
            if (current->Is_Territory(id)) break;
            cursor++;
        }
        if (cursor) {
            selected = true;
            unknown_50 = *cursor;
            description = (*cursor)->Describe_Options();
            options = description;
            MSShapeAnim *target = (MSShapeAnim *)territory->Get_unknown_2c();
            if (target) {
                target->Set_End_Frame(-1);
                target->Set_Start_Frame(TargetDividingFrame);
                target->Set_Frame(TargetDividingFrame);
            }
        }
    }
    WideString text = StringTable::Load_String("WDT:TerritoryPrefix", 0, "D:\\Ra2\\WDTSel.cpp", 0x2d7)
        + unknown_464->Name + StringTable::Load_String("WDT:TerritorySuffix", 0, "D:\\Ra2\\WDTSel.cpp", 0x2d7);
    if (options.Length() > 0) text += description;
    Set_Description(text, 0);
    return selected;
}
}
// @ref ??_C@_0BE@FGNO@WDT?3TerritorySuffix?$AA@=007fc5a8
// @ref ??_C@_0BE@OHDC@WDT?3TerritoryPrefix?$AA@=007fc594
// @ref ??_C@_0BG@FDFJ@WDT?3AlliedHeldTooltip?$AA@=007fc5d8
// @ref ??_C@_0BG@PPKO@WDT?3SovietHeldTooltip?$AA@=007fc5f0
// @ref ??_C@_0BM@MKJF@WDT?3TerritorySelDispToolTip?$AA@=007fc5bc
// @ref ??H@YI?AVWideString@@PBGABV0@@Z=00771380
// @ref ??_E?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEPAXI@Z=00726b20
// @ref ??B?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UBE_NXZ=00726ab0
// @ref ??E?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEAAV0@XZ=00726ef0
// @ref ??F?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEAAV0@XZ=00726f00
// @ref ??_7?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@6B@=007af054
// @ref ??_G?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEPAXI@Z=00726b20
