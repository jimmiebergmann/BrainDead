#ifndef __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__
#define __BRAINDEAD_DEBUGGER_DEBUGLOG_HPP__

#include <DataTypes.hpp>

#if BUILD_DEBUG
#define bdTrace BD::Trace
#else
#define bdTrace sizeof
#endif

namespace BD
{
	// Trace can go to a file or the standard output (for Windows, this will be
	// the debug output window)
	BD_UINT32 Trace( const char *p_pFileName, const char *p_pMessage, ... );
}

#endif
