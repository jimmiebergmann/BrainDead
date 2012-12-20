#include <Windows.h>
#include <Main.hpp>
#include <DataTypes.hpp>

#include <Debugger/DebugLog.hpp>

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_pCmdLine, int p_CmdShow )
{
	BD::Game game;

	bdTrace( BD_NULL, "\n------------------TEST: %s-------------------\n",
		"Windows" );

	return game.Run(0, BD_NULL);
}
