/*
 * Base64.h
 *
 *  Created on: 2011-10-28
 *      Author: zq
 */

#ifndef BASE64_H_
#define BASE64_H_

class Base64 {
public:
	static int Encode( const char* pIn, int inLen,  char* pOut, int outLen );
	static int Decode( const char* pIn, int inLen,  char* pOut, int outLen );
       static int DecodeEx( const char* pIn, int inLen,  char* pOut, int outLen, const char* pKey );
};

#endif /* BASE64_H_ */
