#include <System.hpp>
#include <Windows.h>
#include <string>
#include <cstring>
#include <Debugger.hpp>

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

	std::string GetFileExtension( char *p_pBuffer )
	{
		// Hacky way of doing it?

		BD_MEMSIZE BufferSize = strlen(p_pBuffer);
		std::string Extension = "";

		for(BD_MEMSIZE i = BufferSize - 1; i >= 0; i--)
		{
			if(p_pBuffer[i] == '.')
			{
				// We found a file extension, now let's add every character in the extension
				// to the Extension string, (as large characters)
				BD_UINT32 ExtensionPosition = i + 1;
				
				// Let's loop through the extension's characters.
				for(BD_MEMSIZE j = ExtensionPosition; j < BufferSize; j++)
				{
					Extension += toupper(p_pBuffer[j]);
				}

				break;

			}
		}

		return Extension;
	}
}
