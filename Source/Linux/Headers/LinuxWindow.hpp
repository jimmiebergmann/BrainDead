#ifndef __BRAINDEAD_WINDOW_LINUXWINDOW_HPP__
#define __BRAINDEAD_WINDOW_LINUXWINDOW_HPP__

#include <Window/Window.hpp>

namespace BD
{
	class LinuxWindow : public Window
	{
	public:
		LinuxWindow( );
		virtual ~LinuxWindow( );

		virtual BD_UINT32 Initialise( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height );
	};
}

#endif

