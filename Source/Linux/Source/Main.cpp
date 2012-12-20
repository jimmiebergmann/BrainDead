#include <iostream>
#include <DataTypes.hpp>
#include <LinuxWindow.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	BD::LinuxWindow Test;
	Test.Initialise( 800, 600, BD_FALSE );

	sleep( 10 );
	std::cout << "BrainDead" << std::endl;
	return 0;
}
