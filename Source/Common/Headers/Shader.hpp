#ifndef __BRAINDEAD_SHADER_HPP__
#define __BRAINDEAD_SHADER_HPP__

#include <DataTypes.hpp>
#include <string>

namespace BD
{


	class Shader
	{

	public:

		enum eShaderType
		{
			SHADERTYPE_NONE = 0,
			SHADERTYPE_VERTEX = 1,
			SHADERTYPE_FRAGMENT = 2
		};

		friend class ShaderProgram;

		virtual ~Shader() { }
		BD_UINT32 Read( const char * p_FileName );
		BD_INLINE void SetSource( std::string p_Source ) { m_ShaderSource = p_Source; };
		virtual BD_UINT32 Compile( std::string & p_Validation ) = 0;
		BD_BOOL IsCompiled( ) const;
		std::string GetSource( ) const;

	protected:

		BD_BOOL m_Compiled;
		eShaderType m_ShaderType;
		std::string m_ShaderSource;
		std::string m_FileName;

	};

}


#endif
