#ifndef __RANDOM_TIMER_HPP__
#define __RANDOM_TIMER_HPP__

#include <DataTypes.hpp>
#include <string>

namespace BD
{
	void bdSeedRandom( BD_SINT32 p_Seed );
	void bdSeedRandom( std::string p_Seed );
	BD_SINT32 bdRandom( BD_SINT32 p_To );
	BD_SINT32 bdRandom( BD_SINT32 p_From, BD_SINT32 p_To );

}

#endif