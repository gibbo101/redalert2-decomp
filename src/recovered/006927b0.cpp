extern "C" void* __cdecl allocate_6927b0(unsigned int);
extern "C" unsigned char data_6927b0_0[];
class FactoryObject_6927b0 {
 public:
 virtual int __stdcall query(const void*,void**);
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void destroy(unsigned int);
 FactoryObject_6927b0* init(const unsigned char*,unsigned int);
};
extern "C" int __stdcall factory_6927b0(unsigned int unused,void* outer,const void* identifier,void** output) {
 if(!output) return (int)0x80070057u;
 *output=0;
 if(outer) return (int)0x80040110u;
 FactoryObject_6927b0* object=(FactoryObject_6927b0*)allocate_6927b0(452);
 if(object) object=object->init(data_6927b0_0,0);
 if(!object) return (int)0x8007000eu;
 int result=object->query(identifier,output);
 if(result<0) object->destroy(1);
 return result;
}
