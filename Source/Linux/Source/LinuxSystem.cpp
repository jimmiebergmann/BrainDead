#include <System.hpp>
#include <Debugger.hpp>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <string>

namespace BD
{
	// Credit to:
	// http://www.flipcode.com/archives/Path_To_Executable_On_Linux.shtml
	// For the following function contents
	BD_UINT32 GetExecutablePath( char *p_pBuffer, size_t p_Size )
	{
		// /proc/[pid]/exe
		char LinkName[ 64 ];
		pid_t PID;
		int Ret;
	
		// Get our PID and build the name of the link in /proc
		PID = getpid( );
	
		if( snprintf( LinkName, sizeof( LinkName ), "/proc/%i/exe", PID ) < 0 )
		{
			return BD_ERROR;
		}

		// Now read the symbolic link
		char FullPath[ p_Size ];
		Ret = readlink( LinkName, FullPath, p_Size );
	
		// In case of an error, leave the handling up to the caller
		if( Ret == -1 )
		{
			return BD_ERROR;
		}
	
		// Report insufficient buffer size
		if( Ret >= p_Size )
		{
			errno = ERANGE;
			return BD_ERROR;
		}

		// Ensure proper NULL termination
		FullPath[ Ret ] = 0;

		// Find the last '/' and cull
		std::string ExePath( FullPath );
		BD_MEMSIZE SlashLoc = ExePath.find_last_of( "/" );
		ExePath.resize( SlashLoc );
		ExePath.append( "/\0" );

		// Copy it, and we're done
		strncpy( p_pBuffer, ExePath.c_str( ), ExePath.size( ) );

		return BD_OK;
	}
}

