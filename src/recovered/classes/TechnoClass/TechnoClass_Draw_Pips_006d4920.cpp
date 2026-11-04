// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// The free Intersect expanded here while every other row of this unit calls 0x0041FDF0 out of line, so
// shared/rect_intersect.hpp stays out of the unit (its definition would expand them too).
static inline Rect Expanded_Intersect(Rect const &rect1, Rect const &rect2, int *x = 0, int *y = 0)
{
    Rect empty(0, 0, 0, 0);
    Rect result = rect2;
    if (!rect1.Is_Valid() || !rect2.Is_Valid()) {
        return empty;
    }
    if (result.X < rect1.X) {
        result.Width += result.X - rect1.X;
        result.X = rect1.X;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y < rect1.Y) {
        result.Height += result.Y - rect1.Y;
        result.Y = rect1.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (result.X + result.Width > rect1.X + rect1.Width) {
        result.Width = rect1.X - result.X + rect1.Width;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y + result.Height > rect1.Y + rect1.Height) {
        result.Height = rect1.Y + rect1.Height - result.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (x != 0) {
        *x += rect2.X - result.X;
    }
    if (y != 0) {
        *y += rect2.Y - result.Y;
    }
    return result;
}
void TechnoClass::unknown_slot249(Point2D const &point, Point2D const &center, Rect const &window)
{
    Point2D offset(4, 2);
    Point2D xy = point + Point2D(6, -1);
    Class_Of();
    ShapeFileStruct const *pip_shapes = (ShapeFileStruct const *)unknown_pips_shapes_a72fe4;
    Class_Of();
    ShapeFileStruct const *pips2 = (ShapeFileStruct const *)unknown_pips2_shapes_a72fe8;
    bool building = Kind_Of() == 6;
    if (!building) {
        xy = point + Point2D(-5, 0);
        offset = Point2D(4, 0);
        pip_shapes = pips2;
    }
    if (Kind_Of() == 6 && unknown_slot32()->PipScale == 2) return;
    int spawns = unknown_slot32()->SpawnsNumber;
    if (spawns > 0) {
        int docked = SpawnManager->Docked_Count();
        for (int i = 0; i < spawns; i++) {
            int full = 1;
            int empty = 0;
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pip_shapes, i < docked ? full : empty, xy + offset * i, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
    }
    if (building) {
        BuildingClass *self = static_cast<BuildingClass *>(this);
        int occupants = self->Type->MaxNumberOccupants;
        int count = self->unknown_4532f0();
        if (self->Type->ShowOccupantPips && occupants > 0 && count > 0) {
            for (int i = 0; i < occupants; i++) {
                int full = 7;
                int empty = 6;
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pip_shapes, i < count ? full : empty, xy + offset * i, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            }
        }
    }
    if (unknown_slot32()->Passengers > 0) {
        Point2D shift(0, 0);
        int pips = Class_Of()->unknown_slot29();
        unknown_slot32();
        int *colors = new int[pips];
        for (int c = 0; c < pips; c++) colors[c] = 0;
        int passengers = Cargo.Count;
        int index = Cargo.Unknown_00468A20() - 1;
        if (index > pips) index = pips;
        ObjectClass *object = Cargo.unknown_468a10();
        for (int i = 0; i < passengers && object; i++) {
            if (object->Kind_Of() == 15) {
                colors[index] = static_cast<InfantryClass *>(object)->Type->Pip;
            } else if (object->Kind_Of() == 1) {
                int size = (int)(static_cast<TechnoClass *>(object)->unknown_slot32()->Size - 1.0);
                for (int k = size; k > 0; k--) colors[index--] = 4;
                colors[index] = 5;
            } else {
                colors[index] = 1;
            }
            object = object->unknown_30;
            index--;
        }
        int start = 0;
        if (unknown_slot32()->Gunner) {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pip_shapes, colors[0], xy, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            start = 1;
            shift = offset * 2;
        }
        for (int j = start; j < pips; j++) {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pip_shapes, colors[j], xy + shift + offset * j, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
        delete colors;
    } else {
        int pips = unknown_slot166();
        if (Kind_Of() == 1 && unknown_slot32()->PipScale == 2) {
            float gold = unknown_294.Get_Amount(0);
            float gems = unknown_294.Get_Amount(2);
            float ore = unknown_294.Get_Amount(3);
            float other = unknown_294.Get_Amount(1);
            int greenpips = (int)(unknown_slot32()->unknown_slot29() * ((double)(ore + gems + gold) / unknown_slot32()->Storage) + 0.5);
            int bluepips = (int)(unknown_slot32()->unknown_slot29() * ((double)other / unknown_slot32()->Storage) + 0.5);
            for (int i = 0; i < Class_Of()->unknown_slot29(); i++) {
                int shape = 0;
                if (bluepips > 0) {
                    shape = 5;
                    bluepips--;
                } else if (greenpips > 0) {
                    shape = 1;
                    greenpips--;
                }
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pip_shapes, shape, xy + offset * i, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            }
        } else if (unknown_slot32()->PipScale == 1) {
            int wrap = unknown_slot32()->PipWrap;
            if (wrap == 0) {
                int left = pips;
                for (int i = 0; i < Class_Of()->unknown_slot29(); i++) {
                    if (left > 0) {
                        left--;
                        CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pips2, 12, xy + offset * i - Point2D(0, 3), window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                    }
                }
            } else {
                int rows = Class_Of()->unknown_slot29() / wrap;
                for (int i = 0; i < wrap; i++) {
                    int frame = 13;
                    for (int j = rows - 1; j >= 0; j--) {
                        if (i + j * wrap < unknown_254) {
                            frame = j + 14;
                            break;
                        }
                    }
                    CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, pips2, frame, xy + offset * i - Point2D(0, 3), window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                }
            }
        }
    }
    if (Kind_Of() != 6) unknown_slot251(point + Point2D(-10, 10), point, window);
    if (unknown_1ac >= 0 && unknown_1ac < 10) {
        int group = unknown_1ac + 1;
        if (group == 10) group = 0;
        int yval = Kind_Of() == 15 ? -36 : -33;
        wchar_t text[10];
        swprintf(text, L"%d", group < 10 ? group : 0);
        Point2D where = point + Point2D(-4, yval - 3);
        Rect box = Text_Rect(text, where.X, where.Y, 0x49, 2, -2);
        box = Expanded_Intersect(box, window);
        box.X--;
        box.Width++;
        RGBClass color = House->unknown_55e9;
        int pixel = Build_Hicolor_Pixel(color.Red, color.Green, color.Blue);
        unknown_surface_83995c->Fill_Rect(box, 0);
        unknown_surface_83995c->Draw_Rect(box, pixel);
        unknown_scheme_text_print_498050(text, unknown_surface_83995c, &window, &where, pixel, 0, 0x49, -1, 1);
    }
}
