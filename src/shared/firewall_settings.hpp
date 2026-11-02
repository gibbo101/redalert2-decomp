// FirewallSettings: the firewall detection state kept by the multiplayer
// network options (members 0x005B9E80, 0x005BA210, 0x005BA280, 0x005BA2C0;
// layout from the INI load/save pair; names are hypotheses).
#ifndef RA2_SHARED_FIREWALL_SETTINGS_HPP
#define RA2_SHARED_FIREWALL_SETTINGS_HPP

class IPXAddressClass;

#pragma pack(push, 1)
// The port mangler query and reply (0x38 bytes; 0x005B9F90 sends one, 0x005BA0D0 waits for the
// reply; both use a 456-byte buffer; names are hypotheses).
struct ManglerPacket {
    int Type;                           // +0x00 0x2B query, 0x2C reply
    char Name[0x2B];                    // +0x04 "WW"
    unsigned short SeenPort;            // +0x2F the port the mangler saw the query come from
    unsigned long SeenAddress;          // +0x31
    unsigned short Port;                // +0x35 the port the query was sent from
    bool unknown_37;                    // +0x37
};
#pragma pack(pop)

class FirewallSettings {
public:
    FirewallSettings();                             // 0x005B9E60 (all zero; the global's initializer 0x005B9E40 expands it)
    void Detect_And_Save_005b9e80();                // 0x005B9E80 (when type is still 0)
#ifdef FIREWALL_SETTINGS_DECLARE_CLEAR
    // Clears the detected type (0x005B9E70); MainOpt calls it after changing network settings.
    void Clear_005b9e70();
#endif
    void Save_005ba210();                           // 0x005BA210
    void Load_005ba280();                           // 0x005BA280 (Read_MultiPlayer_Settings calls it once)
    int Detect_005ba2c0(bool *found);               // 0x005BA2C0 (thiscall, one stack argument)

    // Sends a mangler query from port to address and waits up to 180 ticks for it to leave (0x005B9F90).
    bool Send_Mangler_Query(IPXAddressClass *address, unsigned short port, int packet_id, bool flag);
    // Waits (60 ticks, or time) for the mangler's reply to packet_id; the port it saw, or 0 (0x005BA0D0).
    unsigned short Wait_For_Mangler_Reply(int packet_id, int time);
    int Connection_Step_005baf20(int flags); // connection rank from flag bits, 0x005BAF20
    int Connection_Weight_005baee0(unsigned char flags);   // 0x005BAEE0 the weighted sum of the flag bits
#ifdef RA2_FIREWALL_SETTINGS_UNIT
    // The next source port from the pool: steps PortPool (wrapping past 0xFFFF to 0x800) until the
    // UDP transport can open a spare socket on it, 256 tries at most (0x005B9F10; expanded in 0x005BAF50
    // and twice in 0x005BA2C0).
    unsigned short Get_Next_Port(int step);
    // The port a NAT maps port to, predicted from a mangler query (0x005BAF50; called from 0x0074E87B).
    unsigned short Get_Mangled_Port(unsigned short port);
    // The NAT's port allocation delta from four queried ports and their mangled ports (sorted together):
    // relative (deltas of mangled - original) or absolute, and whether it is sequential (0x005BAC50; Detect).
    int Get_Allocation_Delta(int count, unsigned short *original_ports, unsigned short *ports, bool *relative, bool *sequential);
#endif

    int unknown_00;                                 // +0x00 detected type; [MultiPlayer] FirewallSettings
    int unknown_04;                                 // +0x04 loaded by 0x005BA280
    int unknown_08;                                 // +0x08 [MultiPlayer] FirewallDelta
    int unknown_0c;                                 // +0x0C loaded by 0x005BA280
#ifdef RA2_FIREWALL_SETTINGS_UNIT
    // Declared only for the firewall unit 0x005B9C50 (RA2_FIREWALL_SETTINGS_UNIT, set by its first source);
    // the object is 0x14 bytes.
    int PortPool;                                   // +0x10 the last source port handed out (0x00A71B28;
                                                    // Read_MultiPlayer_Settings: unknown_port_pool_a71b28)
#endif
};

// The game's firewall settings (0x00A71B18; dynamic initializer 0x005B9E40).
extern FirewallSettings unknown_firewall_a71b18;

#endif
