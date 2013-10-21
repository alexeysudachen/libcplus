#include "../../c+/C+.hc"
#include "../../c+/program.hc"

int main(int argc, char **argv)
  {
    Prog_Init(argc,argv,0,0);
    __Auto
      {
        puts(__Sformat("%?, %x at %?",$4(0x70000000L),$8(0x70000000L),$S("hello world!")));    
        puts(__Sformat3("%?, %x at %?",$4(0x70000000L),$8(0x70000000L),$S("hello world!")));    
        puts(__Sformat2("%10x at %?",$8(0x70000000L),$S("hello world!")));    
        puts(__Sformat1("%?",$U(L"hello world!")));    
        puts(__Sformat("%?, %010x at %?",$4(0x70000000L)));    
      }
  }


#if 0

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

typedef struct C_FORMAT_VALUE {
    uint64_t value;
    int kind;
} C_FORMAT_VALUE;

#ifdef __GNUC__
#define __Inline static
#define __No_Inline __attribute__((noinline))
#else
#define __Inline static __forceinline
#define __No_Inline __declspec(noinline)
#endif

__Inline C_FORMAT_VALUE format_value_i(int32_t a)        { C_FORMAT_VALUE r = {(uint64_t)a,  4}; return r; }
__Inline C_FORMAT_VALUE format_value_q(int64_t a)        { C_FORMAT_VALUE r = {(uint64_t)a,  8}; return r; }
__Inline C_FORMAT_VALUE format_value_S(char *const a)    { C_FORMAT_VALUE r = {(uintptr_t)a, 5}; return r; }
__Inline C_FORMAT_VALUE format_value_L(wchar_t *const a) { C_FORMAT_VALUE r = {(uintptr_t)a, 7}; return r; }

#define $4(a) format_value_i(a)
#define $8(a) format_value_q(a)
#define $S(a) format_value_S(a)
#define $L(a) format_value_L(a)

__No_Inline void C_Safe_Format(char const *fmt,C_FORMAT_VALUE *k)
{
  int j=0;
  while ( *fmt ) 
    {
      if ( *fmt == '%' && fmt[1] == '?' )
        {
          if ( k[j].kind )
            {
              switch(k[j].kind) 
              {
              case 4: 
                  printf("%08x",(uint32_t)k[j].value);
                  break;
              case 8: 
                  printf("%08x'%08x",(uint32_t)(k[j].value>>32),(uint32_t)k[j].value);
                  break;
              case 5: 
                  printf("%s",(char*)(uintptr_t)k[j].value);
                  break;
              case 7: 
                  printf("%S",(wchar_t*)(uintptr_t)k[j].value);
                  break;
              }
              ++j;
            }
          fmt+=2;
        }
      else
        putchar(*fmt++);
    }
}

#define C_ARGS_COUNT_(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,...) a15
#define C_ARGS_COUNT(...) C_EVAL(C_ARGS_COUNT_(__VA_ARGS__,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))

#define SFORMAT_K1(fv,N,a)     fv[N] = a;
#define SFORMAT_K2(fv,N,a,b)   fv[N] = a; SFORMAT_K1(fv,N+1,b)
#define SFORMAT_K3(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K2(fv,N+1,__VA_ARGS__))
#define SFORMAT_K4(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K3(fv,N+1,__VA_ARGS__))
#define SFORMAT_K5(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K4(fv,N+1,__VA_ARGS__))
#define SFORMAT_K6(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K5(fv,N+1,__VA_ARGS__))
#define SFORMAT_K7(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K6(fv,N+1,__VA_ARGS__))
#define SFORMAT_K8(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K7(fv,N+1,__VA_ARGS__))
#define SFORMAT_K9(fv,N,a,...) fv[N] = a; C_EVAL(SFORMAT_K8(fv,N+1,__VA_ARGS__))

#define SFORMAT_NU(fv,N,...) C_EVAL(C_CONCAT2(SFORMAT_K,C_ARGS_COUNT(__VA_ARGS__))(fv,N,__VA_ARGS__))

#define __Sformat(Fmt,...) \
    do { \
        C_FORMAT_VALUE fv[C_ARGS_COUNT(__VA_ARGS__)+1]; \
        SFORMAT_NU(fv,0,__VA_ARGS__); \
        C_Safe_Format(Fmt,fv); \
    } while (0)

int main()
{
  __Sformat("%? at %?",$4(0x70000000L),$S("hello world!"));
  __Sformat("%? at %?",1,"hello world!");
}


#endif
