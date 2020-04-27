#include <stdio.h>
#include <string.h>

#include "uuid.h"
#include "cuuid.h"

std::string GetUUID()
{
	uuid_t uuid;
	uuid_generate( uuid );
	char out[40]={0};
	int i = 0;
	sprintf( out,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++],
		uuid[i++]
		);
	
	return out;
}

	