#include <Debugger.hpp>
#include <cstdarg>
#include <cstdio>

namespace BD
{
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

			pFileHandle = fopen( p_pFileName, "w+" );

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

