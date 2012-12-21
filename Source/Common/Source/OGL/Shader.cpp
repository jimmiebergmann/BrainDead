#include <OGL/Shader.hpp>
#include <fstream>

namespace BD
{
/*
	Shader::Shader(eShaderType p_ShaderType) :
		m_Loaded(BD_FALSE),
		m_ShaderType(p_ShaderType),
		m_ShaderSource(""),
		m_Filename("")
	{
	}
*/
	BD_UINT32 Shader::Read(const char * p_Filename)
	{
		// Use fstream for reading files.
		std::ifstream File(p_Filename);
		if(File.is_open() == false)
		{
			return BD_ERROR;
		}

		// Set the file name (if we want to reload the shader later)
		m_Filename = p_Filename;

		// Get the file size
		File.seekg (0, std::ios::end);
		BD_UINT32 FileSize = File.tellg();
		File.seekg (0, std::ios::beg);

		// Clear the old source, and reserve new size
		m_ShaderSource.clear();
		m_ShaderSource.reserve(FileSize);

		// Read all the file's lines
		std::string Line = "";

		while(!File.eof())
		{
			std::getline(File, Line);
			m_ShaderSource += Line + "\n";
		}

		// Close the file, we are done.
		File.close();

		return BD_OK;
	}

	std::string Shader::GetSource() const
	{
		return m_ShaderSource;
	}

}