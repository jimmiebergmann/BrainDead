#ifndef __BRAINDEAD_SHADER_HPP__
#define __BRAINDEAD_SHADER_HPP__

#include <DataTypes.hpp>
#include <OpenGL/OpenGL.hpp>
#include <string>

namespace BD
{

	class ShaderProgram;

	class Shader
	{

	public:

		friend class ShaderProgram;

		Shader();
		BD_UINT32 Read(const char * p_Filename);
		BD_UINT32 Load();
		void Unload();
		std::string Source();

	protected:

		BD_BOOL m_Loaded;
		GLhandleARB m_ShaderObject;
		std::string m_ShaderSource;
		std::string m_Filename;
		GLenum m_ShaderType;

	};

}

#endif
