
#include "../../c+/program.hc"
#include "../../c+/tester.hc"
#include "../../c+/text/regex.hc"

void Test_1()
{
#define S_RE "aa (\\d+)4\\s*(\\S+)"
	Do_Test_Case(S_RE)
	{
		C_ARRAY *L = 0;
		L = Re_Match(S_RE, "aa 1234 xy\nz", 0);
		Test_True( L != 0 );
		Test_Iqual( L->count, 3 );
		Test_Squal( L->at[0], "aa 1234 xy" );
		Test_Squal( L->at[1], "123" );
		Test_Squal( L->at[2], "xy" );
	}

	Do_Test_Case(S_RE)
	{
		int len = -1;
		const char *text = "Sdf aa 1234 xy\nz";
		const char *S = Re_Search(S_RE, text, &len);
		Test_True( S != 0 );
		Test_Iqual( len, 10 );
	}
#undef S_RE
}

void Test_2()
{
#define S_RE "(\\d(\\d)?)"
	Do_Test_Case(S_RE)
	{
		C_ARRAY *L = 0;
		L = Re_Match(S_RE, "1", 0);
		Test_True( L != 0 );
		Test_Iqual( L->count, 3 );
		Test_Squal( L->at[0], "1" );
		Test_Squal( L->at[1], "1" );
		Test_Squal( L->at[2], "" );
	}
#undef S_RE
}

void Test_3()
{
	const char *text = " \tGET /index.html HTTP/1.0\r\n\r\n";
#define S_RE "^\\s*(GET|POST)\\s+(\\S+)\\s+HTTP/(\\d)\\.(\\d)"	
	Do_Test_Case(S_RE)
	{
		C_ARRAY *L = 0;
		L = Re_Match(S_RE, text, 0);
		Test_True( L != 0 );
		Test_Iqual( L->count, 5 );
		Test_Squal( L->at[0], " \tGET /index.html HTTP/1.0" );
		Test_Squal( L->at[1], "GET" );
		Test_Squal( L->at[2], "/index.html" );
		Test_Squal( L->at[3], "1" );
		Test_Squal( L->at[4], "0" );
	}
#undef S_RE
}

int main(int argc, char **argv)
{
	Prog_Init(argc,argv,0,0);

	Do_Test_Group("regex.hc")
	{
		Test_1();
		Test_2();
		Test_3();
	}
}
 
