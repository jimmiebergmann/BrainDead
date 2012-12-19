#include <OpenGL/OpenGL.hpp>

#ifdef _WINDOWS
	#define GETPROCADDRESS(x) (wglGetProcAddress(x))
#endif

PFNGLACTIVETEXTUREARBPROC GlExt::glActiveTextureARB;
PFNGLATTACHOBJECTARBPROC GlExt::glAttachObjectARB;
PFNGLBINDATTRIBLOCATIONARBPROC GlExt::glBindAttribLocationARB;
PFNGLGETATTRIBLOCATIONARBPROC GlExt::glGetAttribLocationARB;
PFNGLBINDBUFFERARBPROC GlExt::glBindBufferARB;
PFNGLBINDVERTEXARRAYPROC GlExt::glBindVertexArray;
PFNGLBUFFERDATAARBPROC GlExt::glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC GlExt::glBufferSubDataARB;
PFNGLCOMPILESHADERARBPROC GlExt::glCompileShaderARB;
PFNGLCREATEPROGRAMOBJECTARBPROC GlExt::glCreateProgramObjectARB;
PFNGLCREATESHADEROBJECTARBPROC GlExt::glCreateShaderObjectARB;
PFNGLDELETEOBJECTARBPROC GlExt::glDeleteObjectARB;
PFNGLDELETEVERTEXARRAYSPROC GlExt::glDeleteVertexArrays;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC GlExt::glEnableVertexAttribArrayARB;
PFNGLGENBUFFERSARBPROC GlExt::glGenBuffersARB;
PFNGLGENVERTEXARRAYSPROC GlExt::glGenVertexArrays;
PFNGLGETPROGRAMINFOLOGPROC GlExt::glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC GlExt::glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC GlExt::glGetShaderInfoLog;
PFNGLGETSHADERIVPROC GlExt::glGetShaderiv;
PFNGLGETUNIFORMLOCATIONARBPROC GlExt::glGetUniformLocationARB;
PFNGLLINKPROGRAMARBPROC GlExt::glLinkProgramARB;
PFNGLSHADERSOURCEARBPROC GlExt::glShaderSourceARB;
PFNGLUNIFORM1FARBPROC GlExt::glUniform1fARB;
PFNGLUNIFORM1IARBPROC GlExt::glUniform1iARB;
PFNGLUNIFORM2FARBPROC GlExt::glUniform2fARB;
PFNGLUNIFORM2IARBPROC GlExt::glUniform2iARB;
PFNGLUNIFORM3FARBPROC GlExt::glUniform3fARB;
PFNGLUNIFORM4FARBPROC GlExt::glUniform4fARB;
PFNGLUNIFORMMATRIX4FVARBPROC GlExt::glUniformMatrix4fvARB;
PFNGLUSEPROGRAMPROC GlExt::glUseProgram;
PFNGLUSEPROGRAMOBJECTARBPROC GlExt::glUseProgramObjectARB;
PFNGLVALIDATEPROGRAMPROC GlExt::glValidateProgram;
PFNGLVERTEXATTRIBPOINTERARBPROC GlExt::glVertexAttribPointerARB;


bool GlExt::s_Loaded = false;
std::map<std::string, void*> GlExt::s_ExtensionMap;
std::string GlExt::s_ExtensionError = "";
unsigned int GlExt::s_ExtensionErrorCount = 0;

bool GlExt::Load()
{
	// Make sure everything is clear.
	s_Loaded = false;
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

	// Make sure all the extensions are ok.
	for(std::map<std::string, void*>::iterator it = s_ExtensionMap.begin(); it != s_ExtensionMap.end(); it++)
	{
		if(it->second == NULL)
		{
			s_ExtensionErrorCount ++;
			s_ExtensionError += it->first + "\n";
		}
	}

	// Return false if any of the extensions failed.
	if(s_ExtensionErrorCount > 0)
	{
		return false;
	}

	// Everything went fine.
	return (s_Loaded = true);
}

bool GlExt::IsLoaded()
{
	return s_Loaded;
}

std::string GlExt::GetError()
{
	return s_ExtensionError;
}

unsigned int GlExt::GetErrorCount()
{

	return s_ExtensionErrorCount;
}