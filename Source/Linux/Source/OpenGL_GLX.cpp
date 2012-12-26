#include <OGL/OpenGL.hpp>
#include <Debugger.hpp>
#include <list>
#include <string>

PFNGLXCREATECONTEXTATTRIBSARBPROC	__bglwsCreateContextAttribsARB = BD_NULL;

namespace BD
{
	BD_UINT32 GLWSExtBind( Display *p_pDisplay, int p_Screen )
	{
		int Major = 0, Minor = 0;
		glXQueryVersion( p_pDisplay, &Major, &Minor );

		if( Major == 1 && Minor == 0 )
		{
			// No extensions to get
			return BD_OK;
		}

		bdTrace( BD_NULL, "[BD::GLWSExtBind] <INFO> "
			"GLX [%d.%d]\n", Major, Minor );

		std::list< std::string > GLXExt;
		BD_MEMSIZE NumExtensions = 0, Position = 0, CharCount = 0;
		char CurExt[ 64 ] = { '\0' };
		BD_BOOL Loop = BD_TRUE;
		const char *pGLXExt = glXQueryExtensionsString( p_pDisplay, p_Screen );

		do
		{
			CurExt[ Position++ ] = pGLXExt[ CharCount ];
			if( pGLXExt[ CharCount+1 ] == 0x20 )
			{
				std::string CopyString;
				CopyString.insert( 0, CurExt, Position );
				GLXExt.push_back( CopyString );
				bdTrace( BD_NULL, "\t%s\n", CopyString.c_str( ) );
				Position = 0;
				CharCount++;
			}

			CharCount++;

			if( pGLXExt[ CharCount ] == 0x00 )
			{
				Loop = BD_FALSE;
			}
		}while( Loop );

		BD_BOOL Ret = BD_FALSE;
		
		std::list< std::string >::const_iterator GLXItr = GLXExt.begin( );

		for( ; GLXItr != GLXExt.end( ); ++GLXItr )
		{
			if( ( *GLXItr ).compare( "GLX_ARB_create_context" ) == 0 )
			{
				bdTrace( BD_NULL, "[BD::GLWSExtBind] <INFO> "
						"Binding glXCreateContextAttribsARB... " );
				Ret = ( ( __bglwsCreateContextAttribsARB =
					( PFNGLXCREATECONTEXTATTRIBSARBPROC )bglGetProcAddress(
						"glXCreateContextAttribsARB" ) ) == BD_NULL ) || Ret;

				if( __bglwsCreateContextAttribsARB )
				{
					bdTrace( BD_NULL, " [ OK ]\n" );
				}
				else
				{
					bdTrace( BD_NULL, " [ FAIL ]\n" );
				}

				if( Ret )
				{

					bdTrace( BD_NULL, "[BD::GLWSExtBind] <ERROR> "
						"Failed to bind GLX_ARB_create_context family of "
						"GLX extensions" );
					bdAssert( ( Ret == BD_FALSE ) );
					return BD_ERROR;
				}
			}
		}
		return BD_OK;
	}
}

