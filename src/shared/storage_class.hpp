// StorageClass: four tiberium amounts (0x10 bytes; RTTI-less value class; TS name
// StorageClass). Methods are out of line in another unit (0x0069ADA0..0x0069AE50).
// Used by HouseClass (Tiberium) and TechnoClass (+0x294, the harvested load).
#ifndef RA2_SHARED_STORAGE_CLASS_HPP
#define RA2_SHARED_STORAGE_CLASS_HPP

class NoInitClass;

class StorageClass {
public:
    StorageClass();                         // 0x0069ADA0
    StorageClass(NoInitClass const &noinit) {}
    int Get_Total_Value() const;            // 0x0069ADC0 (amounts times their values)
    float Get_Total_Amount() const;         // 0x0069AE10
    float Get_Amount(int type) const;       // 0x0069AE40 (the amount of one type; hypothesis)
    float Add_Amount(float amount, int type);   // 0x0069AE50 (returns the new amount; hypothesis)
    float Remove_Amount(float amount, int type);    // 0x0069AE70 (at most what is there; returns the amount removed)
    int First_Used_Slot() const;            // 0x0069AFE0 (the first type with a positive amount, or -1)
    StorageClass operator+=(StorageClass const &that);  // 0x0069AF00 (adds each amount; returns a copy)
    StorageClass operator-=(StorageClass const &that);  // 0x0069AFA0 (subtracts each amount; returns a copy)
#ifdef STORAGE_CLASS_UNIT
    StorageClass operator+(StorageClass const &that) const;   // 0x0069AEA0 (the sums of each amount)
    StorageClass operator-(StorageClass const &that) const;   // 0x0069AF40 (the differences of each amount)
#endif

    float Amounts[4];
};

#endif
