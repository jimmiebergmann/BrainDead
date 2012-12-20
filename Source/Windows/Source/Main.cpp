#include <Windows.h>
#include <Main.hpp>
#include <DataTypes.hpp>
#include <Window/WindowsWindow.hpp>

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_pCmdLine, int p_CmdShow )
{
	/*BD::Game game;

	return game.Run(0, 0);*/

	BD::WindowsWindow Win;
	Win.Create( 800, 600 );
	Sleep( 5000 );
	return BD_OK;

}
