#ifndef __BRAINDEAD_WINDOW_WINDOWSWINDOW_HPP__
#define __BRAINDEAD_WINDOW_WINDOWSWINDOW_HPP__

#include <Window/Window.hpp>

namespace BD
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow( );
		virtual ~WindowsWindow( );

		virtual BD_UINT32 Initialise( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen = BD_FALSE );

	private:
	};
}

#endif
