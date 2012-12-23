#ifndef __BRAINDEAD_SYSTEM_HPP__
#define __BRAINDEAD_SYSTEM_HPP__

#include <DataTypes.hpp>
#include <string>

namespace BD
{
	BD_UINT32 GetExecutablePath( char **p_ppBuffer, BD_MEMSIZE p_Size );
	BD_UINT32 GetFileExtension( const char *p_pFilePath, char **p_ppExt,
		const BD_MEMSIZE p_Size );
}

#endif

