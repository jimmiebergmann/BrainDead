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
extern PFNGLUSEPROGRAMPROC					__bglUseProgram;
extern PFNGLVALIDATEPROGRAMPROC				__bglValidateProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC			__bglVertexAttribPointer;

///////////////////////////////////////////////////////////////////////////////
// GL CORE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define bglClear			glClear

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
#define bglGetAttribLocation			__bglGetAttribLocation
#define bglGetProgramiv					__bglGetProgramiv
#define bglLinkProgram					__bglLinkProgram

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
