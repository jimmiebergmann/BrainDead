#ifndef __BRAINDEAD_WINDOW_WINDOW_HPP__
#define __BRAINDEAD_WINDOW_WINDOW_HPP__

#include <DataTypes.hpp>
#include <Windows.h>

namespace BD
{
	class Window
	{
	public:
		virtual ~Window( ){ }

		virtual BD_UINT32 Initialise( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen ) = 0;
	};
}

#endif

