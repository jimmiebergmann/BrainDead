#ifndef __BRAINDEAD_SHADER_PROGRAM_HPP__
#define __BRAINDEAD_SHADER_PROGRAM_HPP__

#include <DataTypes.hpp>
#include <Shader/Shader.hpp>
#include <string>

namespace BD
{

	class ShaderProgram
	{

	public:

		ShaderProgram() : m_Compiled(BD_FALSE) { };
		virtual BD_UINT32 Compile(Shader * p_VertexShader, Shader * p_FragmentShader) = 0;

	protected:

		BD_BOOL m_Compiled;

	};

}

#endif
