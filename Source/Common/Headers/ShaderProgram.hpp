#ifndef __BRAINDEAD_SHADER_PROGRAM_HPP__
#define __BRAINDEAD_SHADER_PROGRAM_HPP__

#include <DataTypes.hpp>
#include <Shader.hpp>
#include <Matrix4x4.hpp>
#include <string>

namespace BD
{

	class ShaderProgram
	{

	public:

		virtual ~ShaderProgram() { }
		virtual BD_UINT32 Load( ) = 0;
		virtual BD_UINT32 AttachShaders( Shader * p_Shader ) = 0;
		virtual BD_UINT32 Link( std::string & p_Validation ) = 0;
		virtual void Bind( ) = 0;
		virtual void Unbind( ) = 0;

		virtual void SetUniform1i( const char * p_Location, int p_A ) = 0;
		virtual void SetUniformMatrix4x4f( const char * p_Location, Matrix4x4 & p_Matrix ) = 0;
		virtual void SetAttributeLocation( const char * p_Location, BD_UINT32 p_Index ) = 0;

	protected:

		BD_BOOL m_Linked;

	};

}

#endif