#ifndef __BRAINDEAD_OPENGL_HPP__
#define __BRAINDEAD_OPENGL_HPP__

#include <DataTypes.hpp>
#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#include <gl/glext.h>
#include <GL/wglext.h>
#elif PLATFORM_LINUX
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glxext.h>
#else
#error No platform pre-processor directive specified
#endif
#include <string>
#include <map>

#ifdef __cplusplus
extern "C"
{
#endif

extern PFNGLACTIVETEXTUREPROC				__bglActiveTexture;
extern PFNGLATTACHSHADERPROC				__bglAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC			__bglBindAttribLocation;
extern PFNGLGETATTRIBLOCATIONPROC			__bglGetAttribLocation;
extern PFNGLBINDBUFFERPROC					__bglBindBuffer;
extern PFNGLBINDVERTEXARRAYPROC				__bglBindVertexArray;
extern PFNGLBUFFERDATAPROC					__bglBufferData;
extern PFNGLBUFFERSUBDATAPROC				__bglBufferSubData;
extern PFNGLCOMPILESHADERPROC				__bglCompileShader;
extern PFNGLCREATEPROGRAMPROC				__bglCreateProgram;
extern PFNGLCREATESHADERPROC				__bglCreateShader;
extern PFNGLDELETEPROGRAMPROC				__bglDeleteProgram;
extern PFNGLDELETESHADERPROC				__bglDeleteShader;
extern PFNGLDELETEVERTEXARRAYSPROC			__bglDeleteVertexArrays;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC		__bglEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC					__bglGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC				__bglGenVertexArrays;
extern PFNGLGETPROGRAMINFOLOGPROC			__bglGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC				__bglGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC			__bglGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC					__bglGetShaderiv;
extern PFNGLGETUNIFORMLOCATIONPROC			__bglGetUniformLocation;
extern PFNGLISVERTEXARRAYPROC				__bglIsVertexArray;
extern PFNGLLINKPROGRAMPROC					__bglLinkProgram;
extern PFNGLSHADERSOURCEPROC				__bglShaderSource;
extern PFNGLUNIFORM1FPROC					__bglUniform1f;
extern PFNGLUNIFORM1FVPROC					__bglUniform1fv;
extern PFNGLUNIFORM1IPROC					__bglUniform1i;
extern PFNGLUNIFORM1IVPROC					__bglUniform1iv;
extern PFNGLUNIFORM2FPROC					__bglUniform2f;
extern PFNGLUNIFORM2FVPROC					__bglUniform2fv;
extern PFNGLUNIFORM2IPROC					__bglUniform2i;
extern PFNGLUNIFORM2IVPROC					__bglUniform2iv;
extern PFNGLUNIFORM3FPROC					__bglUniform3f;
extern PFNGLUNIFORM3FVPROC					__bglUniform3fv;
extern PFNGLUNIFORM3IPROC					__bglUniform3i;
extern PFNGLUNIFORM3IVPROC					__bglUniform3iv;
extern PFNGLUNIFORM4FPROC					__bglUniform4f;
extern PFNGLUNIFORM4FVPROC					__bglUniform4fv;
extern PFNGLUNIFORM4IPROC					__bglUniform4i;
extern PFNGLUNIFORM4IVPROC					__bglUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC			__bglUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC			__bglUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC			__bglUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC					__bglUseProgram;
extern PFNGLVALIDATEPROGRAMPROC				__bglValidateProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC			__bglVertexAttribPointer;

///////////////////////////////////////////////////////////////////////////////
// GL CORE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglClear			glClear
#define bglClearColor		glClearColor
#define bglGetIntegerv		glGetIntegerv
#define bglGetString		glGetString

///////////////////////////////////////////////////////////////////////////////
// GL ANCILARY FUNCTIONS //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglGetStringi		__bglGetStringi

///////////////////////////////////////////////////////////////////////////////
// GL SHADER FUNCTIONS ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglAttachShader					__bglAttachShader
#define bglBindAttribLocation			__bglBindAttribLocation
#define bglBindBuffer					__bglBindBuffer
#define bglBufferData					__bglBufferData
#define bglBufferSubData				__bglBufferSubData
#define bglCompileShader				__bglCompileShader
#define bglCreateProgram				__bglCreateProgram
#define bglCreateShader					__bglCreateShader
#define bglDeleteProgram				__bglDeleteProgram
#define bglDeleteShader					__bglDeleteShader
#define bglEnableVertexAttribArray		__bglEnableVertexAttribArray
#define bglGenBuffers					__bglGenBuffers
#define bglGetAttribLocation			__bglGetAttribLocation
#define bglGetProgramInfoLog			__bglGetProgramInfoLog
#define bglGetProgramiv					__bglGetProgramiv
#define bglGetShaderInfoLog				__bglGetShaderInfoLog
#define bglGetShaderiv					__bglGetShaderiv
#define bglGetUniformLocation			__bglGetUniformLocation
#define bglLinkProgram					__bglLinkProgram
#define bglShaderSource					__bglShaderSource
#define bglUniform1f					__bglUniform1f
#define bglUniform1i					__bglUniform1i
#define bglUniform2f					__bglUniform2f
#define bglUnifrom2i					__bglUniform2i
#define bglUniform3f					__bglUniform3f
#define bglUniform3i					__bglUniform3i
#define bglUniform4f					__bglUniform4f
#define bglUniform4i					__bglUniform4i
#define bglUniformMatrix4fv				__bglUniformMatrix4fv
#define bglUseProgram					__bglUseProgram
#define bglValidateProgram				__bglValidateProgram
#define bglVertexAttribPointer			__bglVertexAttribPointer

///////////////////////////////////////////////////////////////////////////////
// GL VERTEX ATTRIBUTE OBJECT FUNCTIONS //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglBindVertexArray		__bglBindVertexArray
#define bglDeleteVertexArrays	__bglDeleteVertexArrays
#define bglGetVertexArrays		__bglGetVertexArrays
#define bglIsVertexArray		__bglIsVertexArray

///////////////////////////////////////////////////////////////////////////////
// GL TEXTURE FUNCTIONS ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglActiveTexture	__bglActiveTexture

///////////////////////////////////////////////////////////////////////////////
// WINDOWING SYSTEM EXTENSIONS ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#ifdef PLATFORM_WINDOWS
	#define bglGetProcAddress( p_GLExt ) wglGetProcAddress( p_GLExt )
	#define PFNWGLGETEXTENSIONSSTRINGPROC	__bglwsGetExtensionsString
	#define PFNWGLCREATECONTEXTATTRIBSPROC	__bglwsCreateContextAttribs
#elif PLATFORM_LINUX
	#define bglGetProcAddress( p_GLExt ) glXGetProcAddress(\
		( const GLubyte * )p_GLExt )
	#define PFNGLXCREATECONTEXTATTRIBSPROC	__bglwsCreateContextAttribs
#else
	#error No platform specified as a pre-processor directive
#endif

#ifdef __cplusplus
}
#endif

namespace BD
{
	// GL Extensions functions
	BD_UINT32 GLExtBind( GLint p_Major, GLint p_Minor );

	// GL Windowing System Extensions functions
	BD_UINT32 GLWSExtBind( );

	class GlExt
	{

	public:

		static BD_UINT32 Load( );
		static BD_BOOL IsLoaded( );
		static std::string GetError( );
		static BD_UINT32 GetErrorCount( );

	private:

		static BD_BOOL s_Loaded;
		static std::map< std::string, void* > s_ExtensionMap;
		static std::string s_ExtensionError;
		static BD_UINT32 s_ExtensionErrorCount;

	};

}

#endif
