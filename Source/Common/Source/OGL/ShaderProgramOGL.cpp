#include <OGL/ShaderProgramOGL.hpp>
#include <OGL/ShaderOGL.hpp>
#include <Debugger.hpp>

namespace BD
{

	ShaderProgramOGL::ShaderProgramOGL() :
		m_ProgramID(0),
		m_AttachedShaderCount(0)
	{
		m_Linked = BD_FALSE;
	}

	ShaderProgramOGL::~ShaderProgramOGL()
	{
		m_AttachedShaderCount = 0;
	}

	BD_UINT32 ShaderProgramOGL::Load( )
	{
		if(  (m_ProgramID = bglCreateProgram()) == 0 )
		{
			bdTrace( BD_NULL, "[BD::ShaderProgramOGL::Load] <ERROR> "
				"Failed to create a shader program\n" );
			return BD_ERROR;
		}

		return BD_OK;
	}

	BD_UINT32 ShaderProgramOGL::AttachShaders( Shader *p_pShader )
	{
		// Make sure the shader program is loaded before we attach any shaders.
		if( m_ProgramID == 0 )
		{
			bdTrace( BD_NULL, "[BD::ShaderProgramOGL::AttachShaders] <ERROR> "
				"Shader program was not initialised\n" );
			return BD_ERROR;
		}

		ShaderOGL *pShaderOGL = dynamic_cast< ShaderOGL * >( p_pShader );

		// Attach the shader
		bglAttachShader( m_ProgramID, pShaderOGL->GetShaderObject( ) );

		m_AttachedShaderCount++;

		return BD_OK;
	}

	BD_UINT32 ShaderProgramOGL::Link( std::string & p_Validation )
	{
		// Make sure we have attached any shaders at all to the shader program
		if( m_AttachedShaderCount < 2 )
		{
			bdTrace( BD_NULL, "[BD::ShaderProgramOGL::Link] <ERROR> "
				"Not enough shader objects are attached: %ld reported\n",
				m_AttachedShaderCount );
			return BD_ERROR;
		}

		// Link the program
		bglLinkProgram( m_ProgramID );

		// Make sure the shaders linked correctly
		GLint LinkStatus = GL_FALSE;
		bglGetProgramiv( m_ProgramID, GL_LINK_STATUS, &LinkStatus );
		if( LinkStatus == GL_FALSE )
		{
			bdTrace( BD_NULL, "[BD::ShaderProgramOGL::Link] <ERROR> "
				"Failed to link program:\n" );

			GLsizei Length = 0;
			GLchar *pLog;

			bglGetProgramiv( m_ProgramID, GL_INFO_LOG_LENGTH, &Length );
			pLog = new GLchar[ Length ];

			bglGetProgramInfoLog( m_ProgramID, Length, &Length, pLog );

			bdTrace( BD_NULL, "\t%s\n", pLog );
			bdAssert( BD_FALSE );

			delete [ ] pLog;

			return BD_ERROR;
		}

		m_Linked = BD_TRUE;
		return BD_OK;
	}

	void ShaderProgramOGL::Bind()
	{
		bglUseProgram(m_ProgramID);
	}

	void ShaderProgramOGL::Unbind()
	{
		bglUseProgram(0);
	}


	void ShaderProgramOGL::SetUniform1i( const char * p_Location,  const BD_SINT32 p_A )
	{
		int UniformLocation = bglGetUniformLocation( m_ProgramID, p_Location );
		bglUniform1i( UniformLocation, (GLint)p_A );
	}

	void  ShaderProgramOGL::SetUniform1f( const char * p_Location, const BD_FLOAT32 p_A )
	{
		int UniformLocation = bglGetUniformLocation( m_ProgramID, p_Location );
		bglUniform1f( UniformLocation, (GLfloat)p_A );
	}

	void  ShaderProgramOGL::SetUniform2f( const char * p_Location, const BD_FLOAT32 p_A, const BD_FLOAT32 p_B )
	{
		int UniformLocation = bglGetUniformLocation( m_ProgramID, p_Location );
		bglUniform2f( UniformLocation, (GLfloat)p_A, (GLfloat)p_B );
	}

	void  ShaderProgramOGL::SetUniform3f( const char * p_Location, const BD_FLOAT32 p_A, const BD_FLOAT32 p_B, const BD_FLOAT32 p_C )
	{
		int UniformLocation = bglGetUniformLocation( m_ProgramID, p_Location );
		bglUniform3f( UniformLocation, (GLfloat)p_A, (GLfloat)p_B, (GLfloat)p_C );
	}

	void  ShaderProgramOGL::SetUniform4f( const char * p_Location, const BD_FLOAT32 p_A, const BD_FLOAT32 p_B, const BD_FLOAT32 p_C, const BD_FLOAT32 p_D )
	{
		int UniformLocation = bglGetUniformLocation( m_ProgramID, p_Location );
		bglUniform4f( UniformLocation, (GLfloat)p_A, (GLfloat)p_B, (GLfloat)p_C, (GLfloat)p_D );
	}

	void ShaderProgramOGL::SetUniformMatrix4x4f( const char * p_Location, Matrix4x4 & p_Matrix )
	{

		int UniformLocation = bglGetUniformLocation( m_ProgramID, p_Location );

		BD_FLOAT32 MatrixData[16];
		p_Matrix.GetMatrix( MatrixData );
		bglUniformMatrix4fv( UniformLocation, 1, GL_FALSE, (GLfloat*)MatrixData );

	}
	void ShaderProgramOGL::SetAttributeLocation( const char * p_Location, BD_UINT32 p_Index )
	{

		bglBindAttribLocation(m_ProgramID, (GLuint)p_Index, p_Location);
	}


}
