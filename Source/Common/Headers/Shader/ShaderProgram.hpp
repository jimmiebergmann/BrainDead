#ifndef __BRAINDEAD_SHADER_PROGRAM_HPP__
#define __BRAINDEAD_SHADER_PROGRAM_HPP__

#include <DataTypes.hpp>
#include <string>

namespace BD
{

	class ShaderProgram;

	class ShaderProgram
	{

	public:

		ShaderProgram();
		BD_UINT32 Compile(Shader * p_VertexShader, Shader * p_FragmentShader);

	protected:

		BD_BOOL m_Compiled;

	};

}

#endif
