#ifndef __BRAINDEAD_SHADER_PROGRAM_OGL_HPP__
#define __BRAINDEAD_SHADER_PROGRAM_OGL_HPP__

#include <ShaderProgram.hpp>
#include <OGL/OpenGL.hpp>

namespace BD
{

	class ShaderProgramOGL : public ShaderProgram
	{

	public:

		ShaderProgramOGL( );
		virtual ~ShaderProgramOGL( );

		virtual BD_UINT32 Load( );
		virtual BD_UINT32 AttachShaders( Shader * p_Shader );
		virtual BD_UINT32 Link( std::string & p_Validation );
		virtual void Bind( );
		virtual void Unbind( );

		virtual void SetUniform1i( const char * p_Location, const BD_SINT32 );
		virtual void SetUniform1f( const char *, const BD_FLOAT32 );
		virtual void SetUniform2f( const char *, const BD_FLOAT32,
			const BD_FLOAT32 );
		virtual void SetUniform3f( const char *, const BD_FLOAT32,
			const BD_FLOAT32 , const BD_FLOAT32 );
		virtual void SetUniform4f( const char *, const BD_FLOAT32,
			const BD_FLOAT32 , const BD_FLOAT32 , const BD_FLOAT32 );
		virtual void SetUniformMatrix4x4f( const char * p_Location,
			Matrix4x4 & );
		virtual void SetAttributeLocation( const char * p_Location,
			BD_UINT32 p_Index );

	private:

		GLuint m_ProgramID;
		BD_UINT32 m_AttachedShaderCount;
	};

}

#endif
