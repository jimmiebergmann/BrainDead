#ifndef __BRAINDEAD_SHADER_HPP__
#define __BRAINDEAD_SHADER_HPP__

#include <DataTypes.hpp>
#include <string>

namespace BD
{

	class ShaderProgram;

	class Shader
	{

	public:

		enum eShaderType
		{
			SHADERTYPE_NONE = 0,
			SHADERTYPE_VERTEX = 1,
			SHADERTYPE_FRAGMENT = 2
		};

		Shader(eShaderType p_ShaderType);
		BD_UINT32 Read(const char * p_Filename);
		virtual BD_UINT32 Load(std::string & p_Validation) = 0;
		virtual BD_UINT32 Reload() = 0; // Read and Load the last file.
		virtual void Unload() = 0;
		std::string GetSource() const;

	protected:

		BD_BOOL m_Loaded;
		eShaderType m_ShaderType;
		std::string m_ShaderSource;
		std::string m_Filename;

	};

}


#endif
