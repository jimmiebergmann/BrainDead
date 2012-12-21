#ifndef __BRAINDEAD_GAME_HPP__
#define __BRAINDEAD_GAME_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>

#ifdef PLATFORM_WINDOWS
#include <WindowsRendererOGL.hpp>
#elif PLATFORM_LINUX
#include <LinuxRendererOGL.hpp>
#else
#error No platform pre-processor directive specified
#endif

#include <OGL/ShaderOGL.hpp>
#include <OGL/ShaderProgramOGL.hpp>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace BD
{
	class Game
	{

	public:
		
		~Game();
		Game();
		int Run(int argc, char ** argv);
		
	private:

		BD_UINT32 Load();
		BD_UINT32 Unload();

		BD_BOOL m_Loaded;
		BD_BOOL m_Running;

		Window * m_pWindow;
		Renderer * m_pRenderer;

		// Test shaders
		Shader * m_pVertexShader;
		Shader * m_pFragmentShader;
		ShaderProgram * m_pShaderProgram;

	};

}

#endif
