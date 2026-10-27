// 0x0058DB20: frees the block at +0x08 and, when bit 0 of the flags is set,
// the object itself, returning the object (a scalar-deleting-destructor
// shape without a vtable store). Callers: 0x00582954, 0x00583B5F,
// 0x006E9198 and others pass 1.
// @ref ??3@YAXPAX@Z=00781d3b

class UnknownOwner_58db20 {
public:
    UnknownOwner_58db20 *Release_58db20(unsigned char flags);

    unsigned char unknown_00[8];
    void *unknown_08;
};

UnknownOwner_58db20 *UnknownOwner_58db20::Release_58db20(unsigned char flags)
{
    delete unknown_08;
    if (flags & 1) {
        delete this;
    }
    return this;
}
