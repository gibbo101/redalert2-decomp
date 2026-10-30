// Sets the eight corners of each tailer's box from its size, centered on the
// origin.
void UnknownPairFirst::unknown_719f60()
{
    for (unsigned index = 0; index < unknown_08; index++) {
        UnknownVoxelTailer *tailer = &unknown_14[index];
        tailer->unknown_40[0] = Vector3(tailer->unknown_a0 * 0.5f, tailer->unknown_a1 * 0.5f, -tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[1] = Vector3(tailer->unknown_a0 * 0.5f, -tailer->unknown_a1 * 0.5f, -tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[2] = Vector3(-tailer->unknown_a0 * 0.5f, -tailer->unknown_a1 * 0.5f, -tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[3] = Vector3(-tailer->unknown_a0 * 0.5f, tailer->unknown_a1 * 0.5f, -tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[4] = Vector3(tailer->unknown_a0 * 0.5f, tailer->unknown_a1 * 0.5f, tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[5] = Vector3(tailer->unknown_a0 * 0.5f, -tailer->unknown_a1 * 0.5f, tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[6] = Vector3(-tailer->unknown_a0 * 0.5f, -tailer->unknown_a1 * 0.5f, tailer->unknown_a2 * 0.5f);
        tailer->unknown_40[7] = Vector3(-tailer->unknown_a0 * 0.5f, tailer->unknown_a1 * 0.5f, tailer->unknown_a2 * 0.5f);
    }
}
