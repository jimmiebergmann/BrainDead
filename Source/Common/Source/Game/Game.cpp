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

		}

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
		return BD_OK;
	}

	BD_UINT32 Game::Unload()
	{
		
		return BD_OK;
	}


}