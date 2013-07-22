
#include "../../c+/program.hc"
#include "../../c+/tester.hc"
#include "../../c+/crypto/sha1.hc"

struct SHA1_VECTOR
{
	const char *input;
	int filler;
	int input_len;
	byte_t result[20];
} g_vec[] = {

	{ "abc", 0, 3, 
		{ 0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E,
		  0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D }},

	{ "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 0, 56,
		{ 0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E, 0xBA, 0xAE,
		  0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5, 0xE5, 0x46, 0x70, 0xF1 }},

	{ 0, 'a', 1000000,
		{ 0x34, 0xAA, 0x97, 0x3C, 0xD4, 0xC4, 0xDA, 0xA4, 0xF6, 0x1E,
		  0xEB, 0x2B, 0xDB, 0xAD, 0x27, 0x31, 0x65, 0x34, 0x01, 0x6F }},
};

void Test_N(int no)
{
	C_SHA1 ctx;
	byte_t digest[20];

	Do_Test_Case(__Format("SHA1-#%d VECTOR",no))
	{
		Sha1_Start(&ctx);
		if ( !g_vec[no].input )
		{
			int L = C_Minu(1000,g_vec[no].input_len);
			int i;
			byte_t *buf = malloc(L);
			memset(buf, g_vec[no].filler, L);
			for ( i = 0; i < g_vec[no].input_len; i+= L )
				Sha1_Update(&ctx,buf,C_Minu(g_vec[no].input_len-i,L));
			free(buf);
		}
		else
			Sha1_Update(&ctx,g_vec[no].input,g_vec[no].input_len);
		
		Sha1_Finish(&ctx,digest);

		Test_Mem_Equal( g_vec[no].result, digest, 20 );
	}
}

int main(int argc, char **argv)
  {
	int i;
    Prog_Init(argc,argv,0,0);
    
	Do_Test_Group("crypto/sha1.hc")
	{
		for ( i = 0; i < __Length_Of(g_vec); ++i )
			Test_N(i);      
	}

    return 0;
  }
