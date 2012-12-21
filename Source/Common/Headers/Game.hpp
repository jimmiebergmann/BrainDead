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
		int Run(int argc, char ** argv);
		
	private:

		BD_UINT32 Load();
		BD_UINT32 Unload();

		BD_BOOL m_Loaded;
		BD_BOOL m_Running;

		Window * m_pWindow;
		Renderer * m_pRenderer;


	};

}

#endif