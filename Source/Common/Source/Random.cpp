#include <Random.hpp>

static BD_SINT32 s_RandomSeed = 0;

namespace BD
{
	void bdSeedRandom( BD_SINT32 p_Seed )
	{
		s_RandomSeed = p_Seed;
	}

	void bdSeedRandom( std::string p_Seed )
	{
		s_RandomSeed = 0;

		for( BD_MEMSIZE i = 0; i < p_Seed.size(); i++ )
		{
			s_RandomSeed += p_Seed[i] * ( i + 1 );
		}
	}

	BD_SINT32 bdRandom( BD_SINT32 p_To )
	{
		s_RandomSeed = ( 214013 * s_RandomSeed + 2531011 );
		return ( ( s_RandomSeed >> 16 ) & 0x00FFFF ) % ( p_To +1 );
	}

	BD_SINT32 bdRandom( BD_SINT32 p_From, BD_SINT32 p_To )
	{
		s_RandomSeed = ( 214013 * s_RandomSeed + 2531011 );
		return p_From + ( ( s_RandomSeed >> 16 ) & 0x00FFFF ) % ( p_To - ( p_From - 1 ) );
	}

}
