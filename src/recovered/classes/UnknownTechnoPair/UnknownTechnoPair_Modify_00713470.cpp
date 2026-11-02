// The multiplier for value at this experience: 1 + value * level above zero, a fraction
// below it (0x00713470).
// @ref __real@8@bff8a3d70a3d70a3d800=007ae970
// @ref __real@8@3ff8a3d70a3d70a3d800=0079c518
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@bfff8000000000000000=0079d578
double UnknownTechnoPair::Modify(double value)
{
    double lvl = Experience;
    lvl = floor(lvl);

    if (lvl < -0.01) {
        return -1.0 / (lvl - 1.0);
    }
    if (lvl > 0.01) {
        return 1.0 + (value * lvl);
    }
    return 1.0;
}
