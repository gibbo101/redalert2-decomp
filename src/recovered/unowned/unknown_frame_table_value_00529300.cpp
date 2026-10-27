// int UnknownImageOwner_00529300::unknown_frame_table_value(int frame) -- 0x00529300
// Purpose: asks the object (virtual slot 39, +0x9C: the image data) for the
// frame record of `frame` modulo the frame count and returns the entry of
// the int table at 0x007DE4EC selected by the record's signed byte at
// +0x29; 0 without image or record. No direct callers. Owner and record
// types not identified (same image shape as 0x0052DFA0).
// @ref ?unknown_table_7de4ec@@3PAHA=007de4ec

extern int unknown_table_7de4ec[];

struct UnknownFrame_00529300 {
    int unknown_00;
    int unknown_04;
    int unknown_08[4];
    int unknown_18;
    int unknown_1c[2];
    unsigned char unknown_flags_24;
    char unknown_25[4];
    signed char unknown_29;
};

struct UnknownImage_00529300 {
    int unknown_count_a;
    int unknown_count_b;
    int unknown_08[2];
    UnknownFrame_00529300 *frames[1];    // +0x10
};

class UnknownImageOwner_00529300 {
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
    virtual UnknownImage_00529300 *unknown_image_slot39();    // +0x9C
    int unknown_frame_table_value_00529300(int frame);
};

int UnknownImageOwner_00529300::unknown_frame_table_value_00529300(int frame)
{
    UnknownImage_00529300 *image = unknown_image_slot39();
    if (image != 0) {
        UnknownFrame_00529300 *record = image->frames[frame % (image->unknown_count_b * image->unknown_count_a)];
        if (record != 0) {
            return unknown_table_7de4ec[record->unknown_29];
        }
    }
    return 0;
}
