// Unknown53E330Owner::unknown_53e330(object, flag) (0x0053E330; LogicClass vtable 0x0079A8EC slot 7)
// True once the object's +0x84 latch is set: tries 0x005348A0 and latches on success.
// @ref ?unknown_5348a0@@YG_NPAUUnknown53E330Object@@D@Z=005348a0
struct Unknown53E330Object {
    char unknown_pad[0x84];
    bool unknown_84;
};
bool __stdcall unknown_5348a0(Unknown53E330Object *object, char unknown);

class Unknown53E330Owner {
public:
    bool unknown_53e330(Unknown53E330Object *object, char unknown);
};

bool Unknown53E330Owner::unknown_53e330(Unknown53E330Object *object, char unknown)
{
    if (object->unknown_84) {
        return true;
    }
    if (unknown_5348a0(object, unknown)) {
        object->unknown_84 = true;
        return true;
    }
    return false;
}
