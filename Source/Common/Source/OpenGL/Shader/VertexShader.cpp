#include <OpenGL/Shader/VertexShader.hpp>

namespace BD
{
	
	VertexShader::VertexShader() :
		Shader()
	{
		m_ShaderType = GL_VERTEX_SHADER_ARB;
	}

}