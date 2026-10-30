// The index of the normal of normal type `type` closest in direction to
// `normal` (largest dot product); 0xFF when `normal` is shorter than 0.2.
int __fastcall unknown_71bc30(Vector3 const *normal, int type)
{
    Vector3 const *normals = unknown_normal_tables_7f9f80[type];
    float best = 0;
    int best_index = 0;
    if (Fast_Sqrt(normal->X * normal->X + normal->Y * normal->Y + normal->Z * normal->Z) < 0.2f) {
        return 0xFF;
    }
    int count = unknown_normal_counts_7f9f94[type];
    for (int index = 0; index < count; index++) {
        float dot = normals[index].X * normal->X + normals[index].Z * normal->Z + normals[index].Y * normal->Y;
        if (dot > best) {
            best = dot;
            best_index = index;
        }
    }
    return best_index;
}
