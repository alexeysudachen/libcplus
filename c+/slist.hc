
/*

Copyright © 2010-2012, Alexéy Sudachén, alexey@sudachen.name, Chile

In USA, UK, Japan and other countries allowing software patents:

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    http://www.gnu.org/licenses/

Otherwise:

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Except as contained in this notice, the name of a copyright holder shall not
be used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization of the copyright holder.

*/

#ifndef C_once_8D00296D_5AEA_48BA_BCAA_AAA1C0CB05A4
#define C_once_8D00296D_5AEA_48BA_BCAA_AAA1C0CB05A4

#include "C+.hc"

#ifdef _BUILTIN
#define _C_SLIST_BUILTIN
#endif

#define Slist_Remove_By(ListPtr,Next,Val) C_Slist_Remove((void**)ListPtr,(int)((size_t)(&(*ListPtr)->Next)-(size_t)(*ListPtr)),Val)
#define Slist_Remove(ListPtr,Val) Slist_Remove_By(ListPtr,next,Val)

void C_Slist_Remove(void **p, int offs_of_next, void *val)
#ifdef _C_SLIST_BUILTIN
  {
    if ( p ) 
      {
        while ( *p )
          {
            if ( *p == val )
              {
                void *r = *p;
                *p = *(void**)((byte_t*)r + offs_of_next);
                *(void**)((byte_t*)r + offs_of_next) = 0;
                break;
              }
            else
              p =  (void**)((byte_t*)*p + offs_of_next);
          }
      }
  }
#endif
  ;

#define Slist_Push_By(ListPtr,Next,Val) C_Slist_Push((void**)ListPtr,(int)((size_t)(&(*ListPtr)->Next)-(size_t)(*ListPtr)),Val)
#define Slist_Push(ListPtr,Val) Slist_Push_By(ListPtr,next,Val)

void C_Slist_Push(void **p, int offs_of_next, void *val)
#ifdef _C_SLIST_BUILTIN
  {
    if ( p ) 
      {
        while ( *p )
          {
            p =  (void**)((byte_t*)*p + offs_of_next);
          }
        *p = val;
        *(void**)((byte_t*)*p + offs_of_next) = 0;
      }
  }
#endif
  ;
  
#define Slist_Pop_By(ListPtr,Next) C_Slist_Pop((void**)ListPtr,(int)((size_t)(&(*ListPtr)->Next)-(size_t)(*ListPtr)))
#define Slist_Pop(ListPtr) Slist_Pop_By(ListPtr,next)

void *C_Slist_Pop(void **p, int offs_of_next)
#ifdef _C_SLIST_BUILTIN
  {
    void *r = 0;
    
    if ( p )
      {
        r = *p;
        if ( r ) 
          {
            *p = *(void**)((byte_t*)r + offs_of_next);
            *(void**)((byte_t*)r + offs_of_next) = 0;
          }
      }
      
    return r;
  }
#endif
  ;

#endif /* C_once_8D00296D_5AEA_48BA_BCAA_AAA1C0CB05A4 */

