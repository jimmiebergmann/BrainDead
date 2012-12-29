#include <OGL/ShaderOGL.hpp>
#include <Debugger.hpp>
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

		// Did the shader compile without incident?
		GLint Compiled = 0;
		bglGetShaderiv( m_ShaderObject, GL_COMPILE_STATUS, &Compiled );

		if( !Compiled )
		{
			GLint LogLength = 0;
			bglGetShaderiv( m_ShaderObject, GL_INFO_LOG_LENGTH, &LogLength );

			if( LogLength > 1 )
			{
				char *pLog = new char[ LogLength ];
				bglGetShaderInfoLog( m_ShaderObject, LogLength, BD_NULL, pLog );
				bdTrace( BD_NULL, "[BD::ShaderOGL::Compile] <ERROR> "
					"Shader compiler error:\n%s\n", pLog );
				delete [ ] pLog;
			}

			m_Compiled = BD_FALSE;
			return BD_ERROR;
		}
		
		m_Compiled = BD_TRUE;
		return BD_OK;
	}

	GLuint ShaderOGL::GetShaderObject( ) const
	{
		return m_ShaderObject;
	}
}
