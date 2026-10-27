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

    float Amounts[4];
};

#endif
