#include <OGL/OpenGL.hpp>
#include <Debugger.hpp>
#include <list>
#include <string>


PFNGLACTIVETEXTUREPROC				__bglActiveTexture = BD_NULL;
PFNGLATTACHSHADERPROC				__bglAttachShader = BD_NULL;
PFNGLBINDATTRIBLOCATIONPROC			__bglBindAttribLocation = BD_NULL;
PFNGLGETATTRIBLOCATIONPROC			__bglGetAttribLocation = BD_NULL;
PFNGLGETSTRINGIPROC					__bglGetStringi = BD_NULL;
PFNGLBINDBUFFERPROC					__bglBindBuffer = BD_NULL;
PFNGLBINDVERTEXARRAYPROC			__bglBindVertexArray = BD_NULL;
PFNGLBUFFERDATAPROC					__bglBufferData = BD_NULL;
PFNGLBUFFERSUBDATAPROC				__bglBufferSubData = BD_NULL;
PFNGLCOMPILESHADERPROC				__bglCompileShader = BD_NULL;
PFNGLCREATEPROGRAMPROC				__bglCreateProgram = BD_NULL;
PFNGLCREATESHADERPROC				__bglCreateShader = BD_NULL;
PFNGLDELETEPROGRAMPROC				__bglDeleteProgram = BD_NULL;
PFNGLDELETESHADERPROC				__bglDeleteShader = BD_NULL;
PFNGLDELETEVERTEXARRAYSPROC			__bglDeleteVertexArrays = BD_NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC	__bglEnableVertexAttribArray = BD_NULL;
PFNGLGENBUFFERSPROC					__bglGenBuffers = BD_NULL;
PFNGLGENVERTEXARRAYSPROC			__bglGenVertexArrays = BD_NULL;
PFNGLGETPROGRAMINFOLOGPROC			__bglGetProgramInfoLog = BD_NULL;
PFNGLGETPROGRAMIVPROC				__bglGetProgramiv = BD_NULL;
PFNGLGETSHADERINFOLOGPROC			__bglGetShaderInfoLog = BD_NULL;
PFNGLGETSHADERIVPROC				__bglGetShaderiv = BD_NULL;
PFNGLGETUNIFORMLOCATIONPROC			__bglGetUniformLocation = BD_NULL;
PFNGLISVERTEXARRAYPROC				__bglIsVertexArray = BD_NULL;
PFNGLLINKPROGRAMPROC				__bglLinkProgram = BD_NULL;
PFNGLSHADERSOURCEPROC				__bglShaderSource = BD_NULL;
PFNGLUNIFORM1FPROC					__bglUniform1f = BD_NULL;
PFNGLUNIFORM1FVPROC					__bglUniform1fv = BD_NULL;
PFNGLUNIFORM1IPROC					__bglUniform1i = BD_NULL;
PFNGLUNIFORM1IVPROC					__bglUniform1iv = BD_NULL;
PFNGLUNIFORM2FPROC					__bglUniform2f = BD_NULL;
PFNGLUNIFORM2FVPROC					__bglUniform2fv = BD_NULL;
PFNGLUNIFORM2IPROC					__bglUniform2i = BD_NULL;
PFNGLUNIFORM2IVPROC					__bglUniform2iv = BD_NULL;
PFNGLUNIFORM3FPROC					__bglUniform3f = BD_NULL;
PFNGLUNIFORM3FVPROC					__bglUniform3fv = BD_NULL;
PFNGLUNIFORM3IPROC					__bglUniform3i = BD_NULL;
PFNGLUNIFORM3IVPROC					__bglUniform3iv = BD_NULL;
PFNGLUNIFORM4FPROC					__bglUniform4f = BD_NULL;
PFNGLUNIFORM4FVPROC					__bglUniform4fv = BD_NULL;
PFNGLUNIFORM4IPROC					__bglUniform4i = BD_NULL;
PFNGLUNIFORM4IVPROC					__bglUniform4iv = BD_NULL;
PFNGLUNIFORMMATRIX2FVPROC			__bglUniformMatrix2fv = BD_NULL;
PFNGLUNIFORMMATRIX3FVPROC			__bglUniformMatrix3fv = BD_NULL;
PFNGLUNIFORMMATRIX4FVPROC			__bglUniformMatrix4fv = BD_NULL;
PFNGLUSEPROGRAMPROC					__bglUseProgram = BD_NULL;
PFNGLVALIDATEPROGRAMPROC			__bglValidateProgram = BD_NULL;
PFNGLVERTEXATTRIBPOINTERPROC		__bglVertexAttribPointer = BD_NULL;


namespace BD
{
	static BD_BOOL s_GLExtLoaded = BD_FALSE;

	BD_BOOL GlExt::s_Loaded = BD_FALSE;
	std::map<std::string, void*> GlExt::s_ExtensionMap;
	std::string GlExt::s_ExtensionError = "";
	BD_UINT32 GlExt::s_ExtensionErrorCount = 0;

	BD_BOOL GLExtBind( GLint p_Major, GLint p_Minor )
	{
		// Get the GL extensions list and attempt to load them
		std::list< std::string > Extensions;
		GLint NumExtensions = 0;
		bglGetIntegerv( GL_NUM_EXTENSIONS, &NumExtensions );

		bdTrace( BD_NULL, "[BD::GLExtLoad] <INFO> "
			"%d OpenGL Extensions supported:\n", NumExtensions );

		if( p_Major >= 3 )
		{
			// Bootstrap glGetStringi
			__bglGetStringi = ( PFNGLGETSTRINGIPROC )bglGetProcAddress(
				"glGetStringi" );
			bdAssert( bglGetStringi != BD_NULL );

			for( BD_MEMSIZE i = 0; i < NumExtensions; ++i )
			{
				Extensions.push_back(
					( char * )bglGetStringi( GL_EXTENSIONS, i ) );
				bdTrace( BD_NULL, "\t%s\n",
					bglGetStringi( GL_EXTENSIONS, i ) );
			}
		}
		else
		{
			char CurExt[ 64 ] = { '\0' };

			BD_MEMSIZE Position = 0, CharCount = 0;
			BD_BOOL Loop = BD_TRUE;

			const char *pGLExtensions =
				( const char * )bglGetString( GL_EXTENSIONS );

			do
			{
				CurExt[ Position++ ] = pGLExtensions[ CharCount ];

				if( pGLExtensions[ CharCount+1 ] == 0x20 )
				{
					std::string CopyString;
					CopyString.insert( 0, CurExt, Position );
					Extensions.push_back( CopyString );
					bdTrace( BD_NULL, "\t%s\n", CopyString.c_str( ) );
					Position = 0;
					CharCount++;
				}
				CharCount++;

				if( pGLExtensions[ CharCount ] == 0x00 )
				{
					Loop = BD_FALSE;
				}

			} while( Loop );
		}

		BD_BOOL Ret = BD_FALSE;
		std::list< std::string >::const_iterator ExtItr = Extensions.begin( );

		// Bind the functions based on the family they happen to reside in
		for( ; ExtItr != Extensions.end( ); ++ExtItr )
		{
			if( ( *ExtItr ).compare( "GL_ARB_vertex_array_object" ) == 0 )
			{
				Ret = ( ( __bglBindVertexArray =
					( PFNGLBINDVERTEXARRAYPROC )bglGetProcAddress(
						"glBindVertexArray" ) ) == BD_NULL ) || Ret;
				Ret = ( ( __bglDeleteVertexArrays =
					( PFNGLDELETEVERTEXARRAYSPROC )bglGetProcAddress(
						"glDeleteVertexArrays" ) ) = BD_NULL ) || Ret;
				Ret = ( ( __bglGenVertexArrays =
					( PFNGLGENVERTEXARRAYSPROC )bglGetProcAddress(
						"glGenVertexArrays" ) ) == BD_NULL ) || Ret;
				Ret = ( ( __bglIsVertexArray =
					( PFNGLISVERTEXARRAYPROC )bglGetProcAddress(
						"glIsVertexArray" ) ) == BD_NULL ) || Ret;

				bdAssert( Ret );
			}

			if( ( *ExtItr ).compare( "GL_ARB_shader_objects" ) == 0 )
			{
				Ret = ( ( __bglUniform1f =
					( PFNGLUNIFORM1FPROC )bglGetProcAddress(
						"glUniform1f" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform1fv =
					( PFNGLUNIFORM1FVPROC )bglGetProcAddress(
						"glUniform1fv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform1i =
					( PFNGLUNIFORM1IPROC )bglGetProcAddress(
						"glUniform1i" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform1iv =
					( PFNGLUNIFORM1IVPROC )bglGetProcAddress(
						"glUniform1iv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform2f =
					( PFNGLUNIFORM2FPROC )bglGetProcAddress(
						"glUniform2f" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform2fv =
					( PFNGLUNIFORM2FVPROC )bglGetProcAddress(
						"glUniform2fv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform2i =
					( PFNGLUNIFORM2IPROC )bglGetProcAddress(
						"glUniform2i" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform2iv =
					( PFNGLUNIFORM2IVPROC )bglGetProcAddress(
						"glUniform2iv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform3f =
					( PFNGLUNIFORM3FPROC )bglGetProcAddress(
						"glUniform3f" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform3fv =
					( PFNGLUNIFORM3FVPROC )bglGetProcAddress(
						"glUniform3fv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform3i =
					( PFNGLUNIFORM3IPROC )bglGetProcAddress(
						"glUniform3i" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform3iv =
					( PFNGLUNIFORM3IVPROC )bglGetProcAddress(
						"glUniform3iv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform4f =
					( PFNGLUNIFORM4FPROC )bglGetProcAddress(
						"glUniform4f" ) ) == BD_NULL ) || Ret;
				
				Ret = ( ( __bglUniform4fv =
					( PFNGLUNIFORM4FVPROC )bglGetProcAddress(
						"glUniform4fv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform4i =
					( PFNGLUNIFORM4IPROC )bglGetProcAddress(
						"glUniform4i" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniform4iv =
					( PFNGLUNIFORM4IVPROC )bglGetProcAddress(
						"glUniform4iv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniformMatrix2fv =
					( PFNGLUNIFORMMATRIX2FVPROC )bglGetProcAddress(
						"glUniformMatrix2fv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniformMatrix3fv =
					( PFNGLUNIFORMMATRIX3FVPROC )bglGetProcAddress(
						"glUniformMatrix3fv" ) ) == BD_NULL ) || Ret;

				Ret = ( ( __bglUniformMatrix4fv =
					( PFNGLUNIFORMMATRIX4FVPROC )bglGetProcAddress(
						"glUniformMatrix4fv" ) ) == BD_NULL ) || Ret;

				bdAssert( Ret );
			}

			if( ( *ExtItr ).compare( "GL_ARB_vertex_shader" ) == 0 )
			{
				Ret = ( ( __bglEnableVertexAttribArray =
					( PFNGLENABLEVERTEXATTRIBARRAYPROC )bglGetProcAddress(
						"glEnableVertexAttribArray" ) ) == BD_NULL ) || Ret;

				bdAssert( Ret );
			}
		}

		
		return BD_OK;
	}

	BD_BOOL GlExt::Load()
	{
		return BD_OK;
	}

	BD_BOOL GlExt::IsLoaded()
	{
		return s_Loaded;
	}

	std::string GlExt::GetError()
	{
		return s_ExtensionError;
	}

	BD_UINT32 GlExt::GetErrorCount()
	{

		return s_ExtensionErrorCount;
	}

}
