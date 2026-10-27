// int __fastcall unknown_run_716f40(void *source) -- 0x00716F40
// Purpose: builds a local worker (0x0071BD00) over the buffers at
// 0x00AE3008 and 0x00AF4608, runs it on source (0x0071BDE0), copies its
// first four words to the globals 0x00AE3004, 0x00AF660C, 0x00AE2FE8 and
// 0x00AF6608, destroys it (0x0071BD70) and returns the run's result.
// Assumptions: the worker class (0x20 bytes; its constructor allocates
// 0x300 bytes when given no first buffer) and every name are unidentified
// placeholders.
// @ref ??0UnknownWorker_716f40@@QAE@PAX0@Z=0071bd00
// @ref ??1UnknownWorker_716f40@@QAE@XZ=0071bd70
// @ref ?Run@UnknownWorker_716f40@@QAEHPAX@Z=0071bde0
// @ref ?unknown_buffer_ae3008@@3PADA=00ae3008
// @ref ?unknown_buffer_af4608@@3PADA=00af4608
// @ref ?unknown_ae3004@@3HA=00ae3004
// @ref ?unknown_af660c@@3HA=00af660c
// @ref ?unknown_ae2fe8@@3HA=00ae2fe8
// @ref ?unknown_af6608@@3HA=00af6608

class UnknownWorker_716f40 {
public:
    UnknownWorker_716f40(void *buffer1, void *buffer2);
    ~UnknownWorker_716f40();
    int Run(void *source);

    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    char unknown_10[0x10];
};

extern char unknown_buffer_ae3008[];
extern char unknown_buffer_af4608[];
extern int unknown_ae3004;
extern int unknown_af660c;
extern int unknown_ae2fe8;
extern int unknown_af6608;

int __fastcall unknown_run_716f40(void *source)
{
    UnknownWorker_716f40 worker(unknown_buffer_ae3008, unknown_buffer_af4608);
    int result = worker.Run(source);
    unknown_ae3004 = worker.unknown_00;
    unknown_af660c = worker.unknown_04;
    unknown_ae2fe8 = worker.unknown_08;
    unknown_af6608 = worker.unknown_0c;
    return result;
}
