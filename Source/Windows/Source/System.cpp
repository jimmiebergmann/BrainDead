#include <System.hpp>
#include <Windows.h>
#include <string>
#include <cstring>

namespace BD
{
	BD_UINT32 GetExecutablePath( char **p_ppBuffer, BD_MEMSIZE p_Size )
	{
		HMODULE Module = GetModuleHandleA( BD_NULL );
		char *pFullPath = new char[ p_Size ];
		memset( pFullPath, '\0', p_Size );
		GetModuleFileNameA( Module, pFullPath, p_Size );

		std::string ExePath( pFullPath );

		delete [ ] pFullPath;
		pFullPath = BD_NULL;

		BD_MEMSIZE SlashLoc = ExePath.find_last_of( "\\" );
		ExePath.resize( SlashLoc+1 );
		
		strncpy( *p_ppBuffer, ExePath.c_str( ), ExePath.size( ) );

		return BD_OK;
	}
}
