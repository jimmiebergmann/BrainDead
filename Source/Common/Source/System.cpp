#include <System.hpp>
#include <Debugger.hpp>

#ifdef PLATFORM_WINDOWS
#include <windows.h>

// ISSUE!
// Can npt find unistd.h on my windows machine.
// ISSUE!
#elif PLATFORM_LINUX
#include <unistd.h>
#endif

#include <errno.h>
#include <cstring>
#include <string>

namespace BD
{

	BD_UINT32 GetFileExtension( const char *p_pFilePath, char *p_pExt,
		const BD_MEMSIZE p_Size )
	{
		// Find the last '.'
		BD_MEMSIZE PathLen = strlen( p_pFilePath );
		BD_MEMSIZE ExtPos = 0;
		BD_BOOL ExtFound = BD_FALSE;

		for( BD_MEMSIZE i = PathLen-1; i >= 0; --i )
		{
			char c = p_pFilePath[ i ];
			if( c == '.' )
			{
				ExtPos = i;
				ExtFound = BD_TRUE;
				break;
			}
		}

		// Couldn't find it.  Bail!
		if( ExtFound == BD_FALSE )
		{
			return BD_ERROR;
		}

		const BD_MEMSIZE ExtLen = PathLen-ExtPos-1;

		// The allocated buffer isn't large enough for the extension
		if( p_Size < ExtLen )
		{
			return BD_ERROR;
		}

		// Extract the extension and null-terminate
		char *pExt = new char[ ExtLen+1 ];
		strncpy( pExt, p_pFilePath + ExtPos+1, PathLen-ExtPos );
		pExt[ ExtLen ] = '\0';

		for( BD_MEMSIZE i = 0; i < strlen( pExt ); ++i )
		{
			pExt[ i ] = toupper( pExt[ i ] );
		}

		strcpy( p_pExt, pExt );

		// Cleaning up Ext
		delete [ ] pExt;

		return BD_OK;
	}	
}

