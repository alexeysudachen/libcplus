
#include <c+/bigint.hc>
#include <c+/xdef.hc>
#include <c+/xjson.hc>
#include <c+/program.hc>

enum { MAX_ITER_COUNT = 1 };

int main(int argc, char **argv)
  {
    int steps, max_bits, bits, i;
    C_BIGINT *p;
    
    Prog_Init(argc,argv,"t",PROG_EXIT_ON_ERROR);
    
    max_bits = Str_To_Int(Prog_Argument_Dflt(0,"512"));
    steps = Str_To_Int(Prog_Argument_Dflt(1,"10"));
    
    printf("%d\n",First_Prime_Values_Count);
    
    bits = max_bits;
    //for ( bits = 64; bits <= max_bits; bits = bits*2 )
      {
        C_BIGINT *prime;
        C_BIGINT *tmp = Bigint_Alloca_Bits(max_bits);
        double cc0;
        clock_t c0 = clock(), c1, c2;
        __Auto_Release for ( i = 0; i < steps; ++i ) 
          {
            c1 = clock();
            prime = Bigint_Prime(bits,0,0,tmp);
            fprintf(stderr,"%d:%.3f ",
                  i,((double)(clock()-c1))/CLOCKS_PER_SEC);
            
          }
        cc0 = ((double)(clock()-c0))/CLOCKS_PER_SEC;
        fprintf(stderr,"\nprimes (%dbits): %.3f / %.3f sec\n",
                  bits,cc0,cc0/steps);
      }

    return 0;
  }
