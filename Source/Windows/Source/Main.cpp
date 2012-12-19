#include "Main.hpp"

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_pCmdLine, int p_CmdShow )
{
	Game game;

	return game.Run(0, 0);
}
