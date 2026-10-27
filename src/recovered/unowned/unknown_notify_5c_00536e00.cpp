// void UnknownNotifyOwner_00536e00::unknown_notify(UnknownListener_00536e00 *listener) -- 0x00536E00
// Purpose: when the object at +0x5C is set, passes it to the listener's
// virtual slot 1 with 0 and 1. No direct callers. Types not identified.
class UnknownListener_00536e00 {
public:
    virtual void unknown_slot0();
    virtual void unknown_slot1(void *object, int a, int b);
};

struct UnknownNotifyOwner_00536e00 {
    void unknown_notify_00536e00(UnknownListener_00536e00 *listener);

    char unknown_00[0x5c];
    void *unknown_5c;
};

void UnknownNotifyOwner_00536e00::unknown_notify_00536e00(UnknownListener_00536e00 *listener)
{
    if (unknown_5c != 0) {
        listener->unknown_slot1(unknown_5c, 0, 1);
    }
}
