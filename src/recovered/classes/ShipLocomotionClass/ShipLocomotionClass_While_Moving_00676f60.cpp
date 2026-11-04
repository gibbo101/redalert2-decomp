// bool ShipLocomotionClass::While_Moving(bool just_started) (0x00676F60)
// TibSun DriveClass::While_Moving: accelerates or slows the unit, then moves
// it along its track by the accumulated speed, handling tunnels, crushing,
// track jumps at turns and arrival at the head-to coordinate.
#include "shared/ship_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/overlay_type.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/tube.hpp"
#include "shared/adjacent_cell.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ?ShipRawTracks@@3QBURawTrackStruct@@B=007aad20
// @ref ?ShipTrackControl@@3QBUTrackControlStruct@@B=007aadf0
// @ref ?Smooth_Turn@ShipLocomotionClass@@QAE?AUPoint2D@@ABU2@AAH@Z=0067a690
// @ref _unknown_geometry_g=00ab9200
// @ref _unknown_geometry_j=00ab91f0
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAVTubeClass@@@@A=008661c8
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?AdjacentCell@@3QBUCell@@B=00851a70
// @ref ?unknown_adjacent_offsets_00851ac0@@3QBUPoint2D@@B=00851ac0
// @ref ?Lerp@@YI?AUCoordStruct@@ABU1@0M@Z=007220c0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __deaccel=007a96b8
// @ref __sinking=007a96c0
// @ref __sinking_scale=007a96c8
// @ref __real@8@3ffbba2e8ba2e8ba3000=007a05d0
// @ref __real@8@3ffc9249249249249000=007a05c0
// @ref __real@8@4001e000000000000000=007a05c8

extern Point2D const unknown_adjacent_offsets_00851ac0[8];
CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t);

static const double _deaccel = 0.3f;
static const double _sinking = 0.1f;
static const double _sinking_scale = 0.0015f;

#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
inline Cell Adjacent_Cell(Cell cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif

// TibSun Adjacent_Cell(Coord const &, FacingType): the coordinate one cell away (Coord + AdjacentPoint).
inline CoordStruct Adjacent_Coord(CoordStruct const &coord, int facing)
{
    Point2D const &offset = unknown_adjacent_offsets_00851ac0[facing & 7];
    return CoordStruct(coord.X + offset.X, coord.Y + offset.Y, coord.Z);
}

// TibSun TPoint2D - TPoint3D (the coordinate taken as its TPoint2D base).
inline Point2D Point_Difference(Point2D const &point, CoordStruct const &coord)
{
    return Point2D(point.X - coord.X, point.Y - coord.Y);
}

// TibSun Coord(TPoint2D, z): a track point at a height.
inline CoordStruct Point_Coord(Point2D const &point, int z)
{
    return CoordStruct(point.X, point.Y, z);
}


inline CoordStruct::CoordStruct(Point2D const &point, int z) : BASECLASS(point.X, point.Y, z) {}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool ShipLocomotionClass::While_Moving(bool just_started)
{
    if ((!unknown_63 || unknown_58 == -1) && LinkedTo->Path[0] != 8 || (unknown_62 && !LinkedTo->unknown_slot32()->Turret)) {
        unknown_4c = 0;
        return false;
    }
    if (LinkedTo->unknown_slot32()->Accelerates) {
        bool not_passive = LinkedTo->Kind_Of() != 1 || !((UnitClass *)LinkedTo)->Type->Passive;
        if (unknown_58 < 0x40 && not_passive) {
            CoordStruct dest_coord = unknown_34;
            dest_coord.Z = Map.Unknown_0055A280(dest_coord) + (Map[dest_coord].IsUnderBridge ? unknown_geometry_j : 0);
            int distance = (Object_Coord(LinkedTo) - CoordStruct(dest_coord)).Length();

            bool forced_speed = false;
            double speed = LinkedTo->unknown_468;

            TechnoTypeClass const *tclass = LinkedTo->unknown_slot32();

            if (distance < tclass->SlowdownDistance) {
                forced_speed = true;
                speed = MAX(_deaccel, speed - tclass->Speed * tclass->DeaccelerationFactor);
            } else if (LinkedTo->unknown_325) {
                speed = MAX(_sinking, speed - tclass->Speed * _sinking_scale);
                forced_speed = true;
            }

            if (LinkedTo->unknown_59f) {
                unknown_50 = MIN(unknown_50, 0.2);
                LinkedTo->unknown_slot306(unknown_50);
            } else if (forced_speed) {
                LinkedTo->unknown_slot306(speed);
            } else if (LinkedTo->unknown_468 < unknown_50) {
                LinkedTo->unknown_slot306(MIN(unknown_50, LinkedTo->unknown_468 + tclass->AccelerationFactor));
            } else if (LinkedTo->unknown_468 > unknown_50) {
                LinkedTo->unknown_slot306(MAX(unknown_50, LinkedTo->unknown_468 - tclass->Speed * tclass->DeaccelerationFactor));
            }

            if (LinkedTo->Kind_Of() == 1) {
                UnitClass *unit = (UnitClass *)LinkedTo;
                UnitClass *following = (UnitClass *)unit->unknown_5b0;
                if (following != 0) {
                    do {
                        following->unknown_slot306(LinkedTo->unknown_468);
                        following = (UnitClass *)following->unknown_5b0;
                    } while (following && following != following->unknown_5b0);
                }
            }
        }
    } else {
        LinkedTo->unknown_slot306(unknown_50);
    }

    int maxspeed = LinkedTo->unknown_slot303();

    int actual;
    actual = unknown_4c + (just_started ? 0 : maxspeed);

    int nextface;
    nextface = LinkedTo->Path[0];

    if (nextface == 8 && unknown_58 == -1) {
        LinkedTo->unknown_slot71(0);
        Stop_Driver();

        CellClass *cell = (CellClass *)LinkedTo->unknown_slot105();
        int tubenum = cell->unknown_116;
        if (tubenum >= 0 && tubenum < unknown_TubeClass_list_008661c8.Count()) {
            TubeClass *tube = unknown_TubeClass_list_008661c8[tubenum];
            Cell c = tube->ExitCell;
            unknown_40 = c.As_Coord();
            memcpy((char *)&LinkedTo->Path, (char *)&LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * 23);
            LinkedTo->Path[23] = -1;
            LinkedTo->unknown_574 = tubenum;
            TPoint2D<short> const &enter = tube->EnterCell;
            LinkedTo->unknown_575 = 0;
            LinkedTo->unknown_45c = Map[Adjacent_Cell(Cell(enter), tube->Directions[0])].unknown_475d60();
            int current_height = Map.Unknown_0055A280(Object_Coord(LinkedTo));
            Cell exit = tube->ExitCell;
            int count = tube->unknown_1c0;
            LinkedTo->unknown_45c.Z = current_height + (Map.Unknown_0055A280(exit) - current_height) / count;
            unknown_63 = true;
            unknown_58 = -1;
        } else {
            LinkedTo->Path[0] = -1;
            unknown_58 = -1;
            unknown_40 = unknown_coord_ab91c8;
            Stop_Driver();
        }
        return false;
    }

    if (actual > 7) {
        TrackControlStruct const *track;
        TrackType const *ptr;
        int tracknum;
        bool adj;

        track = &ShipTrackControl[unknown_58];
        if (unknown_60) {
            tracknum = track->StartTrack;
        } else {
            tracknum = track->Track;
        }
        ptr = ShipRawTracks[tracknum - 1].Track;

        if (nextface < -1 || nextface > 8) {
            LinkedTo->Path[0] = -1;
            return false;
        }

        adj = false;
        if (nextface != 8 && nextface != -1 && Dir_To_8(UnknownFacingDir((unsigned short)((unsigned char)track->Facing << 8))) != nextface) {
            adj = true;
        }

        while (actual > 7) {
            Point2D offset;
            int dir;

            actual -= 7;

            offset = ptr[unknown_5c].Offset;
            if (offset != Point2D(0, 0) || !unknown_5c) {
                if (LinkedTo->unknown_slot47()) {
                    LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
                    LinkedTo->unknown_5a0 = false;
                    LinkedTo->unknown_5a1 = false;
                }

                Cell oldcell;
                if (!unknown_5c) {
                    oldcell = LinkedTo->unknown_slot104();
                } else {
                    dir = ptr[unknown_5c - 1].Facing;
                    Point2D prevoffset = ptr[unknown_5c - 1].Offset;
                    oldcell = CoordStruct(Smooth_Turn(prevoffset, dir), 0).As_Cell();
                }

                dir = ptr[unknown_5c].Facing;
                CoordStruct newcoord = Point_Coord(Smooth_Turn(offset, dir), 0);
                Cell a0 = newcoord.As_Cell();
                Cell b0 = Object_Coord(LinkedTo).As_Cell();
                Cell newcell = newcoord.As_Cell();

                if (a0 != b0) {
                    LinkedTo->unknown_slot71(0);
                    LinkedTo->unknown_slot103(newcoord);
                    CellClass *oldcellptr = &Map[oldcell];
                    CellClass *newcellptr = &Map[newcell];
                    if (newcellptr->unknown_11b == oldcellptr->unknown_11b - 4 && newcellptr->IsUnderBridge) {
                        LinkedTo->unknown_79 = true;
                    }
                    if (!newcellptr->IsUnderBridge && oldcellptr->IsUnderBridge) {
                        LinkedTo->unknown_79 = false;
                    }
                    if (LinkedTo->unknown_slot32()->IsTrain && !((UnitClass *)LinkedTo)->unknown_5b8) {
                        FootClass *train = LinkedTo;
                        bool is_bridge = train->unknown_79 || (Object_Coord(LinkedTo).Z >= (Map.Unknown_0055A280(Object_Coord(LinkedTo)) + unknown_geometry_j));
                        ObjectClass *object = is_bridge ? Map[newcell].AltOccupierPtr : Map[newcell].OccupierPtr;
                        ObjectClass *&ref = object;
                        ObjectClass *occupier = ref;
                        while (occupier != 0) {
                            ObjectClass *next = occupier->unknown_30;
                            if (!occupier->Class_Of()->unknown_1fd) {
                                int strength = 10000;
                                occupier->unknown_slot86(&strength, 0, Rules->unknown_c74, 0, true, true);
                                strength = 20;
                                train->unknown_slot86(&strength, 0, Rules->unknown_c74, 0, true, false);
                            }
                            occupier = next;
                        }
                    }
                    if (!LinkedTo->unknown_7d) return false;
                    LinkedTo->unknown_slot71(1);

                    if (newcellptr->OverlayIndex != -1) {
                        OverlayTypeClass *otype = OverlayTypes[newcellptr->OverlayIndex];
                        if (unknown_64 && (LinkedTo->unknown_slot32()->Crusher || LinkedTo->unknown_6d7910(0x11)) && otype->ArrayIndex == 0) {
                            LinkedTo->unknown_59f = true;
                            TechnoTypeClass const *ttype = LinkedTo->unknown_slot32();
                            if (ttype->TiltsWhenCrushes) {
                                LinkedTo->unknown_28c = -0.02f;
                            }
                        }
                    }
                } else {
                    bool down = LinkedTo->unknown_74;
                    LinkedTo->unknown_74 = false;
                    LinkedTo->unknown_slot103(newcoord);
                    LinkedTo->unknown_74 = down;
                }

                if (!LinkedTo->unknown_7d) {
                    return false;
                }

                bool down = LinkedTo->unknown_74;
                LinkedTo->unknown_74 = false;
                LinkedTo->unknown_slot109(0);
                LinkedTo->unknown_74 = down;

                LinkedTo->unknown_2e0.Set_Current(UnknownFacingDir((unsigned short)((unsigned char)dir << 8)));

                if (unknown_5c && ShipRawTracks[tracknum - 1].Cell == unknown_5c) {
                    LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
                }

                if (nextface != 8 && nextface != -1 && adj && ShipRawTracks[tracknum - 1].Jump == unknown_5c && unknown_5c) {
                    TrackControlStruct const *newtrack;
                    int tnum;

                    tnum = Dir_To_8(UnknownFacingDir((unsigned short)((unsigned char)track->Facing << 8))) * 8 + nextface;
                    newtrack = &ShipTrackControl[tnum];
                    if (newtrack->Track && ShipRawTracks[newtrack->Track - 1].Entry) {
                        double oldspeed = LinkedTo->unknown_468;

                        CoordStruct c = Adjacent_Coord(unknown_40, nextface);

                        switch (LinkedTo->unknown_slot101(&Map[c.As_Cell()], nextface, LinkedTo->unknown_5d47d0(), 0, true)) {
                            case 0:
                            case 2:
                                if (LinkedTo->Kind_Of() == 1 && !((UnitClass *)LinkedTo)->Type->Passive) break;
                                unknown_60 = false;
                                unknown_58 = tnum;
                                track = newtrack;

                                tracknum = track->Track;
                                unknown_5c = ShipRawTracks[tracknum - 1].Entry - 1;
                                ptr = ShipRawTracks[tracknum - 1].Track;
                                adj = false;

                                Stop_Driver();
                                unknown_63 = true;
                                LinkedTo->unknown_slot93(2);
                                unknown_63 = false;
                                if (!LinkedTo->unknown_7d || LinkedTo->unknown_76 || LinkedTo->unknown_7a) return false;
                                if (Start_Driver(c)) {
                                    LinkedTo->unknown_slot306(oldspeed);
                                    memcpy((char *)&LinkedTo->Path, (char *)&LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * 23);
                                    LinkedTo->Path[23] = -1;
                                }
                                break;

                            case 1:
                                Map[c].unknown_478740();
                                break;

                            case 3:
                                {
                                    Cell gate = c.As_Cell();
                                    Map.Unknown_0055ACD0(LinkedTo, gate);
                                }
                                break;

                            case 6: {
                                    bool bridge;
                                    if (!Map[c].IsUnderBridge || abs(Object_Coord(LinkedTo).Z / unknown_geometry_g - Map[c].unknown_11b) <= 2) {
                                        bridge = false;
                                    } else {
                                        bridge = true;
                                    }
                                    Map[unknown_40].unknown_476920(&unknown_coord_ab91c8, true, true, bridge);
                                }
                                break;
                        }
                    }
                }
                unknown_5c++;

            } else {
                CoordStruct dc = unknown_40 - Object_Coord(LinkedTo);
                int d = abs(dc.X) + abs(dc.Y);
                actual += (int)((1.0 - (double)d / 11.0) * 7.0);
                LinkedTo->unknown_5a0 = true;
                LinkedTo->unknown_5a1 = false;

                Cell here = Object_Coord(LinkedTo).As_Cell();
                if (here != unknown_40.As_Cell()) {
                    LinkedTo->unknown_slot71(0);
                    LinkedTo->unknown_slot103(unknown_40);
                    LinkedTo->unknown_slot109(0);
                    LinkedTo->unknown_slot71(1);
                } else {
                    bool down = LinkedTo->unknown_74;
                    LinkedTo->unknown_74 = false;
                    LinkedTo->unknown_slot103(unknown_40);
                    LinkedTo->unknown_slot109(0);
                    LinkedTo->unknown_74 = down;
                }

                Stop_Driver();
                unknown_58 = -1;
                unknown_5c = 0;

                bool arrived = false;
                AbstractClass *target = LinkedTo->unknown_494;
                if (target != 0 && LinkedTo->unknown_slot104() == target->unknown_slot19(LinkedTo).As_Cell()) {
                    if (abs(LinkedTo->unknown_slot19(LinkedTo).Z - unknown_34.Z) < 2 * unknown_geometry_g) {
                        arrived = true;
                        unknown_34 = unknown_coord_ab91c8;
                        Stop_Driver();
                        unknown_63 = false;
                    }
                }

                LinkedTo->unknown_slot93(2);
                if (!LinkedTo->unknown_7d || LinkedTo->unknown_76 || LinkedTo->unknown_7a) return true;

                if (arrived) {
                    LinkedTo->unknown_4cd9b0();
                    LinkedTo->Path[0] = -1;
                    if (LinkedTo->unknown_slot91() == 2 && LinkedTo->unknown_slot261(false, true)) {
                        return true;
                    }
                }

                if (LinkedTo->unknown_slot292()) {
                    return true;
                }

                if (!LinkedTo->unknown_7d) return false;

                break;
            }
        }
    }

    unknown_4c = actual;

    if (actual > 0 && unknown_58 > -1) {
        TrackControlStruct const *track;
        TrackType const *ptr;
        int tracknum;

        track = &ShipTrackControl[unknown_58];
        if (unknown_60) {
            tracknum = track->StartTrack;
        } else {
            tracknum = track->Track;
        }
        ptr = ShipRawTracks[tracknum - 1].Track;

        int dir;
        Point2D offset = ptr[unknown_5c].Offset;
        if (offset != Point2D(0, 0) || !unknown_5c) {

            CoordStruct oldcoord = Object_Coord(LinkedTo);

            dir = ptr[unknown_5c].Facing;
            CoordStruct movement(Point_Difference(Smooth_Turn(offset, dir), Object_Coord(LinkedTo)), 0);
            CoordStruct stepcoord = movement + Object_Coord(LinkedTo);
            CellClass *stepcellptr = &Map[stepcoord];

            CoordStruct partial(0, 0, 0);
            movement = Lerp(partial, movement, unknown_4c / 7.0);
            CoordStruct partialcoord = oldcoord + movement;

            CellClass *oldcellptr = &Map[oldcoord];
            CellClass *partialcellptr = &Map[partialcoord];

            CoordStruct coord = Object_Coord(LinkedTo);

            if (partialcellptr != stepcellptr && partialcellptr != oldcellptr) {
                if (unknown_4c > 3) {
                    coord = stepcoord;
                }
            } else {
                coord = partialcoord;
            }

            CellClass *newcellptr = &Map[CoordStruct(coord)];

            if (coord.As_Cell() != Object_Coord(LinkedTo).As_Cell()) {
                LinkedTo->unknown_slot71(0);
                LinkedTo->unknown_slot103(coord);
                if (newcellptr->unknown_11b == oldcellptr->unknown_11b - 4 && newcellptr->IsUnderBridge) {
                    LinkedTo->unknown_79 = true;
                }
                if (!newcellptr->IsUnderBridge && oldcellptr->IsUnderBridge) {
                    LinkedTo->unknown_79 = false;
                }
                LinkedTo->unknown_slot71(1);
            } else {
                bool down = LinkedTo->unknown_74;
                LinkedTo->unknown_74 = false;
                LinkedTo->unknown_slot103(coord);
                LinkedTo->unknown_74 = down;
            }
        }
    }

    return false;
}
