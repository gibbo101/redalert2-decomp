// // Whether no speech waits (inline).
static inline bool Speech_Lists_Empty()
{
    if (unknown_vox_list_ad0868.Prev != &unknown_vox_list_ad0868
            || unknown_vox_list_ad0890.Prev != &unknown_vox_list_ad0890
            || unknown_vox_pending_ad0948 != 0) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        AudioListNode *list = &unknown_vox_lists_ad08e0[i];
        if (list->Prev != list) {
            return false;
        }
    }
    return true;
}

bool Speech_Is_Playing()
{
    Speech_Update();
    return unknown_vox_stream_ad095c != 0
            && (Audio_Stream_Is_Playing(unknown_vox_stream_ad095c) || !Speech_Lists_Empty());
}
