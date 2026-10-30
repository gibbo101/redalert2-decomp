// Fills the shade table from a light direction: the lit share of each normal
// of normal type `type` times 16; the last three entries are unlit.
void __fastcall unknown_71ba20(Vector3 const *light, int type)
{
    Vector3 const *normals = unknown_normal_tables_7f9f80[type];
    int count = unknown_normal_counts_7f9f94[type];
    for (int index = 0; index < count; index++) {
        Vector3 const &normal = normals[index];
        float dot = normal.X * light->X + normal.Z * light->Z + light->Y * normal.Y;
        if (dot < 0.0) {
            unknown_shades_af8e10[index] = 0;
        } else {
            unknown_shades_af8e10[index] = (unsigned char)(dot * 16.0f);
        }
    }
    unknown_shades_af8e10[255] = 0x10;
    unknown_shades_af8e10[254] = 0x10;
    unknown_shades_af8e10[253] = 0x10;
}
