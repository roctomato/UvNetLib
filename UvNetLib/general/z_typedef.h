#pragma once

#include <string>
#include <cstdint>


	typedef char LsInt8;
	typedef short LsInt16;
	typedef int LsInt32;
	typedef std::int64_t  LsInt64;

	typedef unsigned char LsUInt8;
	typedef unsigned short LsUInt16;
	typedef unsigned int LsUInt32;
	typedef std::uint64_t  LsUInt64;


	class BigString: public std::string
	{
		using std::string::string;
	};

	#define MAKE_WORD(a, b)      ((LsUInt16)(((LsUInt8)((LsUInt32)(a) & 0xff)) | ((LsUInt16)((LsUInt8)((LsUInt32)(b) & 0xff))) << 8))
	#define LO_BYTE(w)           ((LsUInt8)((LsUInt32)(w) & 0xff))
	#define HI_BYTE(w)           ((LsUInt8)((LsUInt32)(w) >> 8))

	#define MAKE_UINT32(a, b)      ((LsUInt32)(((LsUInt16)(((LsUInt32)(a)) & 0xffff)) | ((LsUInt32)((LsUInt16)(((LsUInt32)(b)) & 0xffff))) << 16))
	#define LO_WORD(l)           ((LsUInt16)(((LsUInt32)(l)) & 0xffff))
	#define HI_WORD(l)           ((LsUInt16)((((LsUInt32)(l)) >> 16) & 0xffff))

	#define ARRAY_SIZE(a ) (sizeof(a)/sizeof(a[0]))

