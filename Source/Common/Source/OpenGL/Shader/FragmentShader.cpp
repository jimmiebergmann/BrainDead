#include <OpenGL/Shader/FragmentShader.hpp>

namespace BD
{
	FragmentShader::FragmentShader() :
		Shader()
	{
		m_ShaderType = GL_FRAGMENT_SHADER_ARB;
	}

}