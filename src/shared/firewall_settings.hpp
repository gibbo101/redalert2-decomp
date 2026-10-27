// FirewallSettings: the firewall detection state kept by the multiplayer
// network options (members 0x005B9E80, 0x005BA210, 0x005BA280, 0x005BA2C0;
// layout from the INI load/save pair; names are hypotheses).
#ifndef RA2_SHARED_FIREWALL_SETTINGS_HPP
#define RA2_SHARED_FIREWALL_SETTINGS_HPP

class FirewallSettings {
public:
    void Detect_And_Save_005b9e80();                // 0x005B9E80 (when type is still 0)
    void Save_005ba210();                           // 0x005BA210
    int Detect_005ba2c0(bool *found);               // 0x005BA2C0 (thiscall, one stack argument)

    int unknown_00;                                 // +0x00 detected type; [MultiPlayer] FirewallSettings
    int unknown_04;                                 // +0x04 loaded by 0x005BA280
    int unknown_08;                                 // +0x08 [MultiPlayer] FirewallDelta
    int unknown_0c;                                 // +0x0C loaded by 0x005BA280
};

#endif
