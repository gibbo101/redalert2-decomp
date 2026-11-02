// int __fastcall unknown_last_used_count_0069a110(int const *slots, int count) (0x0069A110; no inventory row, no
// direct callers): one past the index of the last nonzero entry of slots[0..count), 0 when all are zero.
int __fastcall unknown_last_used_count_0069a110(int const *slots, int count)
{
    int result = 0;
    for (int index = 0; index < count; index++) {
        if (slots[index] != 0) {
            result = index + 1;
        }
    }
    return result;
}
