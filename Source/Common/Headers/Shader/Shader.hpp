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

		Shader();
		BD_UINT32 Read(const char * p_Filename);
		BD_UINT32 Load();
		BD_UINT32 Reload(); // Read and Load the last file.
		void Unload();
		std::string Source();

	protected:

		BD_BOOL m_Loaded;
		std::string m_ShaderSource;
		std::string m_Filename;

	};

}


#endif
