#include <Vector4.hpp>
#include <cmath>
#include <Arithmetic.hpp>

namespace BD
{
	Vector4::Vector4( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y,
		const BD_FLOAT32 p_Z, const BD_FLOAT32 p_W )
	{
		m_V[ 0 ] = p_X;
		m_V[ 1 ] = p_Y;
		m_V[ 2 ] = p_Z;
		m_V[ 3 ] = p_W;
	}

	void Vector4::Normalise( )
	{
		BD_FLOAT32 MagnitudeSq = ( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] +
			m_V[ 2 ]*m_V[ 2 ] + m_V[ 3 ]*m_V[ 3 ] );

		if( BD::IsZero( MagnitudeSq ) )
		{
			this->Zero( );
		}
		else
		{
			BD_FLOAT32 Factor = 1.0f / sqrtf( MagnitudeSq );

			m_V[ 0 ] *= Factor;
			m_V[ 1 ] *= Factor;
			m_V[ 2 ] *= Factor;
			m_V[ 3 ] *= Factor;
		}
	}

	BD_FLOAT32 Vector4::Magnitude( ) const
	{
		return sqrtf( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] + m_V[ 2 ]*m_V[ 2 ] +
			m_V[ 3 ]*m_V[ 3 ] );
	}

	BD_FLOAT32 Vector4::MagnitudeSq( ) const
	{
		return ( m_V[ 0 ]*m_V[ 0 ] + m_V[ 1 ]*m_V[ 1 ] + m_V[ 2 ]*m_V[ 2 ] +
			m_V[ 3 ]*m_V[ 3 ] );
	}

	BD_FLOAT32 Vector4::Dot( const Vector4 &p_Other ) const
	{
		return ( m_V[ 0 ]*p_Other.m_V[ 0 ] + m_V[ 1 ]*p_Other.m_V[ 1 ],
			m_V[ 2 ]*p_Other.m_V[ 2 ] + m_V[ 3 ]*p_Other.m_V[ 3 ] );
	}

	void Vector4::Set( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y,
		const BD_FLOAT32 p_Z, const BD_FLOAT32 p_W )
	{
		m_V[ 0 ] = p_X;
		m_V[ 1 ] = p_Y;
		m_V[ 2 ] = p_Z;
		m_V[ 3 ] = p_W;
	}

	BD_BOOL Vector4::IsZero( ) const
	{
		if( BD::IsZero( m_V[ 0 ] ) &&
			BD::IsZero( m_V[ 1 ] ) &&
			BD::IsZero( m_V[ 2 ] ) &&
			BD::IsZero( m_V[ 3 ] ) )
		{
			return BD_TRUE;
		}

		return BD_FALSE;
	}

	void Vector4::Zero( )
	{
		m_V[ 0 ] = m_V[ 1 ] = m_V[ 2 ] = m_V[ 3 ] = 0.0f;
	}

	void Vector4::Clean( )
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

		if( BD::IsZero( m_V[ 3 ] ) )
		{
			m_V[ 3 ] = 0.0f;
		}
	}

	BD_BOOL Vector4::operator==( const Vector4 &p_Other ) const
	{
		if( BD::Equal( m_V[ 0 ], p_Other.m_V[ 0 ] ) &&
			BD::Equal( m_V[ 1 ], p_Other.m_V[ 1 ] ) &&
			BD::Equal( m_V[ 2 ], p_Other.m_V[ 2 ] ) &&
			BD::Equal( m_V[ 3 ], p_Other.m_V[ 3 ] ) )
		{
			return BD_TRUE;
		}

		return BD_FALSE;
	}

	BD_BOOL Vector4::operator!=( const Vector4 &p_Other ) const
	{
		if( BD::Equal( m_V[ 0 ], p_Other.m_V[ 0 ] ) &&
			BD::Equal( m_V[ 1 ], p_Other.m_V[ 1 ] ) &&
			BD::Equal( m_V[ 2 ], p_Other.m_V[ 2 ] ) &&
			BD::Equal( m_V[ 3 ], p_Other.m_V[ 3 ] ) )
		{
			return BD_FALSE;
		}

		return BD_TRUE;
	}

	Vector4 Vector4::operator-( ) const
	{
		return Vector4( -m_V[ 0 ], -m_V[ 1 ], -m_V[ 2 ], -m_V[ 3 ] );
	}

	Vector4 Vector4::operator+( const Vector4 &p_Other ) const
	{
		return Vector4( m_V[ 0 ]+p_Other.m_V[ 0 ], m_V[ 1 ]+p_Other.m_V[ 1 ],
			m_V[ 2 ]+p_Other.m_V[ 2 ], m_V[ 3 ]+p_Other.m_V[ 3 ] );
	}

	Vector4 Vector4::operator-( const Vector4 &p_Other ) const
	{
		return Vector4( m_V[ 0 ]-p_Other.m_V[ 0 ], m_V[ 1 ]-p_Other.m_V[ 1 ],
			m_V[ 2 ]-p_Other.m_V[ 2 ], m_V[ 3 ]-p_Other.m_V[ 3 ] );
	}

	Vector4 Vector4::operator*( const Vector4 &p_Other ) const
	{
		return Vector4( m_V[ 0 ]*p_Other.m_V[ 0 ], m_V[ 1 ]*p_Other.m_V[ 1],
			m_V[ 2 ]*p_Other.m_V[ 2 ], m_V[ 3 ]*p_Other.m_V[ 3 ] );
	}

	Vector4 Vector4::operator*( const BD_FLOAT32 p_Scalar ) const
	{
		return Vector4( m_V[ 0 ]*p_Scalar, m_V[ 1 ]*p_Scalar,
			m_V[ 2 ]*p_Scalar, m_V[ 3 ]*p_Scalar );
	}

	Vector4 Vector4::operator/( const BD_FLOAT32 p_Scalar ) const
	{
		return Vector4( m_V[ 0 ]/p_Scalar, m_V[ 1 ]/p_Scalar,
			m_V[ 2 ]/p_Scalar, m_V[ 3 ]/p_Scalar );
	}

	Vector4 &Vector4::operator+=( const Vector4 &p_Other )
	{
		m_V[ 0 ] *= p_Other.m_V[ 0 ];
		m_V[ 1 ] *= p_Other.m_V[ 1 ];
		m_V[ 2 ] *= p_Other.m_V[ 2 ];
		m_V[ 3 ] *= p_Other.m_V[ 3 ];

		return *this;
	}
	
	Vector4 &Vector4::operator-=( const Vector4 &p_Other )
	{
		m_V[ 0 ] -= p_Other.m_V[ 0 ];
		m_V[ 1 ] -= p_Other.m_V[ 1 ];
		m_V[ 2 ] -= p_Other.m_V[ 2 ];
		m_V[ 3 ] -= p_Other.m_V[ 3 ];

		return *this;
	}

	Vector4 &Vector4::operator*=( const Vector4 &p_Other )
	{
		m_V[ 0 ] *= p_Other.m_V[ 0 ];
		m_V[ 1 ] *= p_Other.m_V[ 1 ];
		m_V[ 2 ] *= p_Other.m_V[ 2 ];
		m_V[ 3 ] *= p_Other.m_V[ 3 ];
		
		return *this;
	}

	Vector4 &Vector4::operator*=( const BD_FLOAT32 p_Scalar )
	{
		m_V[ 0 ] *= p_Scalar;
		m_V[ 1 ] *= p_Scalar;
		m_V[ 2 ] *= p_Scalar;
		m_V[ 3 ] *= p_Scalar;

		return *this;
	}

	Vector4 &Vector4::operator/=( const BD_FLOAT32 p_Scalar )
	{
		m_V[ 0 ] /= p_Scalar;
		m_V[ 1 ] /= p_Scalar;
		m_V[ 2 ] /= p_Scalar;
		m_V[ 3 ] /= p_Scalar;

		return *this;
	}
}

