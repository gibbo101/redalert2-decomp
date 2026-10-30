// void ScoreClass::Do_Graphs() (0x006661E0)
// Sums the units and buildings lost by the player's side (the player and
// mutual allies) and by everyone else, logs them, and draws the buildings
// graph at 227 and the units graph at 283, the player's side first unless
// the player's side index is non-zero.
#include "shared/score.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
// @ref ??_C@_0CO@IDPO@Stats?3?5?$CFs?5?9?5UnitsLost?5?$CFld?0?5Build@=007f29f0
// @ref ??_C@_0EC@PNED@AllyUnits?5?$CFld?0?5AllyBuildings?5?$CFld@=007f29ac
// @ref ?Do_Graph@ScoreClass@@QAEXHHH@Z=00666320
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

void ScoreClass::Do_Graphs()
{
    int allyunits = 0;
    int allybuildings = 0;
    int enemyunits = 0;
    int enemybuildings = 0;
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *house = Houses[index];
        Debug_Printf("Stats: %s - UnitsLost %ld, BuildingsLost %ld\n", (char const *)house->Type->ID,
                     house->unknown_5360, house->unknown_53b4);
        if ((unknown_player_a35db4->Is_Ally(house) && house->Is_Ally(unknown_player_a35db4)) || unknown_player_a35db4 == house) {
            allyunits += house->unknown_5360;
            allybuildings += house->unknown_53b4;
        } else {
            enemyunits += house->unknown_5360;
            enemybuildings += house->unknown_53b4;
        }
        Debug_Printf("AllyUnits %ld, AllyBuildings %ld, EnemyUnits %ld, EnemyBldgs %ld\n",
                     allyunits, allybuildings, enemyunits, enemybuildings);
    }
    if (unknown_player_a35db4->Type->Side == 0) {
        Do_Graph(allybuildings, enemybuildings, 227);
        Do_Graph(allyunits, enemyunits, 283);
    } else {
        Do_Graph(enemybuildings, allybuildings, 227);
        Do_Graph(enemyunits, allyunits, 283);
    }
}
