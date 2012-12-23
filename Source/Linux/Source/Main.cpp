#include <iostream>
#include <DataTypes.hpp>
#include <LinuxWindow.hpp>
#include <Debugger.hpp>
#include <System.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	BD::LinuxWindow Test;
	Test.Create( 800, 600 );

	sleep( 1 );
	bdTrace( "Test.log", "------------ TEST: %s -------------\n", "Linux" );
	std::cout << "BrainDead" << std::endl;
	return 0;
}
