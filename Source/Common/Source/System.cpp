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


	BD_UINT32 GetExecutablePath( char *p_pBuffer, BD_MEMSIZE p_Size )
	{
		
#ifdef PLATFORM_WINDOWS
		HMODULE Module = GetModuleHandleA( BD_NULL );
		char *pFullPath = new char[ p_Size ];
		memset( pFullPath, '\0', p_Size );
		GetModuleFileNameA( Module, pFullPath, p_Size );

		std::string ExePath( pFullPath );

		delete [ ] pFullPath;
		pFullPath = BD_NULL;

		BD_MEMSIZE SlashLoc = ExePath.find_last_of( "\\" );
		ExePath.resize( SlashLoc+1 );

		strncpy( p_pBuffer, ExePath.c_str( ), ExePath.size( ) );

// ISSUE!
// Need linux code for this.
// ISSUE!
#else	

		if( p_pBuffer != BD_NULL && p_Size > 0)
		{
			p_pBuffer[0] = 0;
		}
#endif
		return BD_OK;
	}


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
		// Make sure the extension length isn't longer than p_Size
		if( ExtLen > p_Size )
		{
			ExtLen = p_Size;
		}

		// The allocated buffer isn't large enough for the extension
		if( p_Size < ExtLen )
		{
			return BD_ERROR;
		}

		
/*
		// Extract the extension and null-terminate
		char * Ext = new char[ ExtLen+1 ];
		strncpy( Ext, p_pFilePath + ExtPos+1, PathLen-ExtPos );
		Ext[ ExtLen+1 ] = '\0';

		for( BD_MEMSIZE i = 0; i < strlen( Ext ); ++i )
		{
			Ext[ i ] = toupper( Ext[ i ] );
		}

		strcpy( p_pExt, Ext );

		// Cleaning up Ext
		delete [] Ext;
*/

		char * Ext = new char[ ExtLen+1 ];
		strncpy( Ext, p_pFilePath + ExtPos, PathLen-ExtPos );
		Ext[ ExtLen+1] = '\0';

		memset(p_pExt, 0, p_Size);
		for( BD_MEMSIZE i = 0; i < ExtLen; ++i )
		{
			p_pExt[ i ] = toupper( Ext[ i ] );
		}


		// Cleaning up Ext
		delete [] Ext;




		return BD_OK;
	}	
}

