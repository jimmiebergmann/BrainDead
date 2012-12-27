#include <Shader.hpp>
#include <Debugger.hpp>
#include <fstream>

namespace BD
{
	BD_UINT32 Shader::Read(const char * p_FileName)
	{
		// Use fstream for reading files.
		std::ifstream File( p_FileName );
		if(File.is_open() == false)
		{
			bdTrace( BD_NULL, "[BD::Shader::Read] <ERROR> "
				"Failed to open file: %s", p_FileName );
			return BD_ERROR;
		}

		// Set the file name (if we want to reload the shader later)
		m_FileName = p_FileName;

		// Get the file size
		File.seekg( 0, std::ios::end );
		BD_UINT32 FileSize = File.tellg( );
		File.seekg( 0, std::ios::beg );

		// Clear the old source, and reserve new size
		m_ShaderSource.clear( );
		m_ShaderSource.reserve( FileSize );

		// Read all the file's lines
		std::string Line = "";

		while( !File.eof( ) )
		{
			std::getline( File, Line );
			m_ShaderSource += Line + "\n";
		}

		// Close the file, we are done.
		File.close( );

		return BD_OK;
	}

	BD_BOOL Shader::IsCompiled( ) const
	{
		return m_Compiled;
	}

	std::string Shader::GetSource() const
	{
		return m_ShaderSource;
	}

}

