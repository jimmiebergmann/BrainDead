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


bool GlExt::m_pLoaded = false;
std::map<std::string, void*> GlExt::m_pExtensionMap;
std::string GlExt::m_pExtensionError = "";
unsigned int GlExt::m_pExtensionErrorCount = 0;

bool GlExt::Load()
{
	// Make sure everything is clear.
	m_pLoaded = false;
	m_pExtensionMap.clear();
	m_pExtensionError = "";
	m_pExtensionErrorCount = 0;

	// Store the extension pointers in a std::map as well.
	// Then, we can easily check which extension failed.
	m_pExtensionMap["glActiveTextureARB"] = (void*)( glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) GETPROCADDRESS("glActiveTextureARB"));
	m_pExtensionMap["glAttachObjectARB"] = (void*)( glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) GETPROCADDRESS("glAttachObjectARB"));
	m_pExtensionMap["glBindAttribLocationARB"] = (void*)( glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) GETPROCADDRESS("glBindAttribLocationARB"));
	m_pExtensionMap["glGetAttribLocationARB"] = (void*)( glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) GETPROCADDRESS("glGetAttribLocationARB"));
	m_pExtensionMap["glBindBufferARB"] = (void*)( glBindBufferARB = (PFNGLBINDBUFFERARBPROC) GETPROCADDRESS("glBindBufferARB"));
	m_pExtensionMap["glBindVertexArray"] = (void*)( glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) GETPROCADDRESS("glBindVertexArray"));
	m_pExtensionMap["glBufferDataARB"] = (void*)( glBufferDataARB = (PFNGLBUFFERDATAARBPROC) GETPROCADDRESS("glBufferDataARB"));
	m_pExtensionMap["glBufferSubDataARB"] = (void*)( glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) GETPROCADDRESS("glBufferSubDataARB"));
	m_pExtensionMap["glCompileShaderARB"] = (void*)( glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) GETPROCADDRESS("glCompileShaderARB"));
	m_pExtensionMap["glCreateProgramObjectARB"] = (void*)( glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) GETPROCADDRESS("glCreateProgramObjectARB"));
	m_pExtensionMap["glCreateShaderObjectARB"] = (void*)( glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) GETPROCADDRESS("glCreateShaderObjectARB"));
	m_pExtensionMap["glDeleteObjectARB"] = (void*)( glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) GETPROCADDRESS("glDeleteObjectARB"));
	m_pExtensionMap["glDeleteVertexArrays"] = (void*)( glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) GETPROCADDRESS("glDeleteVertexArrays"));
	m_pExtensionMap["glEnableVertexAttribArrayARB"] = (void*)( glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) GETPROCADDRESS("glEnableVertexAttribArrayARB"));
	m_pExtensionMap["glGenBuffersARB"] = (void*)( glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) GETPROCADDRESS("glGenBuffersARB"));
	m_pExtensionMap["glGenVertexArrays"] = (void*)( glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) GETPROCADDRESS("glGenVertexArrays"));
	m_pExtensionMap["glGetProgramInfoLog"] = (void*)( glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) GETPROCADDRESS("glGetProgramInfoLog"));
	m_pExtensionMap["glGetProgramiv"] = (void*)( glGetProgramiv = (PFNGLGETPROGRAMIVPROC) GETPROCADDRESS("glGetProgramiv"));
	m_pExtensionMap["glGetShaderInfoLog"] = (void*)( glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) GETPROCADDRESS("glGetShaderInfoLog"));
	m_pExtensionMap["glGetShaderiv"] = (void*)( glGetShaderiv = (PFNGLGETSHADERIVPROC) GETPROCADDRESS("glGetShaderiv"));
	m_pExtensionMap["glGetUniformLocationARB"] = (void*)( glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) GETPROCADDRESS("glGetUniformLocationARB"));
	m_pExtensionMap["glLinkProgramARB"] = (void*)( glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) GETPROCADDRESS("glLinkProgramARB"));
	m_pExtensionMap["glShaderSourceARB"] = (void*)( glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) GETPROCADDRESS("glShaderSourceARB"));
	m_pExtensionMap["glUniform1fARB"] = (void*)( glUniform1fARB = (PFNGLUNIFORM1FARBPROC) GETPROCADDRESS("glUniform1fARB"));
	m_pExtensionMap["glUniform1iARB"] = (void*)( glUniform1iARB = (PFNGLUNIFORM1IARBPROC) GETPROCADDRESS("glUniform1iARB"));
	m_pExtensionMap["glUniform2fARB"] = (void*)( glUniform2fARB = (PFNGLUNIFORM2FARBPROC) GETPROCADDRESS("glUniform2fARB"));
	m_pExtensionMap["glUniform2iARB"] = (void*)( glUniform2iARB = (PFNGLUNIFORM2IARBPROC) GETPROCADDRESS("glUniform2iARB"));
	m_pExtensionMap["glUniform3fARB"] = (void*)( glUniform3fARB = (PFNGLUNIFORM3FARBPROC) GETPROCADDRESS("glUniform3fARB"));
	m_pExtensionMap["glUniform4fARB"] = (void*)( glUniform4fARB = (PFNGLUNIFORM4FARBPROC) GETPROCADDRESS("glUniform4fARB"));
	m_pExtensionMap["glUniformMatrix4fvARB"] = (void*)( glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) GETPROCADDRESS("glUniformMatrix4fvARB"));
	m_pExtensionMap["glUseProgram"] = (void*)( glUseProgram = (PFNGLUSEPROGRAMPROC)GETPROCADDRESS("glUseProgram"));
	m_pExtensionMap["glUseProgramObjectARB"] = (void*)( glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)GETPROCADDRESS("glUseProgramObjectARB"));
	m_pExtensionMap["glValidateProgram"] = (void*)( glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GETPROCADDRESS("glValidateProgram"));
	m_pExtensionMap["glVertexAttribPointerARB"] = (void*)( glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)GETPROCADDRESS("glVertexAttribPointerARB"));

	// Make sure all the extensions are ok.
	for(std::map<std::string, void*>::iterator it = m_pExtensionMap.begin(); it != m_pExtensionMap.end(); it++)
	{
		if(it->second == NULL)
		{
			m_pExtensionErrorCount ++;
			m_pExtensionError += it->first + "\n";
		}
	}

	// Return false if any of the extensions failed.
	if(m_pExtensionErrorCount > 0)
	{
		return false;
	}

	// Everything went fine.
	return (m_pLoaded = true);
}

bool GlExt::IsLoaded()
{
	return m_pLoaded;
}

std::string GlExt::GetError()
{
	return m_pExtensionError;
}

unsigned int GlExt::GetErrorCount()
{

	return m_pExtensionErrorCount;
}