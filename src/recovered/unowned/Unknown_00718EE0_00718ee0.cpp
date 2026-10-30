extern float unknown_angles_7f9d84[];

void __fastcall Unknown_00718EE0(Matrix3D *matrix, int index, int angle)
{
    Matrix3D rotation(unknown_vectors_af7930[index], unknown_angles_7f9d84[angle]);
    *matrix = *matrix * rotation;
    matrix->Translate(unknown_vectors_af6768[index] * -3.0f);
    matrix->Translate(0.0f, 0.0f, 3.0f);
}
