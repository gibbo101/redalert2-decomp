// PacketClass (Packet.cpp, 0x00602A60-0x00602FD0): the tagged-field packet of the Westwood Online
// messages (TibSun packet.h member order; the RA2 field and constructor bodies are not recovered).
// Only the members the recovered callers use are declared.
#ifndef RA2_SHARED_PACKET_HPP
#define RA2_SHARED_PACKET_HPP

class PacketClass {
public:
    PacketClass(char *buffer);                                         // 0x00602AA0 (parses a received block)
    ~PacketClass();                                                    // 0x00602A60 (deletes the fields)

    bool Get_Field(char const *id, unsigned char &data);               // 0x00602D60
    bool Get_Field(char const *id, unsigned int &data);                // 0x00602F10
    bool Get_Field(char const *id, void *data, int &length);           // 0x00602F60 (length in/out)

    int unknown_00;                                                    // +0x00
    void *Head;                                                        // +0x04 field list
    void *Current;                                                     // +0x08
};

#endif
