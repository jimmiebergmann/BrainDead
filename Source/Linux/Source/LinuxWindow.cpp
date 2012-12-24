#include <LinuxWindow.hpp>
#include <OGL/OpenGL.hpp>
#include <Debugger.hpp>
#include <cstring>
#include <cstdio>

namespace BD
{
	static BD_BOOL g_sContextError = BD_FALSE;
	static int ContextErrorHandler( Display *p_pDisplay,
		XErrorEvent *p_ErrorEvent )
	{
		g_sContextError = BD_TRUE;
		return 0;
	}

	LinuxWindow::LinuxWindow( )
	{
		m_Window = 0;
		m_pDisplay = BD_NULL;
		m_pXVI = BD_NULL;
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

		if( !m_pDisplay )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <ERROR> "
				"Failed to open X display\n" );

			return BD_ERROR;
		}

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

		bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <INFO> "
			"Attempting to retrieve framebuffer configurations\n" );

		BD_SINT32 FBCount = 0;
		GLXFBConfig *pFBC = glXChooseFBConfig( m_pDisplay,
			DefaultScreen( m_pDisplay ), GLXAttribs, &FBCount );

		if( !pFBC )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <ERROR> "
				"Failed to create a GLXFBConfig\n" );
			return BD_ERROR;
		}

		bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <INFO> "
			"Found %d matching framebuffer configurations\n", FBCount );

		GLXFBConfig FBC = pFBC[ 0 ];

		m_pXVI = glXGetVisualFromFBConfig( m_pDisplay, FBC );

		XFree( pFBC );

		bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <INFO> "
			"Visual ID in use: 0x%08X\n", m_pXVI->visualid );

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

		BD::GLWSExtBind( m_pDisplay, m_pXVI->screen );

		m_Window = XCreateWindow( m_pDisplay,
			RootWindow( m_pDisplay, m_pXVI->screen ),
			0, 0, m_Width, m_Height, 0, m_pXVI->depth, InputOutput,
			m_pXVI->visual, CWEventMask | CWColormap | CWBorderPixel,
			&WinAttribs );

		if( !m_Window )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::CreateWindow] <INFO> "
				"Failed to create window\n" );
			return BD_ERROR;
		}

		bdTrace( BD_NULL, "[BD::LinuxWindow::CreateWindow] <INFO> "
			"m_Window: 0x%08X | Width: %d | Height %d | Fullscreen: %s\n",
			m_Window, m_Width, m_Height, ( m_Fullscreen ? "True" : "False" ) );

		XMapWindow( m_pDisplay, m_Window );
		XMapRaised( m_pDisplay, m_Window );

		XStoreName( m_pDisplay, m_Window, "BrainDead" );
		XMoveWindow( m_pDisplay, m_Window, 0, 0 );
		XRaiseWindow( m_pDisplay, m_Window );

		XSync( m_pDisplay, False );

		// Install an X error handler so the application won't exit if
		// GL 3.0+ context allocation fails
		g_sContextError = BD_FALSE;
		int ( *pOldHandler )( Display *, XErrorEvent * ) =
			XSetErrorHandler( &ContextErrorHandler );

		if( !bglwsCreateContextAttribsARB )
		{
			// Create a GLX 1.3 context for GL <2.1
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <INFO> "
				"Creating a GLX 1.3 context\n" );
			m_GLXContext = glXCreateNewContext( m_pDisplay, FBC, GLX_RGBA_TYPE,
				0, True );
		}
		else
		{
			// HARDCODED!
			int ContextAttribs [ ] =
			{
				GLX_CONTEXT_MAJOR_VERSION_ARB,	3,
				GLX_CONTEXT_MINOR_VERSION_ARB,	3,
				// Add forward-compatible and debug if debug
				None
			};
			// !HARDCODED

			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <INFO> "
				"Attempting to create a GLX context for OpenGL 3.3... " );

			m_GLXContext = bglwsCreateContextAttribsARB( m_pDisplay, FBC,
				0, True, ContextAttribs );

			XSync( m_pDisplay, False );

			if( !g_sContextError && m_GLXContext )
			{
				bdTrace( BD_NULL, "[ OK ]\n" );
			}
			else
			{
				bdTrace( BD_NULL, "[ FAIL ]\n"
					"\t Falling back to a GLX context for OpenGL 1.0\n" );
				ContextAttribs[ 1 ] = 1;
				ContextAttribs[ 3 ] = 0;

				g_sContextError = BD_FALSE;
				m_GLXContext = bglwsCreateContextAttribsARB( m_pDisplay, FBC,
					0, True, ContextAttribs );
			}
		}

		// Sync to make sure any errors are processed
		XSync( m_pDisplay, False );

		// Restore the  original error handler
		XSetErrorHandler( pOldHandler );

		if( g_sContextError || !m_GLXContext )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <ERROR> "
				"Failed to create an OpenGL context\n" );
			return BD_ERROR;
		}

		if( !glXIsDirect( m_pDisplay, m_GLXContext ) )
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <WARN> "
				"Indirect GLX rendering context\n" );
		}
		else
		{
			bdTrace( BD_NULL, "[BD::LinuxWindow::Create] <INFO> "
				"Direct GLX rendering context\n" );
		}

		glXMakeCurrent( m_pDisplay, m_Window, m_GLXContext );
		
		// Get the version information to initialise the GL Extensions
		GLint GLMajor = 0, GLMinor = 0;

		// Attempt to get the major and minor using the GL 3.0+ method
		bglGetIntegerv( GL_MAJOR_VERSION, &GLMajor );
		bglGetIntegerv( GL_MINOR_VERSION, &GLMinor );

		// The GL_*_VERSION parameters are not recognised
		GLenum GLErr = bglGetError( );
		if( GLErr == GL_INVALID_ENUM )
		{
			// Resort to using the <GL 3.0 method
			const char *pGLVersion = ( const char * )glGetString( GL_VERSION );

			// The first number up to the first period /should/ be the major
			BD_MEMSIZE Separator = 0;
			BD_MEMSIZE StrCount = 0;
			BD_MEMSIZE StrLoc = 0;

			GLMajor = 0;
			GLMinor = 0;

			char *pNum = BD_NULL;
			for( BD_MEMSIZE i = 0; i < strlen( pGLVersion ); ++i )
			{
				char c = pGLVersion[ i ];
				if( c == '.' )
				{
					pNum = new char[ StrCount+1 ];

					strncpy( pNum, pGLVersion+StrLoc, StrCount );
					pNum[ StrCount ] = '\0';

					StrLoc = StrCount+1;
					StrCount = 0;
					// Skip the '.'
					++i;

					if( GLMajor != 0 )
					{
						GLMinor = atoi( pNum );
						break;
					}	
					if( GLMajor == 0 )
					{
						GLMajor = atoi( pNum );
					}
				}
				StrCount++;
			}

			delete [ ] pNum;
		}

		if( BD::GLExtBind( GLMajor, GLMinor ) != BD_OK )
		{
			bdTrace( BD_NULL, "[BD::LinuxRenderer::Create] <ERROR> "
				"Failed to bind OpenGL %d.%d extensions\n", GLMajor, GLMinor );	
			bdTrace( BD_NULL, "[ FAIL ]\n" );
			return BD_ERROR;
		}

		bdTrace( BD_NULL, "[BD::LinuxRenderer::Create] <INFO> "
			"Bound OpenGL %d.%d extensions\n", GLMajor, GLMinor );

		bglViewport( 0, 0, m_Width, m_Height );

		m_Created = BD_TRUE;

		return BD_OK;
	}

	BD_UINT32 LinuxWindow::DoEvents( )
	{
		XEvent Event;
		KeySym Key;
/*
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
		}*/

		
		return BD_OK;
	}

	WINDATA LinuxWindow::Data( ) const
	{
		WINDATA Data;
		memset( &Data, 0, sizeof( WINDATA ) );

		return Data;
	}
}

