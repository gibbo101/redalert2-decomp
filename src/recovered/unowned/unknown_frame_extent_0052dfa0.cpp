// int UnknownImageOwner_0052dfa0::unknown_frame_extent(int frame) -- 0x0052DFA0
// Purpose: asks the object (virtual slot 39, +0x9C) for its image data and
// returns entry +0x18 minus entry +0x04 of the given frame record when the
// frame exists and its flag bit 0 (+0x24) is set; 0 otherwise. No direct
// callers (alignment-bounded entry). Owner and record types not identified.
struct UnknownFrame_0052dfa0 {
    int unknown_00;
    int unknown_04;
    int unknown_08[4];
    int unknown_18;
    int unknown_1c[2];
    unsigned char unknown_flags_24;
};

struct UnknownImage_0052dfa0 {
    int unknown_count_a;
    int unknown_count_b;
    int unknown_08[2];
    UnknownFrame_0052dfa0 *frames[1];    // +0x10
};

class UnknownImageOwner_0052dfa0 {
public:
    virtual void unknown_slot00(); virtual void unknown_slot01(); virtual void unknown_slot02();
    virtual void unknown_slot03(); virtual void unknown_slot04(); virtual void unknown_slot05();
    virtual void unknown_slot06(); virtual void unknown_slot07(); virtual void unknown_slot08();
    virtual void unknown_slot09(); virtual void unknown_slot10(); virtual void unknown_slot11();
    virtual void unknown_slot12(); virtual void unknown_slot13(); virtual void unknown_slot14();
    virtual void unknown_slot15(); virtual void unknown_slot16(); virtual void unknown_slot17();
    virtual void unknown_slot18(); virtual void unknown_slot19(); virtual void unknown_slot20();
    virtual void unknown_slot21(); virtual void unknown_slot22(); virtual void unknown_slot23();
    virtual void unknown_slot24(); virtual void unknown_slot25(); virtual void unknown_slot26();
    virtual void unknown_slot27(); virtual void unknown_slot28(); virtual void unknown_slot29();
    virtual void unknown_slot30(); virtual void unknown_slot31(); virtual void unknown_slot32();
    virtual void unknown_slot33(); virtual void unknown_slot34(); virtual void unknown_slot35();
    virtual void unknown_slot36(); virtual void unknown_slot37(); virtual void unknown_slot38();
    virtual UnknownImage_0052dfa0 *unknown_image_slot39();    // +0x9C
    int unknown_frame_extent_0052dfa0(int frame);
};

int UnknownImageOwner_0052dfa0::unknown_frame_extent_0052dfa0(int frame)
{
    UnknownImage_0052dfa0 *image = unknown_image_slot39();
    if (image != 0 && frame < image->unknown_count_b * image->unknown_count_a) {
        UnknownFrame_0052dfa0 *record = image->frames[frame];
        if (record != 0 && (record->unknown_flags_24 & 1) != 0) {
            return record->unknown_18 - record->unknown_04;
        }
    }
    return 0;
}
