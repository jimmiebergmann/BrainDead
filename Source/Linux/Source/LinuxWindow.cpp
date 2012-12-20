#include <LinuxWindow.hpp>
#include <cstring>
#include <cstdio>

namespace BD
{
	LinuxWindow::LinuxWindow( )
	{
		m_pDisplay = BD_NULL;
		m_Fullscreen = BD_FALSE;
		m_Created = BD_FALSE;
	}

	LinuxWindow::~LinuxWindow( )
	{
		if( m_pDisplay )
		{
			XDestroyWindow( m_pDisplay, m_Window );
			XCloseDisplay( m_pDisplay );
		}
	}

	BD_UINT32 LinuxWindow::Create( const BD_UINT32 p_Width,
		const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen )
	{
		m_pDisplay = XOpenDisplay( 0 );
		m_Fullscreen = p_Fullscreen;

		XSetWindowAttributes WinAttribs;

		WinAttribs.background_pixmap = None;
		WinAttribs.border_pixel = 0;
		WinAttribs.event_mask = StructureNotifyMask | ExposureMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

		Screen *pScreen = DefaultScreenOfDisplay( m_pDisplay );
		int ScreenVal = DefaultScreen( m_pDisplay );

		if( m_Fullscreen == BD_TRUE )
		{
			m_Width = WidthOfScreen( pScreen );
			m_Height = HeightOfScreen( pScreen );
		}
		else
		{
			m_Width = p_Width;
			m_Height = p_Height;
		}

		m_Window = XCreateWindow( m_pDisplay,
			RootWindow( m_pDisplay, ScreenVal ),
			0, 0, m_Width, m_Height, 0, CopyFromParent, InputOutput,
			CopyFromParent, CWEventMask | CWBorderPixel,
			&WinAttribs );

#ifdef BUILD_DEBUG
		printf( "m_Window: 0x%08X | Width: %d | Height %d | Fullscreen: %s\n",
			m_Window, m_Width, m_Height, ( m_Fullscreen ? "True" : "False" ) );
#endif

		XMapWindow( m_pDisplay, m_Window );
		XMapRaised( m_pDisplay, m_Window );

		XStoreName( m_pDisplay, m_Window, "BrainDead" );
		XMoveWindow( m_pDisplay, m_Window, 0, 0 );
		XRaiseWindow( m_pDisplay, m_Window );

		// Wait for the MapNotify event to 
		for( ; ; )
		{
	    	XEvent Event;
		    XNextEvent( m_pDisplay, &Event );
		    if( Event.type == MapNotify)
			{
				break;
			}
      	}

		m_Created = BD_TRUE;

		return BD_OK;
	}

	WINDATA LinuxWindow::Data( ) const
	{
		WINDATA Data;
		memset( &Data, 0, sizeof( WINDATA ) );

		return Data;
	}
}

