#include <OpenGL/OpenGL.hpp>

#ifdef PLATFORM_WINDOWS
	#define GETPROCADDRESS(x) (wglGetProcAddress(x))
#endif

PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = BD_NULL;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB = BD_NULL;
PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB = BD_NULL;
PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB = BD_NULL;
PFNGLBINDBUFFERARBPROC glBindBufferARB = BD_NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = BD_NULL;
PFNGLBUFFERDATAARBPROC glBufferDataARB = BD_NULL;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = BD_NULL;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB = BD_NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB = BD_NULL;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB = BD_NULL;
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB = BD_NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = BD_NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB = BD_NULL;
PFNGLGENBUFFERSARBPROC glGenBuffersARB = BD_NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = BD_NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = BD_NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = BD_NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = BD_NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = BD_NULL;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB = BD_NULL;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB = BD_NULL;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB = BD_NULL;
PFNGLUNIFORM1FARBPROC glUniform1fARB = BD_NULL;
PFNGLUNIFORM1IARBPROC glUniform1iARB = BD_NULL;
PFNGLUNIFORM2FARBPROC glUniform2fARB = BD_NULL;
PFNGLUNIFORM2IARBPROC glUniform2iARB = BD_NULL;
PFNGLUNIFORM3FARBPROC glUniform3fARB = BD_NULL;
PFNGLUNIFORM4FARBPROC glUniform4fARB = BD_NULL;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB = BD_NULL;
PFNGLUSEPROGRAMPROC glUseProgram = BD_NULL;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB = BD_NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = BD_NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB = BD_NULL;

namespace BD
{
	BD_BOOL GlExt::s_Loaded = BD_FALSE;
	std::map<std::string, void*> GlExt::s_ExtensionMap;
	std::string GlExt::s_ExtensionError = "";
	BD_UINT32 GlExt::s_ExtensionErrorCount = 0;

	BD_BOOL GlExt::Load()
	{
		// Make sure everything is clear.
		s_Loaded = BD_FALSE;
		s_ExtensionMap.clear();
		s_ExtensionError = "";
		s_ExtensionErrorCount = 0;

		// Store the extension pointers in a std::map as well.
		// Then, we can easily check which extension failed.
		s_ExtensionMap["glActiveTextureARB"] = (void*)( glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) GETPROCADDRESS("glActiveTextureARB"));
		s_ExtensionMap["glAttachObjectARB"] = (void*)( glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) GETPROCADDRESS("glAttachObjectARB"));
		s_ExtensionMap["glBindAttribLocationARB"] = (void*)( glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) GETPROCADDRESS("glBindAttribLocationARB"));
		s_ExtensionMap["glGetAttribLocationARB"] = (void*)( glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) GETPROCADDRESS("glGetAttribLocationARB"));
		s_ExtensionMap["glBindBufferARB"] = (void*)( glBindBufferARB = (PFNGLBINDBUFFERARBPROC) GETPROCADDRESS("glBindBufferARB"));
		s_ExtensionMap["glBindVertexArray"] = (void*)( glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) GETPROCADDRESS("glBindVertexArray"));
		s_ExtensionMap["glBufferDataARB"] = (void*)( glBufferDataARB = (PFNGLBUFFERDATAARBPROC) GETPROCADDRESS("glBufferDataARB"));
		s_ExtensionMap["glBufferSubDataARB"] = (void*)( glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) GETPROCADDRESS("glBufferSubDataARB"));
		s_ExtensionMap["glCompileShaderARB"] = (void*)( glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) GETPROCADDRESS("glCompileShaderARB"));
		s_ExtensionMap["glCreateProgramObjectARB"] = (void*)( glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) GETPROCADDRESS("glCreateProgramObjectARB"));
		s_ExtensionMap["glCreateShaderObjectARB"] = (void*)( glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) GETPROCADDRESS("glCreateShaderObjectARB"));
		s_ExtensionMap["glDeleteObjectARB"] = (void*)( glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) GETPROCADDRESS("glDeleteObjectARB"));
		s_ExtensionMap["glDeleteVertexArrays"] = (void*)( glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) GETPROCADDRESS("glDeleteVertexArrays"));
		s_ExtensionMap["glEnableVertexAttribArrayARB"] = (void*)( glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) GETPROCADDRESS("glEnableVertexAttribArrayARB"));
		s_ExtensionMap["glGenBuffersARB"] = (void*)( glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) GETPROCADDRESS("glGenBuffersARB"));
		s_ExtensionMap["glGenVertexArrays"] = (void*)( glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) GETPROCADDRESS("glGenVertexArrays"));
		s_ExtensionMap["glGetProgramInfoLog"] = (void*)( glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) GETPROCADDRESS("glGetProgramInfoLog"));
		s_ExtensionMap["glGetProgramiv"] = (void*)( glGetProgramiv = (PFNGLGETPROGRAMIVPROC) GETPROCADDRESS("glGetProgramiv"));
		s_ExtensionMap["glGetShaderInfoLog"] = (void*)( glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) GETPROCADDRESS("glGetShaderInfoLog"));
		s_ExtensionMap["glGetShaderiv"] = (void*)( glGetShaderiv = (PFNGLGETSHADERIVPROC) GETPROCADDRESS("glGetShaderiv"));
		s_ExtensionMap["glGetUniformLocationARB"] = (void*)( glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) GETPROCADDRESS("glGetUniformLocationARB"));
		s_ExtensionMap["glLinkProgramARB"] = (void*)( glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) GETPROCADDRESS("glLinkProgramARB"));
		s_ExtensionMap["glShaderSourceARB"] = (void*)( glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) GETPROCADDRESS("glShaderSourceARB"));
		s_ExtensionMap["glUniform1fARB"] = (void*)( glUniform1fARB = (PFNGLUNIFORM1FARBPROC) GETPROCADDRESS("glUniform1fARB"));
		s_ExtensionMap["glUniform1iARB"] = (void*)( glUniform1iARB = (PFNGLUNIFORM1IARBPROC) GETPROCADDRESS("glUniform1iARB"));
		s_ExtensionMap["glUniform2fARB"] = (void*)( glUniform2fARB = (PFNGLUNIFORM2FARBPROC) GETPROCADDRESS("glUniform2fARB"));
		s_ExtensionMap["glUniform2iARB"] = (void*)( glUniform2iARB = (PFNGLUNIFORM2IARBPROC) GETPROCADDRESS("glUniform2iARB"));
		s_ExtensionMap["glUniform3fARB"] = (void*)( glUniform3fARB = (PFNGLUNIFORM3FARBPROC) GETPROCADDRESS("glUniform3fARB"));
		s_ExtensionMap["glUniform4fARB"] = (void*)( glUniform4fARB = (PFNGLUNIFORM4FARBPROC) GETPROCADDRESS("glUniform4fARB"));
		s_ExtensionMap["glUniformMatrix4fvARB"] = (void*)( glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) GETPROCADDRESS("glUniformMatrix4fvARB"));
		s_ExtensionMap["glUseProgram"] = (void*)( glUseProgram = (PFNGLUSEPROGRAMPROC)GETPROCADDRESS("glUseProgram"));
		s_ExtensionMap["glUseProgramObjectARB"] = (void*)( glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)GETPROCADDRESS("glUseProgramObjectARB"));
		s_ExtensionMap["glValidateProgram"] = (void*)( glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GETPROCADDRESS("glValidateProgram"));
		s_ExtensionMap["glVertexAttribPointerARB"] = (void*)( glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)GETPROCADDRESS("glVertexAttribPointerARB"));

		// Make sure all the extensions are ok by checking if any function is BD_NULL.
		for(std::map<std::string, void*>::iterator it = s_ExtensionMap.begin(); it != s_ExtensionMap.end(); it++)
		{
			if(it->second == BD_NULL)
			{
				s_ExtensionErrorCount ++;
				s_ExtensionError += it->first + "\n";
			}
		}

		// Return false if any of the extensions failed.
		if(s_ExtensionErrorCount > 0)
		{
			return BD_ERROR;
		}

		// Everything went fine.
		s_Loaded = BD_TRUE;
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