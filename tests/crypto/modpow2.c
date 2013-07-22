
#include <c+/bigint.hc>
#include <c+/xdef.hc>
#include <c+/xjson.hc>
#include <c+/program.hc>

enum { MAX_ITER_COUNT = 1 };

int main(int argc, char **argv)
  {
    C_BIGINT *p0, *p1, *p2, *mod;
    C_BIGINT *R1, *R2;
    int i,N;
    
    Prog_Init(argc,argv,"t",PROG_EXIT_ON_ERROR);
    
    /*for ( N = 0; N < 10; ++N )
      {
        mod = Bigint_Init(101);
        p0 = Bigint_Init(Get_Random(1,65000));
        p1 = Bigint_Copy(p0);
        p2 = Bigint_Copy(p0);
        R1 = Bigint_Modpow2(p1,mod);
        R2 = Bigint_Modmul(p2,p2,mod);
        printf("%s^2%%%s=%s\n",Bigint_Encode_10(p0),Bigint_Encode_10(mod),Bigint_Encode_10(R1));
        printf("%s^2%%%s=%s\n",Bigint_Encode_10(p0),Bigint_Encode_10(mod),Bigint_Encode_10(R2));
        if ( !Bigint_Equal(R1,R2) ) 
          {
            puts("failed\n");
            exit(-1);
          }
      }*/
    
    for ( N = 0; N < 10; ++N )
      {        
        mod = Bigint_Prime(256,0,0,0);
        
        for (i = 0; i < 100; ++i) __Auto_Release
          {
            p0 = Bigint_Random_Bits(0,256);
            p1 = Bigint_Copy(p0);
            p2 = Bigint_Copy(p0);
            R1 = Bigint_Modpow2(p1,mod);
            R2 = Bigint_Modmul(p2,p2,mod);
            printf("%s^2%%%s=%s\n",Bigint_Encode_10(p0),Bigint_Encode_10(mod),Bigint_Encode_10(R1));
            printf("%s^2%%%s=%s\n",Bigint_Encode_10(p0),Bigint_Encode_10(mod),Bigint_Encode_10(R2));
            if ( !Bigint_Equal(R1,R2) ) 
              {
                puts("failed\n");
                exit(-1);
              }
          }
      }
    return 0;
  }
