#ifndef __BRAINDEAD_GAME_HPP__
#define __BRAINDEAD_GAME_HPP__

#include <DataTypes.hpp>
#include <windows.h>
#ifdef PLATFORM_WINDOWS
#include <Renderer/WindowsRendererOGL.hpp>
#endif

namespace BD
{
	class Game
	{

	public:
		
		~Game();
		Game();
		int Run(LPSTR p_pCmdLine, int p_CmdShow);
		
	private:

		BD_UINT32 Load();
		BD_UINT32 Unload();

#ifdef PLATFORM_WINDOWS
		WindowsWindow m_Window;
		WindowsRendererOGL m_Renderer;
#endif
		


	};

}

#endif