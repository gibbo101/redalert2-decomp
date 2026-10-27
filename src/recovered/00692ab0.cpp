extern "C" void* __cdecl allocate_692ab0(unsigned int);

class FactoryObject_692ab0 {
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
 FactoryObject_692ab0* init(unsigned int);
};
extern "C" int __stdcall factory_692ab0(unsigned int unused,void* outer,const void* identifier,void** output) {
 if(!output) return (int)0x80070057u;
 *output=0;
 if(outer) return (int)0x80040110u;
 FactoryObject_692ab0* object=(FactoryObject_692ab0*)allocate_692ab0(208);
 if(object) object=object->init(0);
 if(!object) return (int)0x8007000eu;
 int result=object->query(identifier,output);
 if(result<0) object->destroy(1);
 return result;
}
