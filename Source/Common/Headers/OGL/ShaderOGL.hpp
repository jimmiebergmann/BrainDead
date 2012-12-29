#ifndef __BRAINDEAD_SHADER_OGL_HPP__
#define __BRAINDEAD_SHADER_OGL_HPP__

#include <Shader.hpp>
#include <OGL/OpenGL.hpp>

namespace BD
{
	class ShaderOGL : public Shader
	{
	public:

		ShaderOGL(eShaderType p_ShaderType);
		virtual ~ShaderOGL();
		
		virtual BD_UINT32 Compile(std::string & p_Validation);
		GLuint GetShaderObject() const;

	private:

		static GLenum s_ShaderObjectTypes[ 3 ];

		GLuint m_ShaderObject;

	};

}

#endif
