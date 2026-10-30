void __fastcall Unknown_00718D80(int from, int to, Matrix3D *matrix, double alpha)
{
    if (from == to) {
        *matrix = unknown_matrices_af73a0[to];
    } else {
        *matrix = Build_Matrix3D(Slerp(unknown_quaternions_af77d8[from], unknown_quaternions_af77d8[to], (float)alpha));
    }
}
