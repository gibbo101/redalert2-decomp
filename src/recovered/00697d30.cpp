extern "C" void* __cdecl allocate_697d30(unsigned int);

class FactoryObject_697d30 {
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
 FactoryObject_697d30* init(unsigned int);
};
extern "C" int __stdcall factory_697d30(unsigned int unused,void* outer,const void* identifier,void** output) {
 if(!output) return (int)0x80070057u;
 *output=0;
 if(outer) return (int)0x80040110u;
 FactoryObject_697d30* object=(FactoryObject_697d30*)allocate_697d30(736);
 if(object) object=object->init(0);
 if(!object) return (int)0x8007000eu;
 int result=object->query(identifier,output);
 if(result<0) object->destroy(1);
 return result;
}
