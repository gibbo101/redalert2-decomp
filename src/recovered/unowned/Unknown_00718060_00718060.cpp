// void __fastcall Unknown_00718060() (0x00718060; Tiberian Sun Init_Voxel_Matrices, called by Init_Game 0x005116A0)
// Builds the per-facing and per-ramp voxel matrices and quaternions of this unit's tables. One body of 3,290 bytes
// to the ret at 0x00718D39 (the inventory row stops at 0x00718B80 inside the quaternion sequence). __fastcall: as
// __cdecl VC6 schedules the table/angle register arguments after the stack pushes (88.27).
void __fastcall Unknown_00718060()
{
    float slope_h = (float)unknown_geometry_h;
    float slope_i = (float)unknown_geometry_i;
    Vector3 diagonal1 = Matrix3D(Vector3(0.0f, 0.0f, 1.0f), 0.785375f) * Vector3(1.0f, 0.0f, 0.0f);
    Vector3 diagonal3 = Matrix3D(Vector3(0.0f, 0.0f, 1.0f), 2.3561251f) * Vector3(1.0f, 0.0f, 0.0f);
    Vector3 diagonal5 = Matrix3D(Vector3(0.0f, 0.0f, 1.0f), 3.9268751f) * Vector3(1.0f, 0.0f, 0.0f);
    Vector3 diagonal7 = Matrix3D(Vector3(0.0f, 0.0f, 1.0f), 5.4976249f) * Vector3(1.0f, 0.0f, 0.0f);
    Vector3 east(1.0f, 0.0f, 0.0f);
    Vector3 north(0.0f, 1.0f, 0.0f);
    Vector3 west(-1.0f, 0.0f, 0.0f);
    Vector3 south(0.0f, -1.0f, 0.0f);

    unknown_matrices_af73a0[0].Make_Identity();
    unknown_matrices_af73a0[1] = Matrix3D(3.9268751f, slope_i);
    unknown_matrices_af73a0[2] = Matrix3D(2.3561251f, slope_i);
    unknown_matrices_af73a0[3] = Matrix3D(0.785375f, slope_i);
    unknown_matrices_af73a0[4] = Matrix3D(5.4976249f, slope_i);
    unknown_quaternions_af77d8[1] = Axis_To_Quat(diagonal5, slope_i);
    unknown_quaternions_af77d8[2] = Axis_To_Quat(diagonal3, slope_i);
    unknown_quaternions_af77d8[3] = Axis_To_Quat(diagonal1, slope_i);
    unknown_quaternions_af77d8[4] = Axis_To_Quat(diagonal7, slope_i);
    unknown_matrices_af73a0[5] = Matrix3D(3.1415f, slope_h);
    unknown_matrices_af73a0[6] = Matrix3D(1.57075f, slope_h);
    unknown_matrices_af73a0[7] = Matrix3D(0.0f, slope_h);
    unknown_matrices_af73a0[8] = Matrix3D(4.7122502f, slope_h);
    unknown_quaternions_af77d8[5] = Axis_To_Quat(west, slope_h);
    unknown_quaternions_af77d8[6] = Axis_To_Quat(north, slope_h);
    unknown_quaternions_af77d8[7] = Axis_To_Quat(east, slope_h);
    unknown_quaternions_af77d8[8] = Axis_To_Quat(south, slope_h);
    unknown_matrices_af73a0[9] = Matrix3D(3.1415f, slope_h);
    unknown_matrices_af73a0[10] = Matrix3D(1.57075f, slope_h);
    unknown_matrices_af73a0[11] = Matrix3D(0.0f, slope_h);
    unknown_matrices_af73a0[12] = Matrix3D(4.7122502f, slope_h);
    unknown_quaternions_af77d8[9] = Axis_To_Quat(west, slope_h);
    unknown_quaternions_af77d8[10] = Axis_To_Quat(north, slope_h);
    unknown_quaternions_af77d8[11] = Axis_To_Quat(east, slope_h);
    unknown_quaternions_af77d8[12] = Axis_To_Quat(south, slope_h);
    unknown_matrices_af73a0[13] = Matrix3D(3.1415f, slope_i);
    unknown_matrices_af73a0[14] = Matrix3D(1.57075f, slope_i);
    unknown_matrices_af73a0[15] = Matrix3D(0.0f, slope_i);
    unknown_matrices_af73a0[16] = Matrix3D(4.7122502f, slope_i);
    unknown_quaternions_af77d8[13] = Axis_To_Quat(west, slope_i);
    unknown_quaternions_af77d8[14] = Axis_To_Quat(north, slope_i);
    unknown_quaternions_af77d8[15] = Axis_To_Quat(east, slope_i);
    unknown_quaternions_af77d8[16] = Axis_To_Quat(south, slope_i);
    unknown_matrices_af73a0[17].Make_Identity();
    unknown_matrices_af73a0[18].Make_Identity();
    unknown_matrices_af73a0[19].Make_Identity();
    unknown_matrices_af73a0[20].Make_Identity();
    unknown_quaternions_af77d8[17].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af77d8[18].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af77d8[19].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af77d8[20].Set(0.0f, 0.0f, 0.0f, 1.0f);

    for (int facing = 0; facing < 256; facing++) {
        Matrix3D matrix;
        matrix.Make_Identity();
        matrix.Rotate_Z(facing * 0.024542969f);
        unknown_vectors_af6768[facing] = matrix * Vector3(1.0f, 0.0f, 0.0f);
        unknown_vectors_af7930[facing] = Vector3::Cross_Product(unknown_vectors_af6768[facing], Vector3(0.0f, 0.0f, 1.0f));
        Matrix3D rotation(unknown_vectors_af7930[facing], unknown_839aac);
        unknown_vectors_af6768[facing] = rotation * unknown_vectors_af6768[facing];
    }

    unknown_matrices_af8608[0].Make_Identity();
    unknown_matrices_af8608[1] = Matrix3D(4.7122502f, slope_i);
    unknown_matrices_af8608[2] = Matrix3D(3.1415f, slope_i);
    unknown_matrices_af8608[3] = Matrix3D(1.57075f, slope_i);
    unknown_matrices_af8608[4] = Matrix3D(0.0f, slope_i);
    unknown_matrices_af8608[5] = Matrix3D(3.9268751f, slope_h);
    unknown_matrices_af8608[6] = Matrix3D(2.3561251f, slope_h);
    unknown_matrices_af8608[7] = Matrix3D(0.785375f, slope_h);
    unknown_matrices_af8608[8] = Matrix3D(5.4976249f, slope_h);
    unknown_matrices_af8608[9] = Matrix3D(3.9268751f, slope_h);
    unknown_matrices_af8608[10] = Matrix3D(2.3561251f, slope_h);
    unknown_matrices_af8608[11] = Matrix3D(0.785375f, slope_h);
    unknown_matrices_af8608[12] = Matrix3D(5.4976249f, slope_h);
    unknown_matrices_af8608[13] = Matrix3D(3.9268751f, slope_i);
    unknown_matrices_af8608[14] = Matrix3D(2.3561251f, slope_i);
    unknown_matrices_af8608[15] = Matrix3D(0.785375f, slope_i);
    unknown_matrices_af8608[16] = Matrix3D(5.4976249f, slope_i);
    unknown_quaternions_af6618[0].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af6618[1] = Axis_To_Quat(south, slope_i);
    unknown_quaternions_af6618[2] = Axis_To_Quat(west, slope_i);
    unknown_quaternions_af6618[3] = Axis_To_Quat(north, slope_i);
    unknown_quaternions_af6618[4] = Axis_To_Quat(east, slope_i);
    unknown_quaternions_af6618[5] = Axis_To_Quat(diagonal5, slope_h);
    unknown_quaternions_af6618[6] = Axis_To_Quat(diagonal3, slope_h);
    unknown_quaternions_af6618[7] = Axis_To_Quat(diagonal1, slope_h);
    unknown_quaternions_af6618[8] = Axis_To_Quat(diagonal7, slope_h);
    unknown_quaternions_af6618[9] = Axis_To_Quat(diagonal5, slope_h);
    unknown_quaternions_af6618[10] = Axis_To_Quat(diagonal3, slope_h);
    unknown_quaternions_af6618[11] = Axis_To_Quat(diagonal1, slope_h);
    unknown_quaternions_af6618[12] = Axis_To_Quat(diagonal7, slope_h);
    unknown_quaternions_af6618[13] = Axis_To_Quat(diagonal5, slope_i);
    unknown_quaternions_af6618[14] = Axis_To_Quat(diagonal3, slope_i);
    unknown_quaternions_af6618[15] = Axis_To_Quat(diagonal1, slope_i);
    unknown_quaternions_af6618[16] = Axis_To_Quat(diagonal7, slope_i);
    unknown_matrices_af8608[17].Make_Identity();
    unknown_matrices_af8608[18].Make_Identity();
    unknown_matrices_af8608[19].Make_Identity();
    unknown_matrices_af8608[20].Make_Identity();
    unknown_quaternions_af6618[17].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af6618[18].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af6618[19].Set(0.0f, 0.0f, 0.0f, 1.0f);
    unknown_quaternions_af6618[20].Set(0.0f, 0.0f, 0.0f, 1.0f);

    unknown_matrix_af77a8.Make_Identity();
    unknown_matrix_af77a8.Rotate_X((float)-unknown_geometry_angle60);
    unknown_matrix_af77a8.Rotate_Z((float)-unknown_geometry_angle45);

    for (int index = 0; index < 4; index++) {
        unknown_matrices_af8538[index].Make_Identity();
    }
    unknown_matrices_af8538[0].Row[1][1] = -1.0f;
    unknown_matrices_af8538[1].Row[0][0] = 0.0f;
    unknown_matrices_af8538[1].Row[0][1] = 1.0f;
    unknown_matrices_af8538[1].Row[1][0] = 1.0f;
    unknown_matrices_af8538[1].Row[1][1] = 0.0f;
    unknown_matrices_af8538[2].Row[0][0] = -1.0f;
    unknown_matrices_af8538[3].Row[0][0] = 0.0f;
    unknown_matrices_af8538[3].Row[0][1] = -1.0f;
    unknown_matrices_af8538[3].Row[1][0] = -1.0f;
    unknown_matrices_af8538[3].Row[1][1] = 0.0f;
}
