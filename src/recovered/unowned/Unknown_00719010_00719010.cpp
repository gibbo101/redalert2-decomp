Matrix3D * __fastcall Unknown_00719010(Matrix3D *matrix, int index)
{
    if (index >= 4) {
        index -= 4;
    }
    *matrix = unknown_matrices_af8538[index];
    return matrix;
}
