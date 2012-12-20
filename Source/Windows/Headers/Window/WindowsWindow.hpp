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

		virtual BD_UINT32 Create( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen = BD_FALSE );

		virtual BD_INLINE BD_BOOL Created( ) const { return m_Created; }

		virtual WINDATA Data( ) const;

	private:
		HDC		m_DeviceContext;
		HWND	m_Window;

		RECT	m_WindowRect;

		BD_BOOL m_Fullscreen;
		BD_BOOL m_Created;

		wchar_t	*m_pWindowTitle;

		static LRESULT WindowProc( HWND p_HWND, UINT p_Message,
			WPARAM p_WParam, LPARAM p_LParam );
	};
}

#endif
