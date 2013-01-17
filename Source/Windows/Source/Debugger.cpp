#include <Debugger.hpp>
#include <System.hpp>
#include <windows.h>
#include <cstdio>
#include <string>

namespace BD
{
	static BD_BOOL g_sLogFileOpen = BD_FALSE;

	BD_UINT32 Trace( const char *p_pFileName, const char *p_pMessage, ... )
	{
		char CompleteMessage[ 1024 ];
		BD_UINT32 ReturnVal;
		va_list ArgPtr;

		va_start( ArgPtr, p_pMessage );
		ReturnVal = _vsnprintf( CompleteMessage, 1024, p_pMessage, ArgPtr );
		va_end( ArgPtr );

		if( p_pFileName != BD_NULL )
		{
			HANDLE FileHandle = INVALID_HANDLE_VALUE;

			char *pExeDir = new char[ MAX_PATH ];
			memset( pExeDir, '\0', MAX_PATH );
			BD::GetExecutablePath( pExeDir, MAX_PATH );

			std::string FilePath( pExeDir );

			delete [ ] pExeDir;
			pExeDir = BD_NULL;
			
			FilePath.append( p_pFileName );
			
			if( g_sLogFileOpen )
			{
				FileHandle = CreateFileA( FilePath.c_str( ), FILE_APPEND_DATA,
					FILE_SHARE_READ, BD_NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
					BD_NULL );
			}
			else
			{
				g_sLogFileOpen = BD_TRUE;

				FileHandle = CreateFileA( FilePath.c_str( ), GENERIC_WRITE,
					FILE_SHARE_READ, BD_NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
					BD_NULL );
			}

			DWORD BytesWritten;
			WriteFile( FileHandle, CompleteMessage, strlen( CompleteMessage ),
				&BytesWritten, BD_NULL );

			CloseHandle( FileHandle );
			FileHandle = INVALID_HANDLE_VALUE;
		}
		else
		{
			OutputDebugStringA( CompleteMessage );
		}

		return ReturnVal;
	}
}
