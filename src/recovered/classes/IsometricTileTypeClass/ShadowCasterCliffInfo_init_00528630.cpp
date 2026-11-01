// A cliff or slope tile's shadow caster: the shadow frame, which image and its pixel offset
// (TibSun ShadowCasterInfo; the constructor's out-of-line copy is 0x0052E660).
struct ShadowCasterInfo {
    int Frame;
    int Index;
    int XOffset;
    int YOffset;

    ShadowCasterInfo(int frame = 0, int index = 0, int x = 0, int y = 0) : Frame(frame), Index(index), XOffset(x), YOffset(y) {}
};

// The cliff tiles' shadow casters (0x00A6E108; initializer 0x00528630).
ShadowCasterInfo ShadowCasterCliffInfo[40] = {
    ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(),
    ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(),
    ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(),
    ShadowCasterInfo(), ShadowCasterInfo(),
    ShadowCasterInfo(0, 0, 30, 30),
    ShadowCasterInfo(0, 0, 30, 30),
    ShadowCasterInfo(0, 0, 30, 30),
    ShadowCasterInfo(1, 0, 30, 30),
    ShadowCasterInfo(1, 0, 30, 30),
    ShadowCasterInfo(2, 1, 60, 15),
    ShadowCasterInfo(3, 1, 60, 15),
    ShadowCasterInfo(4, 1, 60, 15),
    ShadowCasterInfo(5, 0, 90, 30),
    ShadowCasterInfo(6, 0, 60, 15),
    ShadowCasterInfo(7, 1, 30, 0),
    ShadowCasterInfo(8, 0, 60, 15),
    ShadowCasterInfo(9, 0, 60, 15),
    ShadowCasterInfo(10, 1, 0, -15),
    ShadowCasterInfo(11, 1, 0, -15),
    ShadowCasterInfo(12, 0, 60, 15),
    ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(), ShadowCasterInfo(),
    ShadowCasterInfo(), ShadowCasterInfo(),
};
// @ref ??0ShadowCasterInfo@@QAE@HHHH@Z=0052e660
// @ref ?ShadowCasterCliffInfo@@3PAUShadowCasterInfo@@A=00a6e108
