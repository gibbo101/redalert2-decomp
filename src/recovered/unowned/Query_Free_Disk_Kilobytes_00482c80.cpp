#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
typedef void *HMODULE;
typedef int (WINAPI *FARPROC)();
WIN32_IMPORT HMODULE WINAPI GetModuleHandleA(char const *name);
WIN32_IMPORT FARPROC WINAPI GetProcAddress(HMODULE module,char const *name);
WIN32_IMPORT BOOL WINAPI GetDiskFreeSpaceA(char const *root,DWORD *sectors,DWORD *bytes,DWORD *free_clusters,DWORD *total_clusters);
typedef BOOL (WINAPI *QueryDiskSpaceFn)(char const *,LARGE_INTEGER *,LARGE_INTEGER *,LARGE_INTEGER *);
extern double const disk_high_word_scale_0079de10;
extern double const disk_bytes_to_kb_0079de08;
// @ref ?disk_high_word_scale_0079de10@@3NB=0079de10
// @ref ?disk_bytes_to_kb_0079de08@@3NB=0079de08
extern char const disk_check_log_007d3680[];
// @ref ?disk_check_log_007d3680@@3QBDB=007d3680
extern char const disk_kernel_module_007d3670[];
// @ref ?disk_kernel_module_007d3670@@3QBDB=007d3670
extern char const disk_extended_name_007d365c[];
// @ref ?disk_extended_name_007d365c@@3QBDB=007d365c
extern char const disk_extended_log_007d3640[];
// @ref ?disk_extended_log_007d3640@@3QBDB=007d3640
extern char const disk_query_error_007d360c[];
// @ref ?disk_query_error_007d360c@@3QBDB=007d360c
extern char const disk_free_log_007d35f0[];
// @ref ?disk_free_log_007d35f0@@3QBDB=007d35f0
extern char const disk_proc_error_007d35c0[];
// @ref ?disk_proc_error_007d35c0@@3QBDB=007d35c0
extern char const disk_module_error_007d3590[];
// @ref ?disk_module_error_007d3590@@3QBDB=007d3590
// Preserves the original signed interpretation of both 32-bit output halves.
unsigned int Query_Free_Disk_Kilobytes_00482c80()
{
    Debug_Printf(disk_check_log_007d3680);
    HMODULE module=GetModuleHandleA(disk_kernel_module_007d3670);
    if (module) {
        QueryDiskSpaceFn query=(QueryDiskSpaceFn)GetProcAddress(module,disk_extended_name_007d365c);
        if (query) {
            Debug_Printf(disk_extended_log_007d3640);
            LARGE_INTEGER available;
            LARGE_INTEGER total_free;
            LARGE_INTEGER total;
            if (!(unsigned char)query(0,&available,&total,&total_free)) {
                Debug_Printf(disk_query_error_007d360c,GetLastError(),0);
            } else {
                unsigned int kilobytes=(unsigned int)(((double)available.HighPart*disk_high_word_scale_0079de10+(LONG)available.LowPart)*disk_bytes_to_kb_0079de08);
                Debug_Printf(disk_free_log_007d35f0,kilobytes>>10);
                return kilobytes;
            }
        } else Debug_Printf(disk_proc_error_007d35c0,GetLastError(),0);
    } else Debug_Printf(disk_module_error_007d3590);
    DWORD sectors;
    DWORD bytes;
    DWORD free_clusters;
    DWORD total_clusters;
    if (GetDiskFreeSpaceA(0,&sectors,&bytes,&free_clusters,&total_clusters)) {
        unsigned int kilobytes=((sectors*bytes)>>10)*free_clusters;
        Debug_Printf(disk_free_log_007d35f0,kilobytes>>10);
        return kilobytes;
    }
    return 0;
}
