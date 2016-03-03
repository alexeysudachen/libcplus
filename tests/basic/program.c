
#include "../../c+/buffer.hc"
#include "../../c+/program.hc"

int object_counter = 0;

typedef struct TESTOBJECT 
  {
    int q;
  } 
  TESTOBJECT;
  
void TESTOBJECT_Destruct(TESTOBJECT *self)
  {
    --object_counter;
    __Destruct(self);
  }

TESTOBJECT *Object()
  {
    TESTOBJECT *self = __Object_Dtor(sizeof(TESTOBJECT),TESTOBJECT_Destruct);
    ++object_counter;
    return self;
  }

void f_raise(int e) 
  {
    __Raise(e,0);
  }

void f_raise_nocatch(int e)
  {
    STRICT_REQUIRE( e != 0 );
    __Try_Ptr(0)
      {
        TESTOBJECT *o = Object();
        f_raise(e);
      }
    __Catch(3)
      {
        STRICT_UNREACHABLE;
      }
  }

void simple_try_except_1() 
  {
    STRICT_REQUIRE( object_counter == 0 );
    __Try_Ptr(0)
      {
        TESTOBJECT *o = Object();
        f_raise(1);
      }
    __Except
      {
        STRICT_REQUIRE( __Error_Code == 1 );
        STRICT_REQUIRE( object_counter == 0 );
      }
    STRICT_REQUIRE( object_counter == 0 );
  }

void simple_try_except_2() 
  {
    STRICT_REQUIRE( object_counter == 0 );
    __Try_Ptr(0)
      {
        TESTOBJECT *o = Object();
        f_raise_nocatch(1);
      }
    __Except
      {
        STRICT_REQUIRE( __Error_Code == 1 );
        STRICT_REQUIRE( object_counter == 0 );
      }
    STRICT_REQUIRE( object_counter == 0 );
  }

void simple_try_catch_1() 
  {
    STRICT_REQUIRE( object_counter == 0 );
    __Try_Ptr(0)
      {
        TESTOBJECT *o = Object();
        f_raise(1);
      }
    __Catch(1)
      {
        STRICT_REQUIRE( __Error_Code == 1 );
        STRICT_REQUIRE( object_counter == 0 );
      }
    STRICT_REQUIRE( object_counter == 0 );
  }

void simple_try_catch_2() 
  {
    STRICT_REQUIRE( object_counter == 0 );
    __Try_Ptr(0)
      {
        TESTOBJECT *o = Object();
        f_raise_nocatch(1);
      }
    __Catch(1)
      {
        STRICT_REQUIRE(__Error_Code == 1);
        STRICT_REQUIRE(object_counter == 0);
      }
    STRICT_REQUIRE( object_counter == 0 );
  }

int main(int argc, char **argv)
  {
    Prog_Init(argc,argv,0,0);
    simple_try_except_1();
    simple_try_except_2();
    simple_try_catch_1();
    simple_try_catch_2();
  }
  
  