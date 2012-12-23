#include <System.hpp>
#include <Debugger.hpp>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <string>

namespace BD
{
	BD_UINT32 GetFileExtension( const char *p_pFilePath, char **p_ppExt,
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
		if( p_Size < ExtLen )
		{
			return BD_ERROR;
		}

		// Extract the extension and null-terminate
		char Ext[ ExtLen+1 ];
		strncpy( Ext, p_pFilePath + ExtPos+1, PathLen-ExtPos );
		Ext[ ExtLen ] = '\0';

		for( BD_MEMSIZE i = 0; i < strlen( Ext ); ++i )
		{
			Ext[ i ] = toupper( Ext[ i ] );
		}

		strcpy( *p_ppExt, Ext );

		return BD_OK;
	}	
}

