#include "sys_tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include  <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "zby_debug.h"

int daemonize( const char* path_name)
{
#ifndef __WIN32__
	pid_t pid = fork ();

	if ( pid  < 0 )
		return -1;

	else if (pid != 0)
		exit (0); // Parent exits.

    // 1st child continues.
	setsid (); // Become session leader.

	signal (SIGHUP, SIG_IGN);

	pid = fork ();

	if (pid != 0)
		exit (0); // First child terminates.

	if (path_name != NULL)
		// change working directory.
		chdir (path_name);

	umask (0); // clear our file mode creation mask.
	close( STDIN_FILENO);
	close( STDOUT_FILENO);
	close( STDERR_FILENO);

    int fd = open ("/dev/null", O_RDWR, 0);
	if (fd != -1)
	{
	  dup2 (fd, STDIN_FILENO);
	  dup2 (fd, STDOUT_FILENO);
	  dup2 (fd, STDERR_FILENO);
	}
#endif
	return 0;
}

unsigned  int GenMark( unsigned char * data, int len)
{
	if ( NULL == data || len == 0 )
		return 0;
		
	unsigned  int ret = 0;
	if ( len < 4 )
	{
		for( int i =0; i < len; i ++ )
		{
			ret += data[i];
		}
	}
	else
	{
		for( int i = len-4; i < len; i ++ )
		{
			ret += data[i];
			//LS_PRINT( "%d) %d", i,data[i]);
		}
	}
	return ret;
}

////////////////////////////////////////////////////
LsUInt16  CheckValid::s_nextFlag = 0;
CheckValid::CheckValid()
{
	if ( s_nextFlag == 0 ){
		s_nextFlag ++;
	}
	_initMark = _lastMark = s_nextFlag ++;
}

bool CheckValid::IsValid()
{
	return _initMark == _lastMark;
}

CheckValid::~CheckValid()
{
	_lastMark = 0;
}

void CheckValid::Dump()
{
	SYS_INFO("%x %x", _initMark, _lastMark);
}
