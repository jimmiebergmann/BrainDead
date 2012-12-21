#include <OGL/ShaderProgramOGL.hpp>
#include <OGL/ShaderOGL.hpp>

namespace BD
{

	ShaderProgramOGL::ShaderProgramOGL() :
		m_ProgramId(0)
	{
		m_Compiled = BD_FALSE;
	}

	ShaderProgramOGL::~ShaderProgramOGL()
	{
	}

	BD_UINT32 ShaderProgramOGL::Compile(Shader * p_VertexShader, Shader * p_FragmentShader, std::string & p_Validation)
	{
		// Create the shader program
		if((m_ProgramId = bglCreateProgram()) == 0)
		{
			return BD_ERROR;
		}

		ShaderOGL * pVertexShaderOGL = (ShaderOGL *)p_VertexShader;
		ShaderOGL * pFragmentShaderOGL = (ShaderOGL *)p_FragmentShader;

		// Attach the shaders
		bglAttachShader(m_ProgramId, pVertexShaderOGL->GetShaderObject()); // Attach a vertex shader to the program
		bglAttachShader(m_ProgramId, pFragmentShaderOGL->GetShaderObject()); // Attach the fragment shader to the program

		// Link the program
		bglLinkProgram(m_ProgramId);

		p_Validation = ShaderOGL::ValidateShader(m_ProgramId);

		m_Compiled = BD_TRUE;
		return BD_OK;
	}

}