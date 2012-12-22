#include <Debugger.hpp>
#include <cstdarg>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <System.hpp>

namespace BD
{
	static BD_BOOL g_sLogFileOpen = BD_FALSE;

	BD_UINT32 Trace( const char *p_pFileName, const char *p_pMessage, ... )
	{
		char CompleteMessage[ 1024 ];
		BD_UINT32 ReturnVal;

		va_list ArgPtr;

		va_start( ArgPtr, p_pMessage );
		ReturnVal = vsnprintf( CompleteMessage, 1024, p_pMessage, ArgPtr );
		va_end( ArgPtr );

		if( p_pFileName != BD_NULL )
		{
			FILE *pFileHandle = BD_NULL;
			// Save files as executable path-relative
			char *pExeDir = new char[ 256 ];
			BD::GetExecutablePath( &pExeDir, 256 );

			std::string FilePath( pExeDir );
			FilePath.append( p_pFileName );

			if( g_sLogFileOpen )
			{
				pFileHandle = fopen( FilePath.c_str( ), "a+" );
			}
			else
			{
				g_sLogFileOpen = BD_TRUE;
				pFileHandle = fopen( FilePath.c_str( ), "w+" );
			}

			delete [ ] pExeDir;

			if( pFileHandle == BD_NULL )
			{
				return BD_ERROR;
			}

			fprintf( pFileHandle, "%s", CompleteMessage );

			fclose( pFileHandle );
			pFileHandle = BD_NULL;
		}
		else
		{
			printf( "%s", CompleteMessage );
		}

		return ReturnVal;
	}
}

