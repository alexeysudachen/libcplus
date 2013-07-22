
/*

Copyright © 2010-2012, Alexéy Sudachén, alexey@sudachen.name
DesaNova Ltda, http://desanova.com/libcplus, Viña del Mar, Chile.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

http://www.gnu.org/licenses/

*/

#include <c+/program.hc>
#include <c+/aes.hc>
#include <c+/sha2.hc>
#include <c+/sha1.hc>
#include <c+/file.hc>

int main(int argc, char **argv)
  {
    quad_t IV = 0x07A87394E8FB41AF;
    C_AES *ctxe;
    C_BUFFER *bf, *bbf, *bbbf;
    char *passwd, *S;
    byte_t sign[32] = {0};
    byte_t dgst[20] = {0};
    int i, flen;
    void *f;

    __Try_Exit(0)
      {
        
        Prog_Init(argc,argv,"d,s,i:",0);

        if (( Prog_Has_Opt("s") && Prog_Arguments_Count() == 2 ) 
              || Prog_Arguments_Count() == 3 )
          ;
        else
          {
            puts("usage: ./aesxex [-d] <passwd> <filename> <outfile>");
            puts("       ./aesxex -s <passwd> <filename>");
            puts("       ./aesxex -i <hexstring> <passwd> <filename> <outfile>");
            fflush(stdout);
            exit(-1);
          }

        passwd = Prog_Argument(0);
        Sha2_Digest(passwd,strlen(passwd),sign);

        if ( !Prog_Has_Opt("d") && !Prog_Has_Opt("s") )
          {
            f = Cfile_Open(Prog_Argument(1),"r");
            flen = Oj_Available(f);
            bf = Buffer_Init(4+4+20+flen);
            memcpy(bf->at,"AESX",4);
            Unsigned_To_Four(flen,bf->at+4);
            Oj_Read_Full(f,bf->at+28,flen);
            Oj_Close(f);

            Sha1_Digest(bf->at+28,flen,bf->at+8);
            
            if ( S = Prog_First_Opt("i",0) ) 
              {
                int l = strlen(S);
                if ( l != 40 ) __Raise(C_ERROR_ILLFORMED,"digest should be hex string with 40 chars length");
                Str_Hex_Decode_(S,&l,dgst);
                REQUIRE(l == 20);  
                if ( 0 == memcmp(dgst,bf->at+8,20) ) 
                  {
                    puts("file has the same dgst, skipped");
                    exit(2);
                  }
              }

            puts(Str_Hex_Encode(bf->at+8,20));

            ctxe = Aes_Init_Encipher(sign,256);
            Oj_Encrypt_Buffer_XEX_MDSH(ctxe,bf,IV);
            
            Oj_Write_Full(Cfile_Open(Prog_Argument(2),"w+"),bf->at,bf->count);
          }
        else if ( Prog_Has_Opt("s") )
          {
            bf = Buffer_Init(32);
            f = Cfile_Open(Prog_Argument(1),"r");
            Oj_Read_Full(f,bf->at,32);
            Oj_Close(f);
            
            ctxe = Aes_Init_Decipher(sign,256);
            Oj_Decrypt_Buffer_XEX_MDSH(ctxe,bf,IV);
            
            puts(Str_Hex_Encode(bf->at+8,20));
          }
        else
          {
            f = Cfile_Open(Prog_Argument(1),"r");
            bf = Oj_Read_All(f);
            Oj_Close(f);
            
            ctxe = Aes_Init_Decipher(sign,256);
            Oj_Decrypt_Buffer_XEX_MDSH(ctxe,bf,IV);
            
            flen = Four_To_Unsigned(bf->at+4);
            Oj_Write_Full(Cfile_Open(Prog_Argument(2),"w+"),bf->at+28,flen);
          }
      }
      
    return 0;
  }

