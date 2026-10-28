// ConnManClass: the abstract connection manager (vtable 0x007A474C) that
// IPXManagerClass and NullModemClass implement.
#ifndef RA2_SHARED_CONN_MAN_HPP
#define RA2_SHARED_CONN_MAN_HPP

class ConnManClass {
public:
    virtual ~ConnManClass() {}                                          // slot 0 (scalar deleting destructor 0x00527870)
    virtual int Service() = 0;                                          // 1
    virtual int Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id) = 0;   // 2
    virtual int Get_Private_Message(void *buf, int *buflen, int *conn_id) = 0;   // 3
    virtual int Num_Connections() = 0;                                  // 4
    virtual int Connection_ID(int index) = 0;                           // 5
    virtual int Connection_Index(int id) = 0;                           // 6
    virtual int Global_Num_Send() = 0;                                  // 7
    virtual int Global_Num_Receive() = 0;                               // 8
    virtual int Private_Num_Send(int id) = 0;                           // 9
    virtual int Private_Num_Receive(int id) = 0;                        // 10
    virtual void Reset_Response_Time(bool clear) = 0;                   // 11
    virtual unsigned long Response_Time() = 0;                          // 12
    virtual void Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global) = 0;   // 13
    virtual void unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout) = 0;   // 14
    virtual void Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount) = 0;   // 15
};

#endif
