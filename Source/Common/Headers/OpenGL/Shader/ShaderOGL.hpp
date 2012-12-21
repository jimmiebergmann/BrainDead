#ifndef __BRAINDEAD_SHADER_OGL_HPP__
#define __BRAINDEAD_SHADER_OGL_HPP__

#include <Shader/Shader.hpp>
#include <OpenGL/OpenGL.hpp>

namespace BD
{

	class ShaderOGL : public Shader
	{

	public:

		~ShaderOGL();
		ShaderOGL(eShaderType p_ShaderType);
		virtual BD_UINT32 Load(std::string & p_Validation);
		virtual BD_UINT32 Reload(); // Read and Load the last file.
		virtual void Unload();

	private:

		std::string validateShader(GLuint p_Shader);

		GLhandleARB m_ShaderObject;


	};

}

#endif