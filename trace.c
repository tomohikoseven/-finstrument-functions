#define _GNU_SOURCE
#include<dlfcn.h>
#include<stdio.h>
#include<string.h>
#define MAX_SIZE 256
const char* addr2name               (   void* address,
                                        char* funcname      );
void        __cyg_profile_func_enter(   void* func_address,
                                        void* call_site     );
void        __cyg_profile_func_exit (   void* func_address,
                                        void* call_site     );
void        common_func             (   void* func_address,
                                        const char *fmt     );

/* ### 関数の呼び出し直後に実行される ### */
void __cyg_profile_func_enter(   void* func_address,
                                 void* call_site     )
{
    common_func( func_address, "enter =>" );
}

/* ### 関数の return 直前に実行される ### */
void __cyg_profile_func_exit (  void* func_address,
                                void* call_site     )
{
    common_func( func_address, "<= exit" );
}

void common_func( void* func_address, const char *fmt )
{
    char        _funcname[MAX_SIZE];
    const char  *_ret = NULL;

    memset( _funcname, 0x00, sizeof( _funcname ) );

    _ret = addr2name( func_address, _funcname );
    if( NULL != _ret )
    {
        printf( "%s _funcname = %s.\n", fmt,  _funcname );
    }
}

/* ### 関数ポインタのアドレスを（人が読める）関数名へ変換する ### */
const char*
addr2name( void* address, char* funcname )
{
    Dl_info dli;
    memset( &dli, 0x00, sizeof( dli ) );

    /* ### この dladdr() で関数名へ変換している ### */
    if( 0 != dladdr( address, &dli ) )
    {
        strncpy( funcname, dli.dli_sname, MAX_SIZE );
        return dli.dli_sname;
    }
    return NULL;
}

