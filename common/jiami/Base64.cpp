/*
 * Base64.cpp
 *
 *  Created on: 2011-10-28
 *      Author: zq
 */

#include "Base64.h"
#include <string.h>

/*
** Translation Table as described in RFC1113
*/
static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
** Translation Table to decode (created by author)
*/
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

static const int linesize = (76*4);
/*
** encodeblock
**
** encode 3 8-bit binary bytes as 4 '6-bit' characters
*/
void encodeblock( unsigned char in[3], unsigned char out[4], int len )
{
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

/*
** decodeblock
**
** decode 4 '6-bit' characters into 3 8-bit binary bytes
*/
void decodeblock( unsigned char in[4], unsigned char out[3] )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

int Base64::Encode( const char* pIn, int inLen,  char* pOut, int outLen )
{
   unsigned char in[3], out[4];
   int i, len, blocksout = 0;
   int readBytes =  0;
   int writeBytes  = 0;
   while( readBytes < inLen ) {
        len = 0;
        for( i = 0; i < 3; i++ ) {
            in[i] = (unsigned char) pIn[readBytes++];
            if( readBytes <= inLen ) {
                len++;
            }
            else {
                in[i] = 0;
            }
        }
        if( len ) {
            encodeblock( in, out, len );
	     if ( writeBytes + 4 >= outLen )
		 	return 0;
		 
            for( i = 0; i < 4; i++ ) {
               pOut[writeBytes++]=  out[i];   
               blocksout++;
            }
         
        }
        if( blocksout >= (linesize/4)  ) {
		 if ( writeBytes + 2 >= outLen )
		 	return 0;
           	 pOut[writeBytes++]=  '\r';
		 pOut[writeBytes++]=  '\n';
               blocksout = 0;
        }
    }
   return writeBytes;
}
int  Base64::Decode( const char* pIn, int inLen,  char* pOut, int outLen )
{
    unsigned char in[4], out[3], v;
    int i, len;
    int readBytes =  0;
    int writeBytes  = 0;
   
    while( readBytes < inLen ) {
        for( len = 0, i = 0; i < 4  && readBytes < inLen; i++ ) {
            v = 0;
            while( readBytes < inLen && v == 0 ) {
                v = (unsigned char) pIn[ readBytes++ ];
                v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
                if( v ) {
                    v = (unsigned char) ((v == '$') ? 0 : v - 61);
                }
            }
            if( readBytes <= inLen && v) {
                len++;
                //if( v ) {
                    in[ i ] = (unsigned char) (v - 1);
                //}
            }
            else {
                in[i] = 0;
            }
        }
        if( len ) {
            decodeblock( in, out );
	     if ( writeBytes + len >= outLen )
		 	return 0;
            for( i = 0; i < len-1 ; i++ ) {
                pOut[writeBytes++] = out[i];
            }
        }
    }
	return writeBytes;
}

int Base64::DecodeEx( const char* pIn, int inLen,  char* pOut, int outLen , const char* pKey)
{
	int len = strlen( pKey );
	int r     = Decode( pIn, inLen, pOut, outLen );
	if ( r > 0  && len > 0 )
	{
		for( int i = 0; i < r; i ++ )
		{
			pOut[i] ^= pKey[i%len];
		}
	}
	return r;
}
