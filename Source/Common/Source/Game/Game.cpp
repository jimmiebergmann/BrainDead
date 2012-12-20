#include <Game/Game.hpp>
#include <iostream>

namespace BD
{
	Game::~Game()
	{
	}

	Game::Game() :
		m_Loaded(BD_FALSE),
		m_Running(BD_FALSE)
	{
	}

	int Game::Run(int argc, char ** argv)
	{
		m_Running = false;

		// Load the game
		if(Load() == BD_OK)
		{
			m_Running = true;
		}

		
		// Main loop
		while(m_Running)
		{
			if(m_Window.DoEvents() == BD_ERROR)
			{
				break;
			}

			m_Renderer.StartScene();

			// Draw things here

			m_Renderer.EndScene();

		}
		

		// Unload the game
		if(Unload() != BD_OK)
		{
#ifdef PLATFORM_WINDOWS
			::MessageBox(NULL, L"Failed to unload BrainDead", L"BrainDead Erorr.", MB_OK | MB_ICONEXCLAMATION);
#elif PLATFORM_LINUX
			std::cout << "Error: Failed to unload BrainDead" << std::endl;
#endif
		}
		
		return 0;
	}

	BD_UINT32 Game::Load()
	{
		m_Loaded = false;

		// Create the window
		if(m_Window.Create( 800, 600 ) != BD_OK)
		{
			return BD_ERROR;
		}

		// Create the renderer by using the window we just created
		if(m_Renderer.Create(m_Window) != BD_OK)
		{
			return BD_ERROR;
		}

		m_Loaded = true;
		return BD_OK;
	}

	BD_UINT32 Game::Unload()
	{
		//m_Renderer.Destroy();
		//m_Window.Destory();
		
		return BD_OK;
	}


}