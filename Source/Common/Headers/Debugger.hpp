#ifndef __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__
#define __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__

#include <DataTypes.hpp>

#if BUILD_DEBUG
#define bdTrace BD::Trace
#ifdef PLATFORM_WINDOWS_X86_64
// x86_64 cannot have in-lined assembly
#ifdef __cplusplus
extern "C"
{
#endif
void bdDebugBreak_x86_64( );
#define bdDebugBreak bdDebugBreak_x86_64
#ifdef __cplusplus
}
#endif
#elif PLATFORM_WINDOWS_X86_32
#define bdDebugBreak( ) { BD_ASM { int 3 } }
#elif PLATFORM_LINUX
#define bdDebugBreak( ) { BD_ASM( "INT $3;\n" ); }
#else
#error No platform specified as a pre-processor directive
#endif

#define bdAssertToFile( p_Expr, p_LogFile ) \
	if( p_Expr ) { } \
	else \
	{\
		bdTrace( p_LogFile, "ASSERTION FAILURE\n%s | FILE: %s | LINE: %d\n\n", \
			#p_Expr, __FILE__, __LINE__ );\
		bdDebugBreak( );\
	}
#define bdAssert( p_Expr ) bdAssertToFile( p_Expr, BD_NULL )
#else
#define bdTrace sizeof
#define bdDebugBreak( )
#define bdAssert( p_Expr )
#define bdAssertToFile( p_Expr, p_LogFile )
#endif

namespace BD
{
	// Trace can go to a file or the standard output (for Windows, this will be
	// the debug output window)
	BD_UINT32 Trace( const char *p_pFileName, const char *p_pMessage, ... );
}

#endif
