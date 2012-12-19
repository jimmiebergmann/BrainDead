#include "Main.hpp"

int __stdcall WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_pCmdLine, int p_CmdShow )
{
	::MessageBox( NULL, L"BrainDead", L"BrainBox", MB_OK );

	return 0;
}
