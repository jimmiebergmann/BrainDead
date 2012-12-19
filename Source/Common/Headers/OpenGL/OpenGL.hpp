#ifndef __BRAINDEAD_OPENGL_HPP__
#define __BRAINDEAD_OPENGL_HPP__

#include <Windows.h>
#include <gl/gl.h>
#include <GL/gl.h>
#include "glext.h"
#ifdef _WINDOWS
#include <OpenGL/wglext.h>
#endif

#include <string>
#include <map>


class GlExt
{

public:


	static bool Load();
	static bool IsLoaded();
	static std::string GetError();
	static unsigned int GetErrorCount();

	static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
	static PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
	static PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
	static PFNGLGETATTRIBLOCATIONARBPROC  glGetAttribLocationARB;
	static PFNGLBINDBUFFERARBPROC glBindBufferARB;
	static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	static PFNGLBUFFERDATAARBPROC glBufferDataARB;
	static PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
	static PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
	static PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
	static PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
	static PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
	static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
	static PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
	static PFNGLGENBUFFERSARBPROC glGenBuffersARB;
	static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	static PFNGLGETPROGRAMIVPROC glGetProgramiv;
	static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	static PFNGLGETSHADERIVPROC glGetShaderiv;
	static PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
	static PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
	static PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
    static PFNGLUNIFORM1FARBPROC glUniform1fARB;
	static PFNGLUNIFORM1IARBPROC glUniform1iARB;
	static PFNGLUNIFORM2FARBPROC glUniform2fARB;
	static PFNGLUNIFORM2IARBPROC glUniform2iARB;
	static PFNGLUNIFORM3FARBPROC glUniform3fARB;
	static PFNGLUNIFORM4FARBPROC glUniform4fARB;
	static PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;
	static PFNGLUSEPROGRAMPROC glUseProgram;
	static PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
	static PFNGLVALIDATEPROGRAMPROC glValidateProgram;
	static PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;


private:

	static bool m_pLoaded;
	static std::map<std::string, void*> m_pExtensionMap;
	static std::string m_pExtensionError;
	static unsigned int m_pExtensionErrorCount;

};

#endif
