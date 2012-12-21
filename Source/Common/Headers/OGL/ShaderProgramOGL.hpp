#ifndef __BRAINDEAD_SHADER_PROGRAM_OGL_HPP__
#define __BRAINDEAD_SHADER_PROGRAM_OGL_HPP__

#include <Shader/ShaderProgram.hpp>
#include <OpenGL/OpenGL.hpp>

namespace BD
{

	class ShaderProgramOGL : public ShaderProgram
	{

	public:

		ShaderProgramOGL();
		virtual ~ShaderProgramOGL();
		virtual BD_UINT32 Compile(Shader * p_VertexShader, Shader * p_FragmentShader, std::string & p_Validation);

	private:

		GLhandleARB m_ProgramId;



	};

}

#endif
