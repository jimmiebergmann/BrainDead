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

		virtual void SetUniformMatrix4x4( const char * p_Location, Matrix4x4 & p_Matrix );
		virtual void SetAttributeLocation( const char * p_Location, BD_UINT32 p_Index );

	private:

		GLhandleARB m_ProgramId;
		BD_UINT32 m_AttachedShaderCount;

	};

}

#endif
