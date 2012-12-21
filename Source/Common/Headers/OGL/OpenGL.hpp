#ifndef __BRAINDEAD_OPENGL_HPP__
#define __BRAINDEAD_OPENGL_HPP__

#include <DataTypes.hpp>
#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
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
extern PFNGLLINKPROGRAMPROC					__bglLinkProgram;
extern PFNGLSHADERSOURCEPROC				__bglShaderSource;
extern PFNGLUNIFORM1FPROC					__bglUniform1f;
extern PFNGLUNIFORM1IPROC					__bglUniform1i;
extern PFNGLUNIFORM2FPROC					__bglUniform2f;
extern PFNGLUNIFORM2IPROC					__bglUniform2i;
extern PFNGLUNIFORM3FPROC					__bglUniform3f;
extern PFNGLUNIFORM4FPROC					__bglUniform4f;
extern PFNGLUNIFORMMATRIX4FVPROC			__bglUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC					__bglUseProgram;
extern PFNGLVALIDATEPROGRAMPROC				__bglValidateProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC			__bglVertexAttribPointer;

///////////////////////////////////////////////////////////////////////////////
// GL CORE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglClear			glClear
#define bglClearColor		glClearColor

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

#ifdef __cplusplus
}
#endif

namespace BD
{

	class GlExt
	{

	public:

		static BD_UINT32 Load();
		static BD_BOOL IsLoaded();
		static std::string GetError();
		static BD_UINT32 GetErrorCount();

	private:

		static BD_BOOL s_Loaded;
		static std::map<std::string, void*> s_ExtensionMap;
		static std::string s_ExtensionError;
		static BD_UINT32 s_ExtensionErrorCount;

	};

}

#endif
