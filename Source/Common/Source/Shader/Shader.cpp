#include <Shader/Shader.hpp>

namespace BD
{
	
	Shader::Shader(eShaderType p_ShaderType) :
		m_Loaded(BD_FALSE),
		m_ShaderType(p_ShaderType),
		m_ShaderSource(""),
		m_Filename("")
	{
	}

	BD_UINT32 Shader::Read(const char * p_Filename)
	{

		return BD_ERROR;
	}

	std::string Shader::GetSource() const
	{
		return m_ShaderSource;
	}

}