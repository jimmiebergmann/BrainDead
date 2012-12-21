#ifndef __BRAINDEAD_SHADER_OGL_HPP__
#define __BRAINDEAD_SHADER_OGL_HPP__

#include <Shader/Shader.hpp>
#include <OpenGL/OpenGL.hpp>

namespace BD
{

	class ShaderOGL : public Shader
	{

	public:

		ShaderOGL(eShaderType p_ShaderType);
		virtual ~ShaderOGL();
		
		virtual BD_UINT32 Load(std::string & p_Validation);
		virtual BD_UINT32 Reload(); // Read and Load the last file.
		GLhandleARB GetShaderObject() const;
		static std::string ValidateShader(GLuint p_Shader);

	private:

		GLhandleARB m_ShaderObject;


	};

}

#endif