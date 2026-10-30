extern float unknown_839aac;
extern Vector3 unknown_839ab0;
extern Vector3 unknown_839a60;

void __stdcall Unknown_00717FB0(float angle)
{
    Matrix3D matrix;
    matrix.Make_Identity();
    unknown_839aac = angle;
    matrix.Rotate_Y(angle);
    unknown_839ab0 = matrix * Vector3(-0.70710599f, -0.70710599f, 0.0f);
    unknown_839a60 = Vector3(unknown_839ab0.X * -6.0f, 0.0f, 0.0f);
}
