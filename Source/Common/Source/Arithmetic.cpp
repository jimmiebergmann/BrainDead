#include <Arithmetic.hpp>
#include <cmath>

namespace BD
{
	BD_BOOL IsZero( const BD_FLOAT32 p_Value )
	{
		return ( fabs( p_Value ) < BD_EPSILON );
	}

	BD_BOOL Equal( const BD_FLOAT32 p_Value1, const BD_FLOAT32 p_Value2 )
	{
		return( IsZero( p_Value1 - p_Value2 ) );
	}
}
