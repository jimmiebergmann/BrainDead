#include <Vector2.hpp>
#include <Arithmetic.hpp>
#include <cmath>

namespace BD
{
	Vector2::Vector2( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y )
	{
		m_V[ 0 ] = p_X;
		m_V[ 1 ] = p_Y;
	}

	void Vector2::Zero( )
	{
		m_V[ 0 ] = m_V[ 1 ] = 0.0f;
	}

	BD_BOOL Vector2::IsZero( ) const
	{
		if( BD::IsZero( m_V[ 0 ] ) && BD::IsZero( m_V[ 1 ] ) )
		{
			return BD_TRUE;
		}

		return BD_FALSE;
	}

	void Vector2::Clean( )
	{
		if( BD::IsZero( m_V[ 0 ] ) )
		{
			m_V[ 0 ] = 0.0f;
		}
		if( BD::IsZero( m_V[ 1 ] ) )
		{
			m_V[ 1 ] = 0.0f;
		}
	}

	void Vector2::Normalise( )
	{
		BD_FLOAT32 Squared = ( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1] );
		
		if( BD::IsZero( Squared ) )
		{
			this->Zero( );
		}
		else
		{
			BD_FLOAT32 Factor = 1.0f / sqrt( Squared );
			m_V[ 0 ] *= Factor;
			m_V[ 1 ] *= Factor;
		}
	}

	BD_FLOAT32 Vector2::Magnitude( ) const
	{
		return ( sqrt( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] ) );
	}
	
	BD_FLOAT32 Vector2::MagnitudeSq( ) const
	{
		return ( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] );
	}
	
	BD_FLOAT32 Vector2::Distance( const Vector2 &p_Other ) const
	{
		BD_FLOAT32 X = m_V[ 0 ] - p_Other[ 0 ];
		BD_FLOAT32 Y = m_V[ 1 ] - p_Other[ 1 ];

		return 1.0f/sqrt( X*X + Y*Y );
	}

	BD_FLOAT32 Vector2::DistanceSq( const Vector2 &p_Other ) const
	{
		BD_FLOAT32 X = m_V[ 0 ] - p_Other[ 0 ];
		BD_FLOAT32 Y = m_V[ 1 ] - p_Other[ 1 ];

		return ( X*X + Y*Y );
	}

	BD_FLOAT32 Vector2::Dot( const Vector2 &p_Other ) const
	{
		return ( m_V[ 0 ]*p_Other[ 0 ] + m_V[ 1 ]*p_Other[ 1 ] );
	}

	BD_FLOAT32 Vector2::PerpendicularDot( const Vector2 &p_Other ) const
	{
		return ( ( m_V[ 0 ]*p_Other[ 1 ] )-( m_V[ 1 ]*p_Other[ 0 ] ) );
	}
	
	Vector2 &Vector2::operator=( const Vector2 &p_Other )
	{
		m_V[ 0 ] = p_Other[ 0 ];
		m_V[ 1 ] = p_Other[ 1 ];

		return *this;
	}

	BD_BOOL Vector2::operator==( const Vector2 &p_Other ) const
	{
		if( BD::Equal( m_V[ 0 ], p_Other[ 0 ] ) &&
			BD::Equal( m_V[ 1 ], p_Other[ 1 ] ) )
		{
			return BD_TRUE;
		}
		return BD_FALSE;
	}

	BD_BOOL Vector2::operator!=( const Vector2 &p_Other ) const
	{
		if( ! BD::Equal( m_V[ 0 ], p_Other[ 0 ] ) ||
			! BD::Equal( m_V[ 1 ], p_Other[ 1 ] ) )
		{
			return BD_TRUE;
		}
		return BD_FALSE;
	}

	Vector2 Vector2::operator+( const Vector2 &p_Other ) const
	{
		return Vector2( m_V[ 0 ]+p_Other[ 0 ], m_V[ 1 ]+p_Other[ 1 ] );
	}
	
	Vector2 Vector2::operator-( const Vector2 &p_Other ) const
	{
		return Vector2( m_V[ 0 ]-p_Other[ 0 ], m_V[ 1 ]-p_Other[ 1 ] );
	}

	Vector2 Vector2::operator*( const Vector2 &p_Other ) const
	{
		return Vector2( m_V[ 0 ]*p_Other[ 0 ], m_V[ 1 ]*p_Other[ 1 ] );
	}

	Vector2 Vector2::operator*( const BD_FLOAT32 p_Scalar ) const
	{
		return Vector2( m_V[ 0 ]*p_Scalar, m_V[ 1 ]*p_Scalar );
	}

	Vector2 Vector2::operator/( const BD_FLOAT32 p_Scalar ) const
	{
		// No divide-by-zero check!
		return Vector2( m_V[ 0 ]/p_Scalar, m_V[ 1 ]/p_Scalar );
	}

	Vector2 &Vector2::operator+=( const Vector2 &p_Other )
	{
		m_V[ 0 ] += p_Other[ 0 ];
		m_V[ 1 ] += p_Other[ 1 ];

		return *this;
	}

	Vector2 &Vector2::operator-=( const Vector2 &p_Other )
	{
		m_V[ 0 ] -= p_Other[ 0 ];
		m_V[ 1 ] -= p_Other[ 1 ];

		return *this;
	}

	Vector2 &Vector2::operator*=( const Vector2 &p_Other )
	{
		m_V[ 0 ] *= p_Other[ 0 ];
		m_V[ 1 ] *= p_Other[ 1 ];

		return *this;
	}

	Vector2 &Vector2::operator*=( const BD_FLOAT32 p_Scalar )
	{
		m_V[ 0 ] *= p_Scalar;
		m_V[ 1 ] *= p_Scalar;

		return *this;
	}

	Vector2 &Vector2::operator/=( const BD_FLOAT32 p_Scalar )
	{
		// No divide-by-zero check!
		m_V[ 0 ] /= p_Scalar;
		m_V[ 1 ] /= p_Scalar;

		return *this;
	}
}

