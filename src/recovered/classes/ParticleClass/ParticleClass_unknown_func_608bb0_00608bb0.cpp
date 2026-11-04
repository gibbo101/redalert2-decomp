// void ParticleClass::unknown_func_608bb0() (0x00608BB0)
// Smoke behaviour (TibSun ParticleClass::Gas_Behavior_AI): every other frame the
// drift jitters within +-5 and the smoke sinks, glancing off the ground, bridge
// decks and walls; then it damages what shares its cell and advances its state.
#include "shared/particle.hpp"
#include "shared/cd_timer.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/rules.hpp"
#include "shared/matrix3d.hpp"
#include "shared/bounce.hpp"
#include "shared/tunnel_locomotion.hpp"
#include "shared/anim.hpp"
#include "shared/building_type.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_475840@CellClass@@QBE_NHH@Z=00475840
// @ref _unknown_geometry_j=00a76510
// @ref __real@4@40069600000000000000=0079caa8
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref _?$S43@?1??unknown_slot64@ParticleClass@@UAEPBVCell@@H@Z@4EA=00a76520

// TibSun Slope_Vector: reflects a vector off the slope of the cell at coord.
static inline Vector3 Slope_Vector(Vector3 &vector, CoordStruct const &coord, float length)
{
    Matrix3D slope_matrix;
    slope_matrix = *Unknown_00718D60(&Matrix3D(), unknown_tactical_83996c->Get_Cell_Ramp_006a7110(coord));
    Matrix3D slope_matrix_inv = Matrix3D_Rigid_Inverse_00591420(slope_matrix);
    Vector3 vec;
    vec.Set_00437690(vector.X, -vector.Y, vector.Z);
    vec = slope_matrix_inv.Rotate_Vector(vec);
    vec.Scale_004376b0(length);
    vec.Z = -vec.Z;
    vec = slope_matrix.Rotate_Vector(vec);
    vector.X = vec.X;
    vector.Y = -vec.Y;
    vector.Z = vec.Z;
    return vector;
}

// The height of a bridge deck over coord; ground receives the ground height.
static inline int Bridge_Height(CoordStruct const &coord, int &ground)
{
    int height = Map.Unknown_0055A280(coord);
    ground = height;
    return height + unknown_geometry_j;
}

// Keeps a value within [low, high].
static inline void Limit(int &value, int low, int high)
{
    if (value < low) {
        value = low;
    } else if (value > high) {
        value = high;
    }
}

void ParticleClass::unknown_func_608bb0()
{
    if ((Frame & 1) == 0) {
        CoordStruct coord = Coord;
        if ((abs(unknown_id_source_a3d290->Random()()) & 7) == 0) {
            int dx = 0;
            int dy = 0;
            if ((abs(unknown_id_source_a3d290->Random()()) & 1) == 0) {
                dx = abs(unknown_id_source_a3d290->Random()()) % 3 - 1;
            } else {
                dy = abs(unknown_id_source_a3d290->Random()()) % 3 - 1;
            }
            unknown_b0.X += dx;
            unknown_b0.Y += dy;
            Limit(unknown_b0.X, -5, 5);
            Limit(unknown_b0.Y, -5, 5);
        }

        Vector3 position(coord.X, coord.Y, coord.Z);
        Vector3 &velocity = GasVelocity;
        velocity = Vector3(0, 0, -2);
        double gravity = Rules->unknown_1320;
        velocity.Z -= gravity;

        CoordStruct old_coord;
        old_coord.Set_00434820(position.X, position.Y, position.Z);
        position.Add_004376e0(velocity);
        CoordStruct coord2;
        coord2.Set_00434820(position.X, position.Y, position.Z);

        int height_gl;
        int height_bridge = Bridge_Height(coord2, height_gl);

        CellClass *cellptr = &Map[coord2];
        bool start_under_bridge = false;
        bool end_under_bridge = false;
        if ((cellptr->unknown_140 & 0x100) || (Map[old_coord].unknown_140 & 0x100)) {
            if (coord2.Z >= height_bridge) {
                if (old_coord.Z < height_bridge) {
                    end_under_bridge = true;
                }
            } else {
                if (old_coord.Z >= height_bridge) {
                    start_under_bridge = true;
                }
            }
        }

        bool blocked = false;
        if (!start_under_bridge && !end_under_bridge) {
            if (position.Z >= (double)height_gl && position.Z - 150.0f < (double)height_gl) {
                BuildingClass *building = static_cast<BuildingClass *>(cellptr->unknown_4717b0());
                if (building || cellptr->unknown_475840(-1, -1)) {
                    blocked = true;
                    if (building) {
                        if (building->Type->LaserFence && building->unknown_4ec >= 8) {
                            blocked = false;
                        }
                        if (building->unknown_slot31()) {
                            blocked = false;
                        }
                    }
                } else {
                    blocked = false;
                }
            }
        }

        if (position.Z < (float)height_gl || start_under_bridge || end_under_bridge || blocked) {
            if (start_under_bridge) {
                position.Z = height_bridge;
            } else if (end_under_bridge) {
                position.Z = height_bridge - 20;
            } else if ((float)(height_gl - 100) < position.Z) {
                position.Z = (float)height_gl;
            }
            Slope_Vector(velocity, coord2, 1);
        }

        if (unknown_slot108() > 5 && (Frame % 2) == 0) {
            unknown_b0.Z = (-5 > unknown_b0.Z - 1) ? -5 : unknown_b0.Z - 1;
        } else {
            unknown_b0.Z = (unknown_b0.Z > 0) ? unknown_b0.Z : 0;
        }
    }

    unknown_11a--;

    if (unknown_11a == 0 && Class->Damage) {
        unknown_11a = Class->MaxDC;
        ObjectClass *occupier = Map[Position_Coord_004f3f40()].OccupierPtr;
        while (occupier) {
            CoordStruct delta = Position_Coord_004f3f40() - occupier->Position_Coord_004f3f40();
            ObjectClass *next = occupier->unknown_30;
            if (occupier->unknown_7d) {
                if (occupier->Strength > 0) {
                    int damage = Class->Damage;
                    occupier->unknown_slot86(&damage, Unknown_006A2970(abs(delta.X) + abs(delta.Y)), Class->Warhead, 0, 0, 0);
                }
            }
            occupier = next;
        }
    }

    if ((Fetch_ID() + (Class->MaxEC - Lifetime)) % ((Fetch_ID() & 1) + Class->StateAIAdvance) == 0) {
        unknown_11e++;
    }
    if (unknown_11e == Class->EndStateAI) {
        if (Class->DeleteOnStateLimit) {
            unknown_121 = true;
            return;
        }
        unknown_11e = 0;
    }
}
