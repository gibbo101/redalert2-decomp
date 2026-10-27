#ifndef RA2_FACTORY_CLASS_HPP
#define RA2_FACTORY_CLASS_HPP
#include "shared/abstract.hpp"
#include "shared/anim.hpp"
#include "shared/techno.hpp"
// FactoryClass: RTTI AbstractClass at +0 and StageClass at +0x24.
// Reuses the real StageClass and StageTimerClass from shared/anim.hpp.
// Partial layout from the factory state methods 0x004B95E0-0x004B9EB0.
// Flags and special-production state retain unknown names until evidenced.
class FactoryClass : public AbstractClass, public StageClass {
public:
 FactoryClass();
 FactoryClass(NoInitClass const &noinit) : AbstractClass(noinit),StageClass(noinit) {}
 virtual ~FactoryClass();
 virtual HRESULT __stdcall Load(IStream *stream);
 virtual HRESULT __stdcall Save(IStream *stream,BOOL clear_dirty);
 virtual int Kind_Of() const;
 virtual int Size_Of() const;
 virtual void AI();
 virtual void Compute_CRC(WWCRCEngine &crc) const;
 bool Start_Production_004B9670(bool suspend);
 int Production_Rate_004B9780() const;
 virtual void Detach(AbstractClass *target,bool all=true);
 virtual HRESULT __stdcall GetClassID(GUID *id);
 void Set_Object_004B95E0(TechnoClass *object);
 bool Suspend_004B9630(bool value);
 bool Is_Complete_004B9900() const;
 int Cost_Per_Tick_004B9950() const;
 bool Release_Completed_004B9970();
 void Start_Next_Queued_004B9D70(); // original114-byte queue-start routine
 bool Delete_Queued_004B9DF0(TechnoTypeClass *type);
 int Count_Type_004B9E40(TechnoTypeClass *type) const;
 bool Has_Queued_004B9E80(TechnoTypeClass *type) const;
 bool Abandon_Production_004B97C0(); // 004b97c0
 static void __fastcall Update_Rates(HouseClass *owner); // 004b9eb0
 DynamicVectorClass<TechnoTypeClass *> Queue; // +3c, pointer queue (RTTI at the neighboring container methods)
 TechnoClass *Object; // +54
 bool unknown_58;
 bool unknown_59;
 char unknown_5a[2];
 int UnspentCost; // +5c, subtracted from the type cost on refund
 int unknown_60;
 int unknown_64;
 HouseClass *Owner; // +68
 bool unknown_6c;
 bool unknown_6d;
};
extern DynamicVectorClass<FactoryClass *> Factories; // 00a35e90
#endif
