// Matrix3D BounceClass::unknown_matrix_436fc0() const (0x00436FC0; TibSun Get_Matrix): the
// tumble rotation as a matrix (Matrix3D's copy constructor is inline here, RA2_MATRIX3D_INLINE_COPY).
Matrix3D BounceClass::unknown_matrix_436fc0() const
{
    return Build_Matrix3D((Quaternion const &)unknown_30);
}
// @ref ?Build_Matrix3D@@YI?AVMatrix3D@@ABVQuaternion@@@Z=00622eb0
