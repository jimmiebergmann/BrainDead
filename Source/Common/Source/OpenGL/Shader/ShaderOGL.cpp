#include <OpenGL/Shader/ShaderOGL.hpp>

namespace BD
{

	ShaderOGL::~ShaderOGL()
	{

	}

	ShaderOGL::ShaderOGL(eShaderType p_ShaderType) :
		Shader(p_ShaderType)
	{
	}

	BD_UINT32 ShaderOGL::Load()
	{
		return BD_ERROR;
	}

	BD_UINT32 ShaderOGL::Reload()
	{
		return BD_ERROR;
	}

	void ShaderOGL::Unload()
	{
	}


	std::string ShaderOGL::validateShader(GLuint p_Shader, const char * p_file)
	{
		const BD_UINT32 BUFFER_SIZE = 512;
		GLchar Buffer[BUFFER_SIZE];
		memset(Buffer, 0, BUFFER_SIZE);
		GLsizei Length = 0;

		glGetShaderInfoLog(p_Shader, BUFFER_SIZE, &Length, Buffer); // Ask OpenGL to give us the log associated with the shader
		
		std::string StringBuffer = std::string(Buffer);
		StringBuffer[Length] = '\0';

	
		return StringBuffer;
		//if (Length > 0) // If we have any information to display
		//	std::cout << "Shader " << shader << " (" << (file?file:"") << ")(" << length << ") compile error: " << buffer << std::endl; // Output the information
	}


}