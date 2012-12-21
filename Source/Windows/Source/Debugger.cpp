#include <Debugger/DebugLog.hpp>
#include <Windows.h>
#include <cstdio>

namespace BD
{
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

			FileHandle = CreateFileA( p_pFileName, GENERIC_WRITE, FILE_SHARE_READ,
				BD_NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, BD_NULL );

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
