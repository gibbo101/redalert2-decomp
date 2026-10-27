// bool UnknownPacketRequest_005cea30::unknown_send() -- 0x005CEA30
// Purpose: hands this request's fields (+0x00, +0x04, the buffer at +0x30,
// +0x08) to the object at 0x00A40A28 (0x005D00E0, with 0, 8 and 1) and
// reports whether it returned nonzero. No direct callers. Names are
// hypotheses (0x00A40A28 also receives the 0x74 message of 0x005974F0).
// @ref ?unknown_send_5d00e0@UnknownMessageSink_005cea30@@QAEHHHPAXHDHH@Z=005d00e0
// @ref ?unknown_message_sink_a40a28@@3VUnknownMessageSink_005cea30@@A=00a40a28

class UnknownMessageSink_005cea30 {
public:
    int unknown_send_5d00e0(int a, int b, void *buffer, int c, char d, int e, int f);
};

extern UnknownMessageSink_005cea30 unknown_message_sink_a40a28;

struct UnknownPacketRequest_005cea30 {
    bool unknown_send_005cea30();

    int unknown_00;
    int unknown_04;
    int unknown_08;
    char unknown_0c[0x30 - 0x0c];
    char unknown_buffer_30[1];
};

bool UnknownPacketRequest_005cea30::unknown_send_005cea30()
{
    return unknown_message_sink_a40a28.unknown_send_5d00e0(unknown_00, unknown_04, unknown_buffer_30, unknown_08, 0, 8, 1)
           != 0 ? true : false;
}
