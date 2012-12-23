#include <iostream>
#include <Debugger.hpp>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	BD::Game Game;

	return Game.Run( 0, BD_NULL );
}
