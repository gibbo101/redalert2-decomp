// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void Tactical::Draw_Objects(bool forced) (0x006A93F0): from ra2-decomp Tactical::Draw_Objects
// (YR 0x006D8DB0), adapted to our names. Clears every layer object's visible flag (+0x85), draws
// those whose position lies in the view diamond (fogged foot objects, fog-removing animations and
// animating terrain under fog skipped), the ground layer's selected buildings' overlays, then the
// post-render pass of every visible techno.
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/terrain.hpp"
#include "shared/terrain_type.hpp"
#include "shared/building_class.hpp"
#include "shared/techno.hpp"

static inline bool Is_Foot_Object(ObjectClass const *object)
{
    if (object == 0) {
        return false;
    }
    unsigned char flag = object->AbstractFlags.IsFoot;
    return flag != 0;
}

static inline bool Is_Techno_Object(ObjectClass const *object)
{
    if (object == 0) {
        return false;
    }
    unsigned char flag = object->AbstractFlags.IsTechno;
    return flag != 0;
}

static inline bool Is_Animating(TerrainClass const *terrain)
{
    return terrain->Class->IsAnimated || terrain->unknown_b5;
}

void Tactical::Draw_Objects(bool forced)
{
    int width = unknown_rect_839630.Width;
    int pixelx = TacPixelX;
    int pixely = TacPixelY;
    int height = unknown_rect_839630.Height;
    Point2D top = Unknown_006A2900(Point2D(pixelx + width / 2, pixely - height));
    Point2D right = Unknown_006A2900(Point2D(pixelx + width * 2, pixely + height / 2));
    Point2D left = Unknown_006A2900(Point2D(pixelx - width, pixely + height / 2));
    Rect view(top.X, top.Y, (right.X - top.X) * 2, (left.Y - top.Y) * 2);
    CoordStruct position;

    for (int layer = 0; layer < 5; layer++) {
        for (int index = 0; index < DisplayClass::Layer[layer].Count(); index++) {
            ObjectClass *obj = DisplayClass::Layer[layer][index];
            obj->unknown_85 = false;

            if (Is_Foot_Object(obj)) {
                position = obj->Position_Coord_004f3f40();
                if (view.Is_Point_Within(Point2D(position.X, position.Y))) {
                    obj->unknown_slot19(0);
                    if (unknown_id_source_a3d290->Special().FogOfWar && Map.Unknown_005683C0(position)) {
                        continue;
                    }
                    Point2D pixel;
                    if (unknown_tactical_83996c->Coord_To_Pixel(obj->Center_Coord(), pixel)) {
                        obj->unknown_85 = true;
                        obj->unknown_slot65((int)&pixel, (int)&unknown_rect_839630);
                        obj->unknown_slot63(&unknown_rect_839630, forced, false);
                    }
                }
            } else if (Is_Techno_Object(obj)) {
                position = obj->Position_Coord_004f3f40();
                if (view.Is_Point_Within(Point2D(position.X, position.Y))) {
                    obj->unknown_85 = true;
                    Draw_Render_Hooks(obj, unknown_rect_839630);
                    obj->unknown_slot63(&unknown_rect_839630, forced, true);
                }
            } else {
                int rtti = obj->Kind_Of();
                if (rtti == 4) {
                    position = obj->Center_Coord();
                    if (view.Is_Point_Within(Point2D(position.X, position.Y))) {
                        AnimClass *anim = (AnimClass *)obj;
                        obj->unknown_85 = true;
                        if (!anim->unknown_100 && anim->Class->ShouldFogRemove && Map.Unknown_005683C0(obj->Center_Coord())) {
                            continue;
                        }
                        obj->unknown_slot63(&unknown_rect_839630, forced, false);
                    }
                } else if (rtti == 0x24) {
                    if (Is_Animating((TerrainClass *)obj)) {
                        position = obj->Position_Coord_004f3f40();
                        if (view.Is_Point_Within(Point2D(position.X, position.Y))) {
                            if (Map.Unknown_005683C0(position)) {
                                continue;
                            }
                            obj->unknown_85 = true;
                            obj->unknown_slot63(&unknown_rect_839630, forced, false);
                        }
                    }
                } else {
                    position = obj->Position_Coord_004f3f40();
                    if (view.Is_Point_Within(Point2D(position.X, position.Y))) {
                        Point2D pixel;
                        if (unknown_tactical_83996c->Coord_To_Pixel(obj->Center_Coord(), pixel)) {
                            obj->unknown_85 = true;
                            obj->unknown_slot65((int)&pixel, (int)&unknown_rect_839630);
                            obj->unknown_slot63(&unknown_rect_839630, forced, false);
                        }
                    }
                }
            }
        }

        if (layer == 2) {
            for (int bindex = 0; bindex < unknown_BuildingClass_list_00a40af8.Count(); bindex++) {
                BuildingClass *bptr = unknown_BuildingClass_list_00a40af8[bindex];
                if (bptr->unknown_74 && bptr->unknown_85) {
                    Point2D pixel;
                    if (unknown_tactical_83996c->Coord_To_Pixel(bptr->unknown_slot42(), pixel)) {
                        Rect rect = unknown_rect_839630;
                        if (rect.X > unknown_rect_839630.X) pixel.X += unknown_rect_839630.X - rect.X;
                        if (rect.Y > unknown_rect_839630.Y) pixel.Y += unknown_rect_839630.Y - rect.Y;
                        bptr->Draw_Selection_Overlay_0043b660(pixel, rect);
                    }
                }
            }
        }
    }

    for (int layer2 = 0; layer2 < 5; layer2++) {
        int count = DisplayClass::Layer[layer2].Count();
        for (int index2 = 0; index2 < count; index2++) {
            ObjectClass *obj2 = DisplayClass::Layer[layer2][index2];
            if (obj2->unknown_85 && obj2 != 0 && Is_Techno_Object(obj2)) {
                if (Is_Foot_Object(obj2)) {
                    obj2->unknown_slot19(0);
                    if (unknown_b263d8 && !unknown_flag_a40d13 && unknown_id_source_a3d290->Special().FogOfWar && Map.Unknown_005683C0(obj2->Position_Coord_004f3f40())) {
                        continue;
                    }
                }
                Point2D pixel;
                if (unknown_tactical_83996c->Coord_To_Pixel(obj2->Center_Coord(), pixel)) {
                    obj2->unknown_slot66(pixel, unknown_rect_839630);
                }
            }
        }
    }
}
