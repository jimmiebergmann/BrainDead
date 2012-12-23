#ifndef __BRAINDEAD_SYSTEM_HPP__
#define __BRAINDEAD_SYSTEM_HPP__

#include <DataTypes.hpp>
#include <string>

namespace BD
{
	BD_UINT32 GetExecutablePath( char **p_ppBuffer, BD_MEMSIZE p_Size );
	std::string GetFileExtension( char *p_pBuffer );
}

#endif

