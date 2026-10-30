// Draws a section: fills the span drawer's parameters from the section's
// tailer and the view's corner choice (origin corner and the three edge
// corners, in 8.8 fixed point; the z steps only when unknown_af6610) and calls
// the drawer chosen by the view's flags, 2 (unknown_af6610), 4
// (unknown_af6614) and 8 (no normal table).
void UnknownPairFirst::unknown_719940(UnknownVoxelDrawState *state, Vector3 const *origin)
{
    UnknownVoxelTailer *tailer = unknown_719860(state->unknown_04, state->unknown_08);
    unsigned char size_x = tailer->unknown_a0;
    unsigned char size_y = tailer->unknown_a1;
    unsigned char size_z = tailer->unknown_a2;
    VoxelFuncArgumentStruct parameters;
    parameters.XSize = size_x;
    parameters.YSize = size_y;
    parameters.ZSize = size_z;
    parameters.StartOffset = tailer->unknown_00;
    parameters.EndOffset = tailer->unknown_04;
    parameters.DataOffset = tailer->unknown_08;
    Vector3 const *corner = &state->unknown_28[unknown_views_7f9e60[state->unknown_0c].unknown_04];
    Vector3 const *corner_x = &state->unknown_28[unknown_views_7f9e60[state->unknown_0c].unknown_08];
    Vector3 const *corner_y = &state->unknown_28[unknown_views_7f9e60[state->unknown_0c].unknown_0c];
    Vector3 const *corner_z = &state->unknown_28[unknown_views_7f9e60[state->unknown_0c].unknown_10];
    parameters.StrideX = unknown_views_7f9e60[state->unknown_0c].unknown_1c;
    parameters.StrideY = unknown_views_7f9e60[state->unknown_0c].unknown_20 * size_x;
    parameters.StartIndex = unknown_views_7f9e60[state->unknown_0c].unknown_18 * (size_y - 1) * size_x + unknown_views_7f9e60[state->unknown_0c].unknown_14 * (size_x - 1);
    parameters.TransformMatrix[0].I = (short)((corner->X + 128.0f - origin->X) * 256.0f);
    parameters.TransformMatrix[0].J = (short)((corner->Y + 128.0f - origin->Y) * 256.0f);
    parameters.TransformMatrix[0].K = (short)((corner->Z + 128.0f - origin->Z) * 256.0f);
    parameters.TransformMatrix[1].I = (short)((corner_x->X - corner->X) / size_x * 256.0f);
    parameters.TransformMatrix[2].I = (short)((corner_y->X - corner->X) / size_y * 256.0f);
    parameters.TransformMatrix[3].I = (short)((corner_z->X - corner->X) / size_z * 256.0f);
    parameters.TransformMatrix[1].J = (short)((corner_x->Y - corner->Y) / size_x * 256.0f);
    parameters.TransformMatrix[2].J = (short)((corner_y->Y - corner->Y) / size_y * 256.0f);
    parameters.TransformMatrix[3].J = (short)((corner_z->Y - corner->Y) / size_z * 256.0f);
    if (unknown_af6610) {
        parameters.TransformMatrix[1].K = (short)((corner_x->Z - corner->Z) / size_x * 256.0f);
        parameters.TransformMatrix[2].K = (short)((corner_y->Z - corner->Z) / size_y * 256.0f);
        parameters.TransformMatrix[3].K = (short)((corner_z->Z - corner->Z) / size_z * 256.0f);
    }
    int drawer = unknown_views_7f9e60[state->unknown_0c].unknown_00;
    if (unknown_af6610) {
        drawer |= 2;
    }
    if (unknown_af6614) {
        drawer |= 4;
    }
    if (tailer->unknown_a3 == 0) {
        drawer |= 8;
    }
    unknown_drawers_7f9de0[drawer](&parameters);
}
