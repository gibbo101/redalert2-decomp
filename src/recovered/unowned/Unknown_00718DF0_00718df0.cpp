Matrix3D * __fastcall Unknown_00718DF0(Matrix3D *matrix, int from, int to, double alpha)
{
    if (from != to) {
        *matrix = Build_Matrix3D(Slerp(unknown_quaternions_af6618[from], unknown_quaternions_af6618[to], (float)alpha));
        return matrix;
    }
    *matrix = unknown_matrices_af8608[to];
    return matrix;
}
