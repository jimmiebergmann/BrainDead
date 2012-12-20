#include <Game/Game.hpp>

namespace BD
{
	Game::~Game()
	{
	}

	Game::Game()
	{
	}

	int Game::Run(LPSTR p_pCmdLine, int p_CmdShow)
	{
		// Load the game
		if(Load() != BD_OK)
		{
			return 0;
		}

		Sleep(500);

		/*
		// Main loop
		
		while(running)
		{

			m_Renderer.StartScene();

			// Draw things here

			m_Renderer.EndScene();

		}
		*/

		// Unload the game
		if(Unload() != BD_OK)
		{

		}
		
		return 0;
	}

	BD_UINT32 Game::Load()
	{
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

		return BD_OK;
	}

	BD_UINT32 Game::Unload()
	{
		
		return BD_OK;
	}


}