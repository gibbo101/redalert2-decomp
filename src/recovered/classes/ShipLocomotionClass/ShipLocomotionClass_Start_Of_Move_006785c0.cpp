// bool ShipLocomotionClass::Start_Of_Move(bool &stop_processing, bool retry, bool force_straight) (0x006785C0)
// TibSun DriveClass::Start_Of_Move: prepares the path and picks the next
// track, handling blockages at the next cell.
#include "shared/ship_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/overlay_type.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/sound_play.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/ground_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/facing.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0
// @ref _unknown_geometry_g=00ab9200
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?AdjacentCell@@3QBUCell@@B=00851a70
// @ref ?unknown_adjacent_offsets_00851ac0@@3QBUPoint2D@@B=00851ac0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??0?$TPoint3D@H@@QAE@HHH@Z=0041b630
// @ref ?Length@?$TPoint3D@H@@QBEHXZ=0041b780
// @ref ?Ground@@3PAUGroundType@@A=00850ea0
// @ref ?Frame@@3HA=00a40d2c
// @ref __real@8@4008e100000000000000=0079b608

extern Point2D const unknown_adjacent_offsets_00851ac0[8];

#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
inline Cell Adjacent_Cell(Cell cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif

inline TPoint3D<int> const operator+(CoordStruct const &coord, Point2D const &point)
{
    return TPoint3D<int>(coord.X + point.X, coord.Y + point.Y, coord.Z);
}

inline CoordStruct Adjacent_Coord_SOM(CoordStruct const &coord, int facing)
{
    return coord + unknown_adjacent_offsets_00851ac0[facing & 7];
}

bool ShipLocomotionClass::Start_Of_Move(bool &stop_processing, bool retry, bool force_straight)
{
    int facing = LinkedTo->Path[0];

    if (!Is_Moving() && facing == -1) {
        unknown_61 = false;
        Stop_Driver();
        if (LinkedTo->unknown_slot91() == 2) {
            stop_processing = LinkedTo->unknown_slot261(false, true);
        }
        return false;
    }

    if (!(unknown_34 != unknown_coord_ab91c8)) return false;

    if (LinkedTo->SpawnManager != 0 && LinkedTo->SpawnManager->Launching_Count() != 0) return true;
    if (LinkedTo->unknown_slot111() || LinkedTo->unknown_slot112()) return false;
    if (LinkedTo->unknown_slot201() || LinkedTo->unknown_slot202()) return true;

    if (facing != -1) {
        if (LinkedTo->unknown_494 != 0 && LinkedTo->unknown_494->Kind_Of() == 1 || LinkedTo->unknown_494 != 0 && LinkedTo->unknown_494->Kind_Of() == 15) {
            int dist = LinkedTo->Distance(unknown_34) / 256;
            if (dist < 24) {
                LinkedTo->Path[dist] = -1;
                facing = LinkedTo->Path[0];
            }
        }
    }

    if (facing == -1) {
        if (LinkedTo->unknown_530 != 0) {
            return false;
        }
        LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>((int)(Rules->unknown_13c8 * 900.0));

        if (!LinkedTo->unknown_4c3000((unknown_34).As_Cell(), 0, 0)) {
            if (LinkedTo == 0) {
                stop_processing = true;
                return false;
            }
            if (!LinkedTo->unknown_slot171(unknown_34)) {
                LinkedTo->unknown_slot260(0, 1);
                return false;
            }

                if (unknown_34 == unknown_coord_ab91c8) return false;

                if (!LinkedTo->unknown_4c8d60() && LinkedTo->Distance(unknown_34) < Rules->unknown_1380 && (LinkedTo->unknown_slot91() == 2 || LinkedTo->unknown_slot91() == 11)) {
                    Stop_Driver();
                    if (unknown_67a7a0()) return true;
                    if (!LinkedTo->unknown_7d) return false;
                } else {
                    Cell cell = Adjacent_Cell((LinkedTo->Center_Coord()).As_Cell(), Dir_To_8(LinkedTo->unknown_2e0.Current()));
                    if (Map.Unknown_0055A660(cell, true)) {
                        int ok = LinkedTo->unknown_slot101(&Map[cell], Dir_To_8(LinkedTo->unknown_2e0.Current()), LinkedTo->unknown_5d47d0(), 0, true);
                        if (ok == 3) {
                            unknown_67a710(cell);
                        } else if (ok == 6) {
                            CellClass *cellptr = &Map[cell];
                            TechnoClass *blockage = (TechnoClass *)cellptr->unknown_471660(Point2D(0, 0), Object_Coord(LinkedTo).Z > Map.Unknown_0055A280(CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0)) + 2 * unknown_geometry_g, 0);
                            if (blockage != 0 && LinkedTo->House->Is_Ally(blockage) && !LinkedTo->unknown_slot32()->IsTrain) {
                                if (LinkedTo->Distance(unknown_34) < Rules->unknown_1380 && !LinkedTo->In_Radio_Contact()) {
                                    if (abs(unknown_34.Z - Object_Coord(LinkedTo).Z) < 2 * unknown_geometry_g) {
                                        if (Map[Object_Coord(LinkedTo)].Land_Type() != 10) {
                                            Stop_Driver();
                                            if (unknown_67a7a0()) return true; return false;
                                        }
                                    }
                                }
                                bool is_bridge;
                                if (!(cellptr->unknown_140 & 0x100) || abs(Object_Coord(LinkedTo).Z / unknown_geometry_g - cellptr->unknown_11b) <= 2) {
                                    is_bridge = false;
                                } else {
                                    is_bridge = true;
                                }
                                cellptr->unknown_476920(&unknown_coord_ab91c8, true, true, is_bridge);
                            }
                        }
                    }

                    if (LinkedTo->unknown_53c > 0) {
                        LinkedTo->unknown_53c--;
                    } else {
                        Stop_Driver();
                        if (unknown_67a7a0()) return true;
                        if (!LinkedTo->unknown_7d) return false;
                        if (LinkedTo->unknown_57a) Voc_Play(Rules->unknown_620, 1.0f, 0x2000, 0);
                        LinkedTo->unknown_57a = false;
                    }
                }

                if (!Is_Moving() && LinkedTo->unknown_228 != 0 && !LinkedTo->unknown_slot213(LinkedTo->unknown_228)) {
                    LinkedTo->unknown_578 = true;
                    if (LinkedTo->Team != 0) LinkedTo->Team->unknown_func_6baa30();
                    LinkedTo->unknown_slot220(0);
                }

                Stop_Driver();
                unknown_58 = -1;
                unknown_61 = false;
                return false;
            
        }

        if (LinkedTo->Path[0] == 8) {
            return false;
        }

        Cell cell = Adjacent_Cell((LinkedTo->Center_Coord()).As_Cell(), LinkedTo->Path[0]);
        if (Map.Unknown_0055A660(cell, true)) {
            int ok = LinkedTo->unknown_slot101(&Map[cell], LinkedTo->Path[0], LinkedTo->unknown_5d47d0(), 0, true);
            if (ok == 3) {
                unknown_67a710(cell);
            } else if (ok == 6) {
                CellClass *cellptr = &Map[cell];
                TechnoClass *blockage;
                {
                    CoordStruct center(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
                    blockage = (TechnoClass *)cellptr->unknown_471660(Point2D(0, 0), Object_Coord(LinkedTo).Z > Map.Unknown_0055A280(center) + 2 * unknown_geometry_g, 0);
                }
                if (blockage != 0 && LinkedTo->House->Is_Ally(blockage) && !LinkedTo->unknown_slot32()->IsTrain) {
                    if (LinkedTo->Distance(unknown_34) < Rules->unknown_1380 && !LinkedTo->In_Radio_Contact()) {
                        if (abs(unknown_34.Z - Object_Coord(LinkedTo).Z) < 2 * unknown_geometry_g) {
                            if (Map[Object_Coord(LinkedTo)].Land_Type() != 10) {
                                Stop_Driver();
                                return unknown_67a7a0();
                            }
                        }
                    }
                    bool is_bridge;
                    if (!(cellptr->unknown_140 & 0x100) || abs(Object_Coord(LinkedTo).Z / unknown_geometry_g - cellptr->unknown_11b) <= 2) {
                        is_bridge = false;
                    } else {
                        is_bridge = true;
                    }
                    cellptr->unknown_476920(&unknown_coord_ab91c8, true, true, is_bridge);
                }
            }
        }

        LinkedTo->unknown_53c = 10;
        facing = LinkedTo->Path[0];
    }

    if (facing == 8) {
        return false;
    }

    CoordStruct dest = Adjacent_Coord_SOM(Object_Coord(LinkedTo), facing);

    CellClass const &here = Map[Object_Coord(LinkedTo)];
    int cell_height = here.unknown_11b + (LinkedTo->unknown_79 ? 4 : 0);

    CellClass const &next = Map[Adjacent_Coord_SOM(Object_Coord(LinkedTo), facing)];
    if (LinkedTo->unknown_79 ^ next.IsUnderBridge) {
        LinkedTo->unknown_57b = true;
    }
    if (!LinkedTo->unknown_slot159()) {
        return true;
    }
    if (!unknown_67a710((dest).As_Cell())) {
        return true;
    }

    if (UnknownFacingDir(DIR_MIN) < (LinkedTo->unknown_2e0.Current() - UnknownFacingDir((FacingType)facing))) {
        Do_Turn(UnknownFacingDir((FacingType)facing));
        return true;
    } else {
        Cell destcell = (dest).As_Cell();
        CellClass *destptr = &Map[destcell];
        bool crushable_dest = false;
        LinkedTo->unknown_slot71(0);
        int cando = LinkedTo->unknown_slot101(destptr, facing, cell_height, 0, true);
        LinkedTo->unknown_slot71(1);

        if (cando < 7 && LinkedTo->unknown_slot32()->IsTrain) {
            cando = 0;
        } else if ((cando == 5 || cando == 4) && LinkedTo->unknown_slot32()->Crusher && destptr->OverlayIndex == 0) {
            cando = 0;
        }

        int overlay = destptr->OverlayIndex;
        if (overlay != -1 && cando == 0 && OverlayTypes[overlay]->unknown_1fd) {
            crushable_dest = true;
        }

        if (cando != 0) {
            if (cando == 3) {
                unknown_67a710(destcell);
            } else if (cando == 6) {
                if (!LinkedTo->unknown_slot32()->IsTrain) {
                    FootClass *unit = LinkedTo;
                    if (retry) {
                        unit->Path[0] = -1;
                        LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>(0);
                        return Start_Of_Move(stop_processing, false, false);
                    }
                    int dist = unit->Distance(unknown_34);
                    if (dist >= Rules->unknown_1380
                        || abs(unknown_34.Z - Object_Coord(LinkedTo).Z) >= 2 * unknown_geometry_g
                        || Map[Object_Coord(LinkedTo)].Land_Type() == 10) {
                        bool is_bridge;
                        if (!(Map[destcell].unknown_140 & 0x100) || abs(Object_Coord(LinkedTo).Z / unknown_geometry_g - Map[destcell].unknown_11b) <= 2) {
                            is_bridge = false;
                        } else {
                            is_bridge = true;
                        }
                        Map[destcell].unknown_476920(&unknown_coord_ab91c8, true, true, is_bridge);
                    } else {
                        Stop_Driver();
                        if (unknown_67a7a0()) {
                            return true;
                        }
                    }
                }
            } else if (cando == 1) {
                Map[destcell].unknown_478740();
                if (retry) {
                    LinkedTo->Path[0] = -1;
                    return Start_Of_Move(stop_processing, false, false);
                }
                Stop_Driver();
                return unknown_67a7a0();
            }

            Stop_Driver();
            if (cando == 2) {
                if (!LinkedTo->unknown_5a1) {
                    LinkedTo->unknown_5a1 = true;
                    LinkedTo->unknown_558 = CDTimerClass<FrameTimerClass>(Rules->unknown_13d0);
                }
                if (LinkedTo->unknown_530 == 0) {
                    bool around_blockage = LinkedTo->unknown_5a1 && LinkedTo->unknown_558 == 0;
                    bool ok = LinkedTo->unknown_4c3000((unknown_34).As_Cell(), 0, (around_blockage != 0) + 1);
                    if (LinkedTo == 0) {
                        stop_processing = true;
                        return false;
                    }
                    if (ok || LinkedTo->unknown_slot171(unknown_34)) {
                        LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>((int)(Rules->unknown_13c8 * 900.0));
                        return true;
                    }
                    LinkedTo->unknown_slot260(0, 1);
                    return false;
                }
            }

            if (cando == 5 || cando == 4) {
                if (retry) {
                    LinkedTo->Path[0] = -1;
                    LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>(0);
                    return Start_Of_Move(stop_processing, false, false);
                }
                if (Map[destcell].unknown_471830(Point2D(0, 0), 0)) {
                    if (!LinkedTo->House->Is_Ally((TechnoClass *)Map[destcell].unknown_471830(Point2D(0, 0), 0))) {
                        LinkedTo->unknown_slot119(1, (int)Map[destcell].unknown_471830(Point2D(0, 0), 0), 0);
                    }
                } else {
                    if (Map[destcell].OverlayIndex != -1 && OverlayTypes[Map[destcell].OverlayIndex]->Wall) {
                        LinkedTo->unknown_slot119(1, (int)&Map[destcell], 0);
                    }
                }
            } else {
                if (LinkedTo->unknown_57a) Voc_Play(Rules->unknown_620, 1.0f, 0x2000, 0);
            }

            if (cando == 7 && retry) {
                LinkedTo->Path[0] = -1;
                LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>(0);
                return Start_Of_Move(stop_processing, false, false);
            } else if (cando == 7 && !retry) {
                Stop_Driver();
                return unknown_67a7a0();
            }

            LinkedTo->unknown_57a = false;
            unknown_58 = -1;
            return true;
        }

        int height;
        int ground;
        if (abs(cell_height - Map[destcell].unknown_11b) < 2) {
            height = Map[destcell].unknown_11b;
            ground = Map[destcell].Land_Type();
        } else {
            height = cell_height;
            ground = 1;
        }

        TechnoTypeClass *ttype = LinkedTo->unknown_slot32();
        double speed = Ground[ground].Cost[ttype->SpeedType];
        if (speed > 1.0) speed = 1.0;

        int destheight = Map.Unknown_0055A280(Map[destcell].unknown_475d60());
        int unitheight = Map.Unknown_0055A280(Object_Coord(LinkedTo));
        if (destheight > unitheight && LinkedTo->Kind_Of() == 1) {
            if (LinkedTo->unknown_slot32()->SpeedType == 1) {
                speed *= Rules->TrackedUphill;
            } else {
                speed *= Rules->WheeledUphill;
            }
        } else if (destheight < unitheight && LinkedTo->Kind_Of() == 1) {
            if (LinkedTo->unknown_slot32()->SpeedType == 1) {
                speed *= Rules->TrackedDownhill;
            } else {
                speed *= Rules->WheeledDownhill;
            }
        }
        if (speed == 0.0) speed = 0.5;

        if (LinkedTo->Health_Ratio() <= Rules->unknown_1368) {
            speed *= 0.75;
        }
        if (unknown_58 < 0x40) {
            unknown_50 = speed;
        } else {
            if (speed != LinkedTo->unknown_468) {
                LinkedTo->unknown_slot306(speed);
            }
        }

        
        LinkedTo->Overrun_Square(dest.As_Cell(), true);

        int nextface = LinkedTo->Path[1];
        if (nextface == -1) {
            if (LinkedTo->Distance(unknown_34) > 0x200) {
                int patharg = LinkedTo->unknown_slot32()->IsTrain ? 1 : 0;
                bool found = LinkedTo->unknown_4c3000((unknown_34).As_Cell(), patharg, 0);
                bool &result = found;
                if (!result) {
                    if (LinkedTo == 0) {
                        stop_processing = true;
                        return found;
                    }
                    if (!LinkedTo->unknown_slot171(unknown_34)) {
                        LinkedTo->unknown_slot260(0, 1);
                    }
                }
                nextface = LinkedTo->Path[1];
            }
        }
        if (nextface == 8) nextface = facing;
        if (nextface == -1 || force_straight) {
            nextface = facing;
        }

        CellClass const *adjcell;
        if (nextface != -1 && (adjcell = &((CellClass const *)destptr)->Adjacent_Cell(nextface)) != 0 && adjcell->OverlayIndex != -1 && OverlayTypes[adjcell->OverlayIndex]->unknown_1fd || crushable_dest) {
            nextface = facing;
            unknown_64 = true;
        } else {
            unknown_64 = false;
        }

        unknown_60 = false;
        unknown_58 = facing * 8 + nextface;
        if (ShipTrackControl[unknown_58].Track == 0) {
            unknown_58 = facing * 8 + facing;
        }

        if (ShipTrackControl[unknown_58].Flag & 8) {
            int nextcando;
            if (!Map[destcell].unknown_476cc0(LinkedTo) && !LinkedTo->unknown_76) {
                nextcando = 7;
                if (!LinkedTo->unknown_7d) return false;
            } else {
                if (!LinkedTo->unknown_7d) return false;
                dest = Adjacent_Coord_SOM(dest, nextface);
                destcell = (dest).As_Cell();
                nextcando = LinkedTo->unknown_slot101(&Map[destcell], nextface, height, 0, true);
                if (nextcando < 7 && LinkedTo->unknown_slot32()->IsTrain) {
                    nextcando = 0;
                } else if ((nextcando == 4 || nextcando == 5) && LinkedTo->unknown_slot32()->Crusher && Map[destcell].OverlayIndex == 0) {
                    nextcando = 0;
                }
            }
            if (!LinkedTo->unknown_7d) return false;

            if (nextcando != 0) {
                if (nextcando == 3) {
                    unknown_67a710(destcell);
                } else if (nextcando == 2) {
                    return Start_Of_Move(stop_processing, retry, true);
                } else if (nextcando == 6) {
                    if (!LinkedTo->unknown_slot32()->IsTrain) {
                        if (retry) {
                            LinkedTo->Path[0] = -1;
                            LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>(0);
                            return Start_Of_Move(stop_processing, false, false);
                        }
                        if (LinkedTo->Distance_YZX(unknown_34) >= Rules->unknown_1380
                            || abs(unknown_34.Z - Object_Coord(LinkedTo).Z) >= 2 * unknown_geometry_g
                            || Map[Object_Coord(LinkedTo)].Land_Type() == 10) {
                            CellClass *cellptr = &Map[destcell];
                            bool is_bridge;
                            if (!(cellptr->unknown_140 & 0x100) || abs(Object_Coord(LinkedTo).Z / unknown_geometry_g - cellptr->unknown_11b) <= 2) {
                                is_bridge = false;
                            } else {
                                is_bridge = true;
                            }
                            cellptr->unknown_476920(&unknown_coord_ab91c8, true, true, is_bridge);
                        } else {
                            Stop_Driver();
                            if (unknown_67a7a0()) {
                                return true;
                            }
                        }
                    }
                } else if (nextcando == 1) {
                    Map[destcell].unknown_478740();
                    if (retry) {
                        LinkedTo->Path[0] = -1;
                        return Start_Of_Move(stop_processing, false, false);
                    }
                    Stop_Driver();
                    return unknown_67a7a0();
                } else if (nextcando == 7) {
                    if (retry) {
                        LinkedTo->Path[0] = -1;
                        LinkedTo->unknown_530 = CDTimerClass<FrameTimerClass>(0);
                        return Start_Of_Move(stop_processing, false, false);
                    }
                    Stop_Driver();
                    return unknown_67a7a0();
                }

                LinkedTo->Path[0] = -1;
                unknown_58 = -1;
                dest = unknown_coord_ab91c8;
                if (nextcando == 5 || nextcando == 4) {
                    return Start_Of_Move(stop_processing, retry, true);
                }
            } else {
                memcpy(&LinkedTo->Path[0], &LinkedTo->Path[2], sizeof(LinkedTo->Path[0]) * 22);
                LinkedTo->Path[22] = -1;
                LinkedTo->unknown_57b = true;
            }
        } else {
            memcpy(&LinkedTo->Path[0], &LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * 23);
        }

        LinkedTo->Path[23] = -1;
        LinkedTo->unknown_450 = (dest).As_Cell();
        LinkedTo->unknown_57a = false;
        unknown_5c = 0;
        if (!Start_Driver(dest)) {
            unknown_58 = -1;
            LinkedTo->Path[0] = -1;
            LinkedTo->unknown_slot306(0);
        }
        return false;
    }
    return false;
}
