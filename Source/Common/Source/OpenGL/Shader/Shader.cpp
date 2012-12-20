#include <OpenGL/Shader/Shader.hpp>

namespace BD
{

	Shader::Shader() :
		m_Loaded(BD_FALSE)
	{
	}

	BD_UINT32 Shader::Read(const char * p_Filename)
	{

		return BD_ERROR;
	}

	BD_UINT32 Shader::Load()
	{
		return BD_ERROR;
	}

	void Shader::Unload()
	{
	}

	std::string Shader::Source()
	{
		return m_ShaderSource;
	}

}