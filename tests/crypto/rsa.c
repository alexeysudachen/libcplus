
#include <c+/bigint.hc>
#include <c+/program.hc>

int MAX_ITER_COUNT;

void test(int bits,C_BIGINT *data)
{
	C_BIGINT *data_e, *data_x;
	C_BIGINT *p, *e, *m;
	Bigint_Generate_Rsa_Key_Pair(&e,&p,&m,bits);
	data_e = Bigint_Expmod(data,p,m);
	data_x = Bigint_Expmod(data_e,e,m);
	if ( !Prog_Has_Opt("s") )
	{
		puts("--------------------------");
		printf("P:%s\n",Bigint_Encode_10(p));
		printf("E:%s\n",Bigint_Encode_10(e));
		printf("M:%s\n",Bigint_Encode_10(m));
		puts(Bigint_Encode_16(data_x));
	}
	REQUIRE( Bigint_Equal(data_x,data) );
}

void usage()
{
	puts("usage: rsa [-s] [-n N] <bits>");
	exit(-1);
}

int main(int argc, char **argv)
{
	clock_t cc, c0;
	double c_min, c_max, c_avg;
	int bits, i;
	C_BIGINT *data;

	Prog_Init(argc,argv,"help|?|h,s,n:",PROG_USAGE_ON_ANY,usage);
	bits = Str_To_Int(Prog_Argument_Dflt(0,"128"));
	data = Bigint_Expand(0,(bits+sizeof(uhalflong_t)*8-1)/(sizeof(uhalflong_t)*8));
	System_Random(data->value,data->digits*sizeof(uhalflong_t));
	Bigint_Rshift_1(data);
	//data = Bigint_Random(bits-1);
	if ( !Prog_Has_Opt("s") )
		puts(Bigint_Encode_16(data));

	MAX_ITER_COUNT = Prog_First_Opt_Int("n",5);

	cc = clock();
	test(bits,data);
	c_min = clock()-cc;
	c_max = c_min;
	printf("%.3f ",(double)c_min/CLOCKS_PER_SEC);

	for ( i = 1; i < MAX_ITER_COUNT; ++i ) __Auto_Release
	{
		clock_t c0 = clock(), c1;
		test(bits,data);
		c1 = clock()-c0;
		printf(" %.3f",(double)c1/CLOCKS_PER_SEC);
		if ( !Prog_Has_Opt("s") ) puts("");
		if ( c1 > c_max ) c_max = c1;
		if ( c1 < c_min ) c_min = c1;
	}

	c_avg = ((double)(clock()-cc)/MAX_ITER_COUNT)/CLOCKS_PER_SEC;

	printf("\n");

	c_min/=CLOCKS_PER_SEC;
	c_max/=CLOCKS_PER_SEC;

	printf("%.3f < %.3f > %.3f\n",c_min,c_avg,c_max);

	return 0;
}
