#ifndef __BRAINDEAD_OPENGL_HPP__
#define __BRAINDEAD_OPENGL_HPP__

#include <DataTypes.hpp>
#include <Windows.h>
#include <gl/gl.h>
#include <GL/gl.h>
#include "glext.h"
#ifdef PLATFORM_WINDOWS
#include <OpenGL/wglext.h>
#endif

#include <string>
#include <map>

extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
extern PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
extern PFNGLGETATTRIBLOCATIONARBPROC  glGetAttribLocationARB;
extern PFNGLBINDBUFFERARBPROC glBindBufferARB;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB;
extern PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
extern PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
extern PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
extern PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
extern PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
extern PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
extern PFNGLUNIFORM1FARBPROC glUniform1fARB;
extern PFNGLUNIFORM1IARBPROC glUniform1iARB;
extern PFNGLUNIFORM2FARBPROC glUniform2fARB;
extern PFNGLUNIFORM2IARBPROC glUniform2iARB;
extern PFNGLUNIFORM3FARBPROC glUniform3fARB;
extern PFNGLUNIFORM4FARBPROC glUniform4fARB;
extern PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;

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
