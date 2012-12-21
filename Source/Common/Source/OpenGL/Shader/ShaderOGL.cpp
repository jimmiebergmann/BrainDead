#include <OpenGL/Shader/ShaderOGL.hpp>

namespace BD
{

	ShaderOGL::~ShaderOGL()
	{

	}

	ShaderOGL::ShaderOGL(eShaderType p_ShaderType) :
		Shader(p_ShaderType),
		m_ShaderObject(0)
	{
	}

	BD_UINT32 ShaderOGL::Load(std::string & p_Validation)
	{
		// Make sure we have a shader source
		if(m_ShaderSource.length() == 0)
		{
			return BD_ERROR;
		}

		m_Loaded = false;

		// Create the shader object.
		m_ShaderObject = glCreateShaderObjectARB(m_ShaderType);

		const GLcharARB * pTextSource = m_ShaderSource.c_str();

		// Might be a silly erorr check. But I'm doing it anyway.
		if(pTextSource == NULL)
		{
			return BD_ERROR;
		}

		// Compile the vertex shader using it's source
		glShaderSourceARB(m_ShaderObject, 1, &pTextSource, 0);
		glCompileShaderARB(m_ShaderObject);
		
		// Validate the vertex shader
		p_Validation = validateShader(m_ShaderObject); 

		m_Loaded = BD_TRUE;
		return BD_ERROR;
	}

	BD_UINT32 ShaderOGL::Reload()
	{
		// Make sure we have a file path to the shader(This is set by reading a file)
		if(m_Filename == "")
		{
			return BD_ERROR;
		}

		return BD_ERROR;
	}

	void ShaderOGL::Unload()
	{
		m_Loaded = BD_FALSE;

		if(m_ShaderObject != 0)
		{
			glDeleteObjectARB(m_ShaderObject);
			m_ShaderObject = 0;
		}
	}

	std::string ShaderOGL::validateShader(GLuint p_Shader)
	{
		const BD_UINT32 BUFFER_SIZE = 512;
		GLchar Buffer[BUFFER_SIZE];
		memset(Buffer, 0, BUFFER_SIZE);
		GLsizei Length = 0;

		glGetShaderInfoLog(p_Shader, BUFFER_SIZE, &Length, Buffer); // Ask OpenGL to give us the log associated with the shader
		
		std::string StringBuffer = std::string(Buffer);
		StringBuffer[Length] = '\0';

		return StringBuffer;
	}

}