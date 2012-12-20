#ifndef __BRAINDEAD_WINDOW_LINUXWINDOW_HPP__
#define __BRAINDEAD_WINDOW_LINUXWINDOW_HPP__

#include <Window/Window.hpp>
#include <X11/Xlib.h>

namespace BD
{
	class LinuxWindow : public Window
	{
	public:
		LinuxWindow( );
		virtual ~LinuxWindow( );

		virtual BD_UINT32 Initialise( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen = BD_FALSE );

	private:
		::Window	m_Window;
		Display		*m_pDisplay;

		BD_BOOL m_Fullscreen;

		BD_UINT32	m_Width;
		BD_UINT32	m_Height;
	};
}

#endif

