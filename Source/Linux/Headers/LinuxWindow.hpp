#ifndef __BRAINDEAD_WINDOW_LINUXWINDOW_HPP__
#define __BRAINDEAD_WINDOW_LINUXWINDOW_HPP__

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <Window.hpp>

namespace BD
{
	class LinuxWindow : public Window
	{
	public:
		LinuxWindow( );
		virtual ~LinuxWindow( );

		virtual BD_UINT32 Create( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen = BD_FALSE );

		virtual BD_INLINE BD_BOOL IsCreated( ) const { return m_Created; }

		virtual BD_UINT32 DoEvents( );

		virtual WINDATA Data( ) const;

	private:
		::Window	m_Window;
		Display		*m_pDisplay;
		XVisualInfo	*m_pXVI;
		GLXContext m_GLXContext;

		BD_BOOL m_Created;
		BD_BOOL m_Fullscreen;

		BD_UINT32	m_Width;
		BD_UINT32	m_Height;
	};
}

#endif

