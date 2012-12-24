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

namespace BD
{
	BD_UINT32 GetExecutablePath( char **p_ppBuffer, BD_MEMSIZE p_Size );
	std::string GetFileExtension( char *p_pBuffer );
}

#endif

