// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref __real@4@40038000000000000000=007aea40
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@4@00000000000000000000=0079a738
// Westwood's Vector3 dot product, Length2, division by a scalar and
// Normalize (the RA2 shared Vector3 does not declare them).
static inline float Vector3_Dot(Vector3 const &a, Vector3 const &b)
{
    return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}
static inline float Vector3_Length2(Vector3 const &v)
{
    return v.Y * v.Y + (v.X * v.X + v.Z * v.Z);
}
static inline Vector3 Vector3_Divide(Vector3 const &a, double k)
{
    return Vector3((float)(a.X / k), (float)(a.Y / k), (float)(a.Z / k));
}
static inline Vector3 Vector3_Normalize(Vector3 const &vec)
{
    float len = (float)Fast_Sqrt(Vector3_Length2(vec));
    if (len != 0.0) {
        return Vector3_Divide(vec, len);
    }
    return vec;
}
// Fills the shade table from a light and a view direction: the lit share of
// each normal of normal type `type` plus a specular term from the halfway
// vector (Schlick: d / (k - d * k + d)), each clamped at 0, times 16; the
// last three entries are unlit.
void __fastcall unknown_71baa0(Vector3 const *light, Vector3 const *view, float specular, int type)
{
    Vector3 const *normals = unknown_normal_tables_7f9f80[type];
    Vector3 sum = *view + *light;
    Vector3 halfway = Vector3_Normalize(sum);
    for (int index = 0; index < unknown_normal_counts_7f9f94[type]; index++) {
        Vector3 const &normal = normals[index];
        float diffuse = Vector3_Dot(normal, *light);
        float dot = Vector3_Dot(normal, halfway);
        float shine = dot / (specular - dot * specular + dot);
        shine = shine >= 0.0f ? shine : 0.0f;
        diffuse = diffuse >= 0.0f ? diffuse : 0.0f;
        float total = diffuse + shine;
        if (total < 0.0) {
            unknown_shades_af8e10[index] = 0;
        } else {
            unknown_shades_af8e10[index] = (unsigned char)(total * 16.0f);
        }
    }
    unknown_shades_af8e10[255] = 0x10;
    unknown_shades_af8e10[254] = 0x10;
    unknown_shades_af8e10[253] = 0x10;
}
