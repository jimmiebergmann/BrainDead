#include <windows.h>
#include <Main.hpp>
#include <DataTypes.hpp>

#include <Debugger.hpp>

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_pCmdLine, int p_CmdShow )
{
	BD::Game game;

	return game.Run( 0, BD_NULL );
}
