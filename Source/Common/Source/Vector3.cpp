#include <Arithmetic.hpp>
#include <Vector3.hpp>
#include <Matrix3x3.hpp>
#include <cmath>

namespace BD
{
	Vector3::Vector3( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y,
		const BD_FLOAT32 p_Z )
	{
		m_V[ 0 ] = p_X;
		m_V[ 1 ] = p_Y;
		m_V[ 2 ] = p_Z;
	}

	void Vector3::Zero( )
	{
		m_V[ 0 ] = m_V[ 1 ] = m_V[ 2 ] = 0.0f;
	}

	void Vector3::Clean( )
	{
		if( BD::IsZero( m_V[ 0 ] ) )
		{
			m_V[ 0 ] = 0.0f;
		}

		if( BD::IsZero( m_V[ 1 ] ) )
		{
			m_V[ 1 ] = 0.0f;
		}

		if( BD::IsZero( m_V[ 2 ] ) )
		{
			m_V[ 2 ] = 0.0f;
		}
	}

	void Vector3::Normalise( )
	{
		BD_FLOAT32 Squared = m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] +
			m_V[ 2 ]*m_V[ 2 ];

		if( BD::IsZero( Squared ) )
		{
			this->Zero( );
		}
		else
		{
			// Save on multiple divisions
			BD_FLOAT32 Factor = 1.0f / sqrt( Squared );
			m_V[ 0 ] *= Factor;
			m_V[ 1 ] *= Factor;
			m_V[ 2 ] *= Factor;
		}
	}

	BD_FLOAT32 Vector3::Magnitude( ) const
	{

		return ( sqrt( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] +
			m_V[ 2 ]*m_V[ 2 ] ) );
	}

	BD_FLOAT32 Vector3::MagnitudeSq( ) const
	{
		return ( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] + m_V[ 2 ]*m_V[ 2 ] );
	}

	BD_FLOAT32 Vector3::Distance( const Vector3 &p_Other ) const
	{
		BD_FLOAT32 X = m_V[ 0 ] - p_Other.m_V[ 0 ];
		BD_FLOAT32 Y = m_V[ 1 ] - p_Other.m_V[ 1 ];
		BD_FLOAT32 Z = m_V[ 2 ] - p_Other.m_V[ 2 ];

		return 1.0f/sqrt( X*X + Y*Y + Z*Z );
	}

	BD_FLOAT32 Vector3::DistanceSq( const Vector3 &p_Other ) const
	{
		BD_FLOAT32 X = m_V[ 0 ] - p_Other.m_V[ 0 ];
		BD_FLOAT32 Y = m_V[ 1 ] - p_Other.m_V[ 1 ];
		BD_FLOAT32 Z = m_V[ 2 ] - p_Other.m_V[ 2 ];

		return ( X*X + Y*Y + Z*Z );
	}

	BD_FLOAT32 Vector3::Dot( const Vector3 &p_Other ) const
	{
		return ( m_V[ 0 ]*p_Other.m_V[ 0 ] + m_V[ 1 ]*p_Other.m_V[ 1 ] +
			m_V[ 2 ]*p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::Cross( const Vector3 &p_Other ) const
	{
		return Vector3(
			( m_V[ 1 ]*p_Other.m_V[ 2 ] )-( m_V[ 2 ]*p_Other.m_V[ 1 ] ),
			( m_V[ 2 ]*p_Other.m_V[ 0 ] )-( m_V[ 0 ]*p_Other.m_V[ 2 ] ),
			( m_V[ 0 ]*p_Other.m_V[ 1 ] )-( m_V[ 1 ]*p_Other.m_V[ 0 ] ) );
	}

	BD_BOOL Vector3::operator==( const Vector3 &p_Other ) const
	{
		if( BD::Equal( m_V[ 0 ], p_Other.m_V[ 0 ] ) &&
			BD::Equal( m_V[ 1 ], p_Other.m_V[ 1 ] ) &&
			BD::Equal( m_V[ 2 ], p_Other.m_V[ 2 ] ) )
		{
			return BD_TRUE;
		}
		return BD_FALSE;
	}

	BD_BOOL Vector3::operator!=( const Vector3 &p_Other ) const
	{
		if( ( BD::Equal( m_V[ 0 ], p_Other.m_V[ 0 ] ) == BD_FALSE ) ||
			( BD::Equal( m_V[ 1 ], p_Other.m_V[ 1 ] ) == BD_FALSE ) ||
			( BD::Equal( m_V[ 2 ], p_Other.m_V[ 2 ] ) == BD_FALSE ) )
		{
			return BD_TRUE;
		}

		return BD_FALSE;
	}

	Vector3 Vector3::operator+( const Vector3 &p_Other ) const
	{
		return Vector3( m_V[ 0 ]+p_Other.m_V[ 0 ], m_V[ 1 ]+p_Other.m_V[ 1 ],
			m_V[ 2 ]+p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::operator-( const Vector3 &p_Other ) const
	{
		return Vector3( m_V[ 0 ]-p_Other.m_V[ 0 ], m_V[ 1 ]-p_Other.m_V[ 1 ],
			m_V[ 2 ]-p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::operator*( const Vector3 &p_Other ) const
	{
		return Vector3( m_V[ 0 ]*p_Other.m_V[ 0 ], m_V[ 1 ]*p_Other.m_V[ 1 ],
			m_V[ 2 ]*p_Other.m_V[ 2 ] );
	}

	Vector3 Vector3::operator*( const Matrix3x3 &p_Matrix ) const
	{
		BD_FLOAT32 X =	m_V[ 0 ]*p_Matrix[ 0 ] +
						m_V[ 1 ]*p_Matrix[ 1 ] +
						m_V[ 2 ]*p_Matrix[ 2 ];
		BD_FLOAT32 Y =	m_V[ 0 ]*p_Matrix[ 3 ] +
						m_V[ 1 ]*p_Matrix[ 4 ] +
						m_V[ 2 ]*p_Matrix[ 5 ];
		BD_FLOAT32 Z =	m_V[ 0 ]*p_Matrix[ 6 ] +
						m_V[ 1 ]*p_Matrix[ 7 ] +
						m_V[ 2 ]*p_Matrix[ 8 ];

		return Vector3( X, Y, Z );
	}

	Vector3 Vector3::operator*( const BD_FLOAT32 p_Scalar ) const
	{
		return Vector3( m_V[ 0 ]*p_Scalar, m_V[ 1 ]*p_Scalar,
			m_V[ 2 ]*p_Scalar );
	}

	Vector3 Vector3::operator/( const BD_FLOAT32 p_Scalar ) const
	{
		// Make sure the caller isn't dividing by zero!
		if( BD::IsZero( p_Scalar ) )
		{
			return Vector3( m_V[ 0 ], m_V[ 1 ], m_V[ 2 ] );
		}

		return Vector3( m_V[ 0 ]/p_Scalar, m_V[ 1 ]/p_Scalar,
			m_V[ 2 ]/p_Scalar );
	}

	Vector3 &Vector3::operator+=( const Vector3 &p_Other )
	{
		m_V[ 0 ] += p_Other.m_V[ 0 ];
		m_V[ 1 ] += p_Other.m_V[ 1 ];
		m_V[ 2 ] += p_Other.m_V[ 2 ];

		return *this;
	}

	Vector3 &Vector3::operator-=( const Vector3 &p_Other )
	{
		m_V[ 0 ] -= p_Other.m_V[ 0 ];
		m_V[ 1 ] -= p_Other.m_V[ 1 ];
		m_V[ 2 ] -= p_Other.m_V[ 2 ];

		return *this;
	}

	Vector3 &Vector3::operator*=( const Vector3 &p_Other )
	{
		m_V[ 0 ] *= p_Other.m_V[ 0 ];
		m_V[ 1 ] *= p_Other.m_V[ 1 ];
		m_V[ 2 ] *= p_Other.m_V[ 2 ];

		return *this;
	}

	Vector3 &Vector3::operator*=( const BD_FLOAT32 p_Scalar )
	{
		m_V[ 0 ] *= p_Scalar;
		m_V[ 1 ] *= p_Scalar;
		m_V[ 2 ] *= p_Scalar;

		return *this;
	}

	Vector3 &Vector3::operator/=( const BD_FLOAT32 p_Scalar )
	{
		if( BD::IsZero( p_Scalar ) )
		{
			return *this;
		}

		m_V[ 0 ] /= p_Scalar;
		m_V[ 1 ] /= p_Scalar;
		m_V[ 2 ] /= p_Scalar;

		return *this;
	}
}
