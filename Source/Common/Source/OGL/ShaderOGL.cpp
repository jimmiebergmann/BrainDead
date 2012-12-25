#include <OGL/ShaderOGL.hpp>
#include <cstring>

namespace BD
{

	GLenum ShaderOGL::s_ShaderObjectTypes[3] = { 0, GL_VERTEX_SHADER_ARB, GL_FRAGMENT_SHADER_ARB };


	ShaderOGL::ShaderOGL( eShaderType p_ShaderType ) :
		m_ShaderObject(0)
	{
		m_Compiled = BD_FALSE;
		m_ShaderType = p_ShaderType;
		m_ShaderSource = "";
		m_FileName = "";
	}

	ShaderOGL::~ShaderOGL( )
	{
		if( m_ShaderObject != 0 )
		{
			bglDeleteShader( m_ShaderObject );
			m_ShaderObject = 0;
		}

		m_Compiled = BD_FALSE;
	}

	BD_UINT32 ShaderOGL::Compile( std::string & p_Validation )
	{
		// Make sure we have a shader source
		if( m_Compiled == BD_TRUE || m_ShaderSource.length() == 0 )
		{
			return BD_ERROR;
		}

		m_Compiled = false;

		// Create the shader object.
		// ===================================
		// Need fix, m_ShaderType is of wrong type.
		m_ShaderObject = bglCreateShader( s_ShaderObjectTypes[m_ShaderType] );

		const GLcharARB * pTextSource = m_ShaderSource.c_str( );

		// Might be a silly erorr check. But I'm doing it anyway.
		if(pTextSource == NULL)
		{
			return BD_ERROR;
		}

		// Compile the vertex shader using it's source
		bglShaderSource( m_ShaderObject, 1, &pTextSource, 0 );
		bglCompileShader( m_ShaderObject );
		
		// Validate the vertex shader
		p_Validation = ValidateShader( m_ShaderObject ); 

		m_Compiled = BD_TRUE;
		return BD_OK;
	}

	GLhandleARB ShaderOGL::GetShaderObject( ) const
	{
		return m_ShaderObject;
	}

	std::string ShaderOGL::ValidateShader( GLuint p_Shader )
	{
		const BD_UINT32 BUFFER_SIZE = 512;
		GLchar Buffer[BUFFER_SIZE];
		memset(Buffer, 0, BUFFER_SIZE);
		GLsizei Length = 0;

		bglGetShaderInfoLog( p_Shader, BUFFER_SIZE, &Length, Buffer ); // Ask OpenGL to give us the log associated with the shader
		
		std::string StringBuffer = std::string( Buffer );
		StringBuffer[ Length ] = '\0';

		return StringBuffer;
	}

}
