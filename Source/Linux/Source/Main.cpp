#include <iostream>
#include <DataTypes.hpp>
#include <LinuxWindow.hpp>
#include <Debugger/DebugLog.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	BD::LinuxWindow Test;
	Test.Create( 800, 600 );

	sleep( 5 );
	bdTrace( BD_NULL, "------------ TEST: %s -------------\n", "Linux" );
	std::cout << "BrainDead" << std::endl;
	return 0;
}
