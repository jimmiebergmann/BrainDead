#ifndef __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__
#define __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__

#include <DataTypes.hpp>

#ifdef BUILD_DEBUG
#define bdTrace BD::Trace
#ifdef __GNUC__
// REMINDER!
// Need to add ARCH_<ARCH> PLATFORM_<OS>_<ARCH> in addition to PLATFORM_<OS>
// and PLATFORM_<OS>_<ARCH>_<BITSIZE>
// !REMINDER
#ifdef ARCH_X86
#define bdDebugBreak( ) { BD_ASM( "INT $3;\n" ); }
#endif // ARCH_X86
#endif // __GNUC__
#ifdef _MSC_VER
#ifdef ARCH_X86
#ifdef PLATFORM_WINDOWS
#ifdef BITSIZE_64
// x86_64 cannot have in-lined assembly with MSVC
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplua
void bdDebugBreak_x86_64( );
#define bdDebugBreak bdDebugBreak_x86_64
#ifdef __cplusplus
}
#endif // __cplusplus
#elif PLATFORM_WINDOWS_X86_32
#define bdDebugBreak( ) { BD_ASM { int 3 } }
#endif // BITSIZE_64
#endif // PLATFORM_WINDOWS
#endif // ARCH_X86
#endif // _MSC_VER

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
#endif // BUILD_DEBUG

namespace BD
{
	// Trace can go to a file or the standard output (for Windows, this will be
	// the debug output window)
	BD_UINT32 Trace( const char *p_pFileName, const char *p_pMessage, ... );
}

#endif // __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__
