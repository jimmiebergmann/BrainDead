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

		BD_MEMSIZE ExtLen = PathLen-ExtPos-1;

		// The allocated buffer isn't large enough for the extension
		if( p_Size < ExtLen + 1 ) // + 1 since we need space for the last 0
		{
			return BD_ERROR;
		}
	
		// Create an array holding the extension data
		char * Ext = new char[ p_Size ];
		strncpy( Ext, p_pFilePath + ExtPos+1, ExtLen );
		Ext[ ExtLen ] = '\0';

		// Now, set the user's variable p_pExt.
		for( BD_MEMSIZE i = 0; i < p_Size; ++i )
		{
			p_pExt[ i ] = toupper( Ext[ i ] );
		}

		// Cleaning up Ext
		delete [ ] Ext;

		return BD_OK;
	}	
}

