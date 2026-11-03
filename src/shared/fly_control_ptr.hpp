// The Fly unit's IFlyControl COM pointer instance, with no Win32 or game layouts.
// The interface is complete where the reference-management bodies are defined.
#ifndef RA2_SHARED_FLY_CONTROL_PTR_HPP
#define RA2_SHARED_FLY_CONTROL_PTR_HPP
struct GUID;
struct IFlyControl;
class FootClass;
extern "C" GUID const unknown_uuid_7d80a8;
void __stdcall _com_issue_error(long result);
template<class Interface,GUID const *iid> class UnknownComPtr;
template<> class UnknownComPtr<IFlyControl,&unknown_uuid_7d80a8> {
public:
    UnknownComPtr() : Pointer(0) {}
    UnknownComPtr(UnknownComPtr const &other);
    ~UnknownComPtr();
    operator IFlyControl *() const { return Pointer; }
    IFlyControl *operator->() const { return Pointer; }
    IFlyControl *Checked() const {
        if (!Pointer) _com_issue_error((long)0x80004003);
        return Pointer;
    }
    void Release_Held();
    template<class Other> long Query_Held(Other other) {
        IFlyControl *pointer;
        long result=other->QueryInterface(unknown_uuid_7d80a8,(void**)&pointer);
        if (result<0) {
            Release_Held();
            Pointer=0;
        } else {
            IFlyControl *attached=pointer;
            Release_Held();
            Pointer=attached;
        }
        return result;
    }
    void Attach(IFlyControl *pointer);
    UnknownComPtr &operator=(IFlyControl *pointer);
    long Query_From(FootClass * const &other);
    bool operator==(int null_value) const;
    IFlyControl *Pointer;
};
#endif
