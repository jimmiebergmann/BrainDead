#include <OGL/ShaderProgramOGL.hpp>
#include <OGL/ShaderOGL.hpp>

namespace BD
{

	ShaderProgramOGL::ShaderProgramOGL() :
		m_ProgramId(0),
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
		if(  (m_ProgramId = bglCreateProgram()) == 0 )
		{
			return BD_ERROR;
		}

		return BD_OK;
	}

	BD_UINT32 ShaderProgramOGL::AttachShaders( Shader * p_Shader )
	{
		// Make sure the shader program is loaded before we attach any shaders.
		if( m_ProgramId == 0 )
		{
			return BD_ERROR;
		}


		ShaderOGL * pShaderOGL = (ShaderOGL *)p_Shader;

		// Attach the shader
		bglAttachShader(m_ProgramId, pShaderOGL->GetShaderObject());

		m_AttachedShaderCount++;

		return BD_OK;
	}

	BD_UINT32 ShaderProgramOGL::Link( std::string & p_Validation )
	{
		// Make sure we have attached any shaders at all to the shader program
		if( m_Linked == BD_TRUE || m_AttachedShaderCount < 2 )
		{
			return BD_ERROR;
		}

		// Link the program
		bglLinkProgram(m_ProgramId);

		// Get the validation string (Useful for debugging shaders)
		p_Validation = ShaderOGL::ValidateShader( m_ProgramId );

		// Make sure the shaders linked correctly
		GLint LinkStatus = GL_FALSE;
		bglGetProgramiv( m_ProgramId,	GL_LINK_STATUS, &LinkStatus );
		if( LinkStatus == GL_FALSE )
		{
			return BD_ERROR;
		}

		m_Linked = BD_TRUE;
		return BD_OK;
	}

	void ShaderProgramOGL::Bind()
	{
		bglUseProgram(m_ProgramId);
	}

	void ShaderProgramOGL::Unbind()
	{
		bglUseProgram(0);
	}



	void ShaderProgramOGL::SetUniformMatrix4x4( const char * p_Location, Matrix4x4 & p_Matrix )
	{

		int UniformLocation = bglGetUniformLocation( m_ProgramId, p_Location );

		BD_FLOAT32 MatrixData[16];
		p_Matrix.GetMatrix( MatrixData );
		bglUniformMatrix4fv( UniformLocation, 1, GL_FALSE, (GLfloat*)MatrixData );

	}
	void ShaderProgramOGL::SetAttributeLocation( const char * p_Location, BD_UINT32 p_Index )
	{

		bglBindAttribLocation(m_ProgramId, (GLuint)p_Index, p_Location);
	}


}