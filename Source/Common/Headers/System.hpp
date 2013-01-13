#ifndef __BRAINDEAD_SYSTEM_HPP__
#define __BRAINDEAD_SYSTEM_HPP__

#include <DataTypes.hpp>
#include <string>

// Sleep
#ifdef PLATFORM_WINDOWS
#define bdSleep(x) ( Sleep( x ) )
#elif PLATFORM_LINUX
#define bdSleep(x) ( usleep( x * 1000 ) )
#endif

// Very useful macro for check single bits
#define bdBit(n)       (1 << (n))
#define bdCheckBit(n,i) ((bool)(((n) & bdBit(i)) != 0)) // <- Use this

namespace BD
{
	BD_UINT32 GetExecutablePath( char *p_pBuffer, BD_MEMSIZE p_Size );
	BD_UINT32 GetFileExtension( const char *p_pFilePath, char *p_pExt,
		const BD_MEMSIZE p_Size );
}

#endif

