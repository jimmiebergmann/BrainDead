#include <Windows.h>
#include <Main.hpp>
#include <DataTypes.hpp>
#include <Window/WindowsWindow.hpp>

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_pCmdLine, int p_CmdShow )
{
	BD::Game game;

	return game.Run(p_pCmdLine, p_CmdShow);

}
