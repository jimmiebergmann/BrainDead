#include <LinuxWindow.hpp>
#include <OGL/OpenGL.hpp>
#include <Debugger.hpp>
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
		if( m_pXVI )
		{
			XFree( m_pXVI );
		}

		if( m_GLXContext )
		{
			glFlush( );
			glXMakeCurrent( m_pDisplay, None, BD_NULL );
			glXDestroyContext( m_pDisplay, m_GLXContext );
		}

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

		BD_SINT32 GLXAttribs[ ] =
		{
			GLX_X_RENDERABLE,	True,
			GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
			GLX_RENDER_TYPE,	GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
			GLX_RED_SIZE,		8,
			GLX_GREEN_SIZE,		8,
			GLX_BLUE_SIZE,		8,
			GLX_ALPHA_SIZE,		8,
			GLX_DEPTH_SIZE,		24,
			GLX_STENCIL_SIZE,	8,
			GLX_DOUBLEBUFFER,	True,
			None
		};

		// For now, we will only care about GLX 1.3
		BD_SINT32 Major = 0, Minor = 0;

		if( !glXQueryVersion( m_pDisplay, &Major, &Minor ) ||
			( ( Major == 1 ) && ( Minor < 3 ) ) || ( Major < 1 ) )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <ERROR> "
				"GLX Version not 1.3 or greater\n" );
			return BD_ERROR;
		}

		BD_SINT32 FBCount = 0;
		GLXFBConfig *pFBC = glXChooseFBConfig( m_pDisplay,
			DefaultScreen( m_pDisplay ), GLXAttribs, &FBCount );

		if( !pFBC )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <ERROR> "
				"Failed to create a GLXFBConfig\n" );
			return BD_ERROR;
		}

		GLXFBConfig FBC = pFBC[ 0 ];

		XFree( pFBC );

		m_pXVI = glXGetVisualFromFBConfig( m_pDisplay, FBC );


		XSetWindowAttributes WinAttribs;
		Colormap ColourMap = XCreateColormap( m_pDisplay,
			RootWindow( m_pDisplay, m_pXVI->screen ), m_pXVI->visual,
			AllocNone );

		WinAttribs.colormap = ColourMap;
		WinAttribs.background_pixmap = None;
		WinAttribs.border_pixel = 0;
		WinAttribs.event_mask = StructureNotifyMask | ExposureMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
/*
		Screen *pScreen = DefaultScreenOfDisplay( m_pDisplay );

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
*/
		m_Window = XCreateWindow( m_pDisplay,
			RootWindow( m_pDisplay, m_pXVI->screen ),
			0, 0, 800, 600, 0, m_pXVI->depth, InputOutput,
			m_pXVI->visual, CWEventMask | CWColormap | CWBorderPixel,
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

		m_GLXContext = glXCreateNewContext( m_pDisplay, FBC, GLX_RGBA_TYPE,
			0, True );
		glXMakeCurrent( m_pDisplay, m_Window, m_GLXContext );

		XSync( m_pDisplay, False );

		bglViewport( 0, 0, m_Width, m_Height );

		m_Created = BD_TRUE;

		return BD_OK;
	}

	BD_UINT32 LinuxWindow::DoEvents( )
	{
		XEvent Event;
		KeySym Key;

		while( XPending( m_pDisplay ) > 0 )
		{
			XNextEvent( m_pDisplay, &Event );

			switch( Event.type )
			{
				case KeyPress:
				{
					Key = XLookupKeysym( &Event.xkey, 0 );
					if( Key == 'q' )
					{
						return BD_ERROR;
					}
					break;
				}
				case ConfigureNotify:
				{
					bglViewport( 0, 0, 800, 600 );
					break;
				}
			}
		}
		
		return BD_OK;
	}

	WINDATA LinuxWindow::Data( ) const
	{
		WINDATA Data;
		memset( &Data, 0, sizeof( WINDATA ) );

		return Data;
	}
}

