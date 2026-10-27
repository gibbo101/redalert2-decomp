#ifndef RA2_CONNECTION_POINTS_HPP
#define RA2_CONNECTION_POINTS_HPP
#include "shared/com_api.hpp"
#include "shared/vector_class.hpp"
#include "shared/win32_api.hpp"
struct IConnectionPointContainer;
struct IEnumConnections;
struct IEnumConnectionPoints;
struct tagCONNECTDATA { IUnknown *pUnk; unsigned long dwCookie; };
int __fastcall operator==(tagCONNECTDATA const &,tagCONNECTDATA const &);
int __fastcall operator!=(tagCONNECTDATA const &,tagCONNECTDATA const &);
struct __declspec(novtable) IConnectionPoint : public IUnknown {
 virtual HRESULT __stdcall GetConnectionInterface(GUID *)=0;
 virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer **)=0;
 virtual HRESULT __stdcall Advise(IUnknown *,unsigned long *)=0;
 virtual HRESULT __stdcall Unadvise(unsigned long)=0;
 virtual HRESULT __stdcall EnumConnections(IEnumConnections **)=0;
};
struct __declspec(novtable) IConnectionPointContainer : IUnknown {
 virtual HRESULT __stdcall EnumConnectionPoints(IEnumConnectionPoints **)=0;
 virtual HRESULT __stdcall FindConnectionPoint(GUID const &,IConnectionPoint **)=0;
};
struct __declspec(novtable) IEnumConnections : IUnknown {
 virtual HRESULT __stdcall Next(unsigned long,tagCONNECTDATA *,unsigned long *)=0;
 virtual HRESULT __stdcall Skip(unsigned long)=0;
 virtual HRESULT __stdcall Reset()=0;
 virtual HRESULT __stdcall Clone(IEnumConnections **)=0;
};
struct __declspec(novtable) IEnumConnectionPoints : IUnknown {
 virtual HRESULT __stdcall Next(unsigned long,IConnectionPoint **,unsigned long *)=0;
 virtual HRESULT __stdcall Skip(unsigned long)=0;
 virtual HRESULT __stdcall Reset()=0;
 virtual HRESULT __stdcall Clone(IEnumConnectionPoints **)=0;
};
extern "C" GUID const IID_IEnumConnections, IID_IConnectionPoint, IID_IConnectionPointContainer, IID_IEnumConnectionPoints;
extern "C" long COMReferences_00a6eb14;
class EnumConnectionsClass : public IEnumConnections {
public:
 virtual HRESULT __stdcall QueryInterface(GUID const &,void **);
 virtual unsigned long __stdcall AddRef();
 virtual unsigned long __stdcall Release();
 virtual HRESULT __stdcall Next(unsigned long,tagCONNECTDATA *,unsigned long *);
 virtual HRESULT __stdcall Skip(unsigned long);
 virtual HRESULT __stdcall Reset();
 virtual HRESULT __stdcall Clone(IEnumConnections **);
 EnumConnectionsClass(DynamicVectorClass<tagCONNECTDATA> const &);
 EnumConnectionsClass(EnumConnectionsClass const &);
 ~EnumConnectionsClass();
 DynamicVectorClass<tagCONNECTDATA> Connections; // +04
 int Position; // +1c
 long RefCount; // +20
};
class ConnectionPointClass : public IConnectionPoint {
public:
 virtual HRESULT __stdcall QueryInterface(GUID const &,void **);
 virtual unsigned long __stdcall AddRef();
 virtual unsigned long __stdcall Release();
 virtual HRESULT __stdcall GetConnectionInterface(GUID *);
 virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer **);
 virtual HRESULT __stdcall Advise(IUnknown *,unsigned long *);
 virtual HRESULT __stdcall Unadvise(unsigned long);
 virtual HRESULT __stdcall EnumConnections(IEnumConnections **);
 ConnectionPointClass(GUID const &,IUnknown *);
 ~ConnectionPointClass();
 GUID InterfaceID; // +04
 long RefCount; // +14
 IUnknown *Container; // +18
 DynamicVectorClass<tagCONNECTDATA> Connections; // +1c
};
class EnumConnectionPointsClass : public IEnumConnectionPoints {
public:
 virtual HRESULT __stdcall QueryInterface(GUID const &,void **);
 virtual unsigned long __stdcall AddRef();
 virtual unsigned long __stdcall Release();
 virtual HRESULT __stdcall Next(unsigned long,IConnectionPoint **,unsigned long *);
 virtual HRESULT __stdcall Skip(unsigned long);
 virtual HRESULT __stdcall Reset();
 virtual HRESULT __stdcall Clone(IEnumConnectionPoints **);
 EnumConnectionPointsClass(DynamicVectorClass<IConnectionPoint *> const &);
 EnumConnectionPointsClass(EnumConnectionPointsClass const &);
 ~EnumConnectionPointsClass();
 int Position; // +04
 long RefCount; // +08
 DynamicVectorClass<IConnectionPoint *> Points; // +0c
};
#endif




