#include <Debugger/DebugLog.hpp>
#include <Windows.h>
#include <cstdio>

namespace BrainDead
{
	BD_UINT32 Trace( const char *p_pFileName, const char *p_pMessage, ... )
	{
		char CompleteMessage[ 1024 ];
		BD_UINT32 ReturnVal;

		va_list ArgPtr;

		va_start( ArgPtr, p_pMessage );
		ReturnVal = _vsnprintf( CompleteMessage, 1024, p_pMessage, ArgPtr );
		va_end( ArgPtr );

		OutputDebugStringA( CompleteMessage );

		return ReturnVal;
	}
}
