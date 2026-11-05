// Tactical::Tactical() (0x006A24B0): the new view (Read_Scenario_INI). The
// members start cleared, the scroll points at the zero coordinate, the view
// rectangle as the empty header rectangle; the body clears the cells to
// redraw and the caption and builds the two projection matrices (TibSun
// Tactical::Tactical).
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
// @ref ??_7Tactical@@6BIPersistStream@@@=007ac570
// @ref ??_7Tactical@@6BIRTTITypeInfo@@@=007ac554
// @ref ??_7Tactical@@6BINoticeSink@@@=007ac54c
// @ref ??_7Tactical@@6BINoticeSource@@@=007ac544
// @ref ??_GTactical@@UAEPAXI@Z=006ac800
// @ref ??_ETactical@@UAEPAXI@Z=006ac800
// @ref ??1Tactical@@UAE@XZ=006a2710
// @ref ?Detach@Tactical@@UAEXPAVAbstractClass@@_N@Z=006aab60
// @ref ?GetClassID@Tactical@@UAGJPAUGUID@@@Z=006ac2e0
// @ref ?Load@Tactical@@UAGJPAUIStream@@@Z=006ac320
// @ref ?Save@Tactical@@UAGJPAUIStream@@H@Z=006ac400
// @ref ?Kind_Of@Tactical@@UBEHXZ=006ac7e0
// @ref ?Size_Of@Tactical@@UBEHXZ=006ac7f0
// @ref ?AI@Tactical@@UAEXXZ=006a2dd0
// @ref ?unknown_slot24@Tactical@@UAE_NABUCoordStruct@@0H_N@Z=006ac160
// @ref ?unknown_abe540@@3UPoint2D@@A=00abe540/00abe544
// @ref __real@4@4004f000000000000000=007a8844
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c

extern Point2D unknown_abe540;    // 0x00ABE540 (the header static unknown_geometry_l, read as a point)

Tactical::Tactical()
    : unknown_a8(-1),
      TacPixelX(0),
      TacPixelY(0),
      LastTacPixelX(0),
      LastTacPixelY(0),
      unknown_c0(1.0),
      unknown_c8(unknown_abe540),
      unknown_d0(unknown_abe540),
      unknown_d8(0),
      unknown_dc(0),
      unknown_e0(0),
      unknown_d64(0, 0),
      unknown_d6c(0, 0),
      unknown_d74(0, 0),
      unknown_d7c(true),
      unknown_d7d(false),
      unknown_d7e(false),
      unknown_d80(unknown_static_rect),
      unknown_d90(0, 0),
      unknown_d98(0, 0),
      unknown_da0(0),
      unknown_da4(),
      unknown_db0(0)
{
    for (int i = 0; i < 800; i++) {
        unknown_e4[i] = 0;
    }

    unknown_24 = 0;
    unknown_a4 = -1;

    unknown_db4.Make_Identity();
    unknown_db4.Rotate_X(unknown_geometry_angle60);
    unknown_db4.Rotate_Z(unknown_geometry_angle45);
    unknown_db4.Scale(60.0f / (float)unknown_geometry_diagonal);

    unknown_de4.Set(4.2667f, 8.5334f, 0.0f, 0.0f,
                    -4.2667f, 8.5334f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f);

    unknown_tactical_83996c = this;
}
