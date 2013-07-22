
#include <c+/bigint.hc>
#include <c+/xdef.hc>
#include <c+/xjson.hc>
#include <c+/program.hc>

enum { MAX_ITER_COUNT = 1 };

int main(int argc, char **argv)
{
	int bits, i;
	C_BIGINT *p, *e, *m, *data_e, *data_x, *data;
	char *RSA_KEY_PRIVATE, *RSA_KEY_PUBLIC, *RSA_KEY_MODULE;
	int triv = 0x10001;

	Prog_Init(argc,argv,"?|h,C,X,J,t,q,T",PROG_EXIT_ON_ERROR);

	bits = Str_To_Int(Prog_Argument_Dflt(0,"512"));
	__Gogo
	{
		clock_t c0 = clock(), c1, c2;
		Bigint_Generate_Rsa_Key_Pair_(&e,&p,&m,bits,Prog_Has_Opt("q")?0:triv);
		if ( Prog_Has_Opt("t") )
			fprintf(stderr,"keygen (success): %.3f sec\n",
			((double)(clock()-c0))/CLOCKS_PER_SEC);
	}

	RSA_KEY_PRIVATE = Bigint_Encode_16(p);
	RSA_KEY_PUBLIC  = Bigint_Encode_16(e);
	RSA_KEY_MODULE  = Bigint_Encode_16(m);

	for ( i = 0; i < 10; ++i ) __Auto_Release
	{
		data = Bigint_Expand(0,(bits+sizeof(uhalflong_t)*8-1)/(sizeof(uhalflong_t)*8));
		Soft_Random(data->value,data->digits*sizeof(uhalflong_t));
		Bigint_Rshift_1(data);
		//puts(Bigint_Encode_16(data));
		data_e = Bigint_Expmod(data,Bigint_Decode_16(RSA_KEY_PRIVATE),Bigint_Decode_16(RSA_KEY_MODULE));
		data_x = Bigint_Expmod(data_e,Bigint_Decode_16(RSA_KEY_PUBLIC),Bigint_Decode_16(RSA_KEY_MODULE));
		REQUIRE( Bigint_Equal(data_x,data) );
	}

	if ( Prog_Has_Opt("C") )
	{ 
		printf("char *RSA_KEY_PRIVATE = \"%s\";\n",RSA_KEY_PRIVATE);
		printf("char *RSA_KEY_PUBLIC  = \"%s\";\n",RSA_KEY_PUBLIC);
		printf("char *RSA_KEY_MODULE  = \"%s\";\n",RSA_KEY_MODULE);
	}
	else if ( Prog_Has_Opt("T") )
	{
		printf("PRIVATE_KEY = \"hex:%d:%s:%s\";\n",bits,RSA_KEY_PRIVATE,RSA_KEY_MODULE);
		printf("PUBLIC_KEY  = \"hex:%d:%s:%s\";\n",bits,RSA_KEY_PUBLIC,RSA_KEY_MODULE);
	}
	else if ( Prog_Has_Opt("X") || Prog_Has_Opt("J") )
	{
		C_XNODE *n = Xdata_Init();
		Xnode_Value_Set_Str(n,"PRIVATE",RSA_KEY_PRIVATE);
		Xnode_Value_Set_Str(n,"PUBLIC", RSA_KEY_PUBLIC);
		Xnode_Value_Set_Str(n,"MODULE", RSA_KEY_MODULE);
		Xnode_Value_Set_Int(n,"BITLEN", bits);

		if ( Prog_Has_Opt("J") )
			puts( Json_Format(n,0) );
		else
			puts( Def_Format(n,0) );
	}
	else /*binary*/
	{
	}

	return 0;
}
