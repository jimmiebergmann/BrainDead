#include <Matrix3x3.hpp>
#include <Vector3.hpp>
#include <Quaternion.hpp>
#include <Arithmetic.hpp>
#include <cmath>

namespace BD
{
	Matrix3x3::Matrix3x3( )
	{
		this->Identity( );
	}

	void Matrix3x3::Identity( )
	{
		m_M[ 0 ] = m_M[ 4 ] = m_M[ 8 ] = 1.0f;

		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 6 ] = m_M[ 7 ] = 0.0f;
	}

	BD_BOOL Matrix3x3::IsIdentity( ) const
	{
		if( BD::Equal( m_M[ 0 ], 1.0f ) &&
			BD::IsZero( m_M[ 1 ] ) &&
			BD::IsZero( m_M[ 2 ] ) &&
			BD::IsZero( m_M[ 3 ] ) &&
			BD::Equal( m_M[ 4 ], 1.0f ) &&
			BD::IsZero( m_M[ 5 ] ) &&
			BD::IsZero( m_M[ 6 ] ) &&
			BD::IsZero( m_M[ 7 ] ) &&
			BD::Equal( m_M[ 8 ], 1.0f ) )
		{
			return BD_TRUE;
		}

		return BD_FALSE;
	}

	BD_BOOL Matrix3x3::IsZero( ) const
	{
		for( BD_MEMSIZE i = 0; i < 9; ++i )
		{
			if( BD::IsZero( m_M[ i ] == BD_FALSE ) )
			{
				return BD_FALSE;
			}
		}

		return BD_TRUE;
	}

	void Matrix3x3::Clean( )
	{
		for( BD_MEMSIZE i = 0; i < 9; ++i )
		{
			if( BD::IsZero( m_M[ i ] == BD_TRUE ) )
			{
				m_M[ i ] = 0.0f;
			}
		}
	}

	void Matrix3x3::SetRows( const Vector3 &p_Row1, const Vector3 &p_Row2,
		const Vector3 &p_Row3 )
	{
		m_M[ 0 ] = p_Row1[ 0 ];
		m_M[ 3 ] = p_Row1[ 1 ];
		m_M[ 6 ] = p_Row1[ 2 ];

		m_M[ 1 ] = p_Row2[ 0 ];
		m_M[ 4 ] = p_Row2[ 1 ];
		m_M[ 7 ] = p_Row2[ 2 ];

		m_M[ 2 ] = p_Row3[ 0 ];
		m_M[ 5 ] = p_Row3[ 1 ];
		m_M[ 8 ] = p_Row3[ 2 ];
	}

	void Matrix3x3::GetRows( Vector3 &p_Row1, Vector3 &p_Row2,
		Vector3 &p_Row3 ) const
	{
		p_Row1[ 0 ] = m_M[ 0 ];
		p_Row1[ 1 ] = m_M[ 3 ];
		p_Row1[ 2 ] = m_M[ 6 ];

		p_Row2[ 0 ] = m_M[ 1 ];
		p_Row2[ 1 ] = m_M[ 4 ];
		p_Row2[ 2 ] = m_M[ 7 ];

		p_Row3[ 0 ] = m_M[ 2 ];
		p_Row3[ 1 ] = m_M[ 5 ];
		p_Row3[ 2 ] = m_M[ 8 ];
	}

	Vector3 Matrix3x3::GetRow( const BD_MEMSIZE p_Index ) const
	{
		return Vector3( m_M[ ( p_Index*3 ) ],
						m_M[ ( p_Index*3 )+1 ],
						m_M[ ( p_Index*3 )+2 ] );
	}

	void Matrix3x3::SetColumns( const Vector3 &p_Column1,
		const Vector3 &p_Column2, const Vector3 &p_Column3 )
	{
		m_M[ 0 ] = p_Column1[ 0 ];
		m_M[ 1 ] = p_Column1[ 1 ];
		m_M[ 2 ] = p_Column1[ 2 ];

		m_M[ 3 ] = p_Column2[ 0 ];
		m_M[ 4 ] = p_Column2[ 1 ];
		m_M[ 5 ] = p_Column2[ 2 ];

		m_M[ 6 ] = p_Column3[ 0 ];
		m_M[ 7 ] = p_Column3[ 1 ];
		m_M[ 8 ] = p_Column3[ 2 ];
	}

	void Matrix3x3::GetColumns( Vector3 &p_Column1, Vector3 &p_Column2,
		Vector3 &p_Column3 ) const
	{
		p_Column1[ 0 ] = m_M[ 0 ];
		p_Column1[ 1 ] = m_M[ 1 ];
		p_Column1[ 2 ] = m_M[ 2 ];

		p_Column2[ 0 ] = m_M[ 3 ];
		p_Column2[ 1 ] = m_M[ 4 ];
		p_Column2[ 2 ] = m_M[ 5 ];

		p_Column3[ 0 ] = m_M[ 6 ];
		p_Column3[ 1 ] = m_M[ 7 ];
		p_Column3[ 2 ] = m_M[ 8 ];
	}

	Vector3 Matrix3x3::GetColumn( const BD_MEMSIZE p_Index ) const
	{
		return Vector3( m_M[ p_Index ], m_M[ p_Index+1 ], m_M[ p_Index+2 ] );
	}

	Matrix3x3 &Matrix3x3::Rotate( const Quaternion &p_Quaternion )
	{
		return *this;
	}

	Matrix3x3 &Matrix3x3::Rotate( const Vector3 &p_Axis,
		const BD_FLOAT32 p_Angle )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;

		Sine = sinf( p_Angle );
		Cosine = cosf( p_Angle );

		BD_FLOAT32 Tangent = ( 1.0f - Cosine );

		m_M[ 0 ] = ( Tangent*( p_Axis[ 0 ]*p_Axis[ 0 ] ) ) + Cosine;
		m_M[ 1 ] = ( Tangent*p_Axis[ 0 ]*p_Axis[ 1 ] ) + ( Sine*p_Axis[ 2 ] );
		m_M[ 2 ] = ( Tangent*p_Axis[ 0 ]*p_Axis[ 2 ] ) + ( Sine*p_Axis[ 1 ] );

		m_M[ 3 ] = ( Tangent*p_Axis[ 0 ]*p_Axis[ 1 ] ) + ( Sine*p_Axis[ 2 ] );
		m_M[ 4 ] = ( Tangent*( p_Axis[ 1 ]*p_Axis[ 1 ] ) ) + Cosine;
		m_M[ 5 ] = ( Tangent*p_Axis[ 1 ]*p_Axis[ 2 ] ) + ( Sine*p_Axis[ 0 ] );

		m_M[ 6 ] = ( Tangent*p_Axis[ 0 ]*p_Axis[ 1 ] ) - ( Sine*p_Axis[ 1 ] );
		m_M[ 7 ] = ( Tangent*p_Axis[ 1 ]*p_Axis[ 0 ] ) - ( Sine*p_Axis[ 0 ] );
		m_M[ 8 ] = ( Tangent*( p_Axis[ 2 ]*p_Axis[ 2 ] ) ) + Cosine;

		return *this;
	}

	Matrix3x3 &Matrix3x3::Rotate( const BD_FLOAT32 p_Roll,
		const BD_FLOAT32 p_Pitch,
		const BD_FLOAT32 p_Yaw )
	{
		BD_FLOAT32 SX = 0.0f, SY = 0.0f, SZ = 0.0f;
		BD_FLOAT32 CX = 0.0f, CY = 0.0f, CZ = 0.0f;

		SX = sinf( p_Pitch );
		CX = cosf( p_Pitch );
		SY = sinf( p_Yaw );
		CY = cosf( p_Yaw );
		SZ = sinf( p_Roll );
		CZ = cosf( p_Roll );

		m_M[ 0 ] = CY*CZ;
		m_M[ 1 ] = ( SX*SY*CZ ) + ( CX*SZ );
		m_M[ 2 ] = -( CX*SY*CZ ) + ( SX*SZ );

		m_M[ 3 ] = -( CY*SZ );
		m_M[ 4 ] = -( SX*SY*SZ ) + ( CX*CZ );
		m_M[ 5 ] = ( CX*SY*SZ ) + ( SX*SZ );

		m_M[ 6 ] = SY;
		m_M[ 7 ] = -( SX*CY );
		m_M[ 8 ] = CX*CY;

		return *this;
	}

	Matrix3x3 &Matrix3x3::RotateX( const BD_FLOAT32 p_X )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;

		Sine = sinf( p_X );
		Cosine = cosf( p_X );

		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;

		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = Cosine;
		m_M[ 5 ] = -Sine;

		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = Sine;
		m_M[ 8 ] = Cosine;

		return *this;
	}

	Matrix3x3 &Matrix3x3::RotateY( const BD_FLOAT32 p_Y )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;

		Sine = sinf( p_Y );
		Cosine = cosf( p_Y );

		m_M[ 0 ] = Cosine;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = -Sine;

		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = 1.0f;
		m_M[ 5 ] = 0.0f;

		m_M[ 6 ] = Sine;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = Cosine;

		return *this;
	}

	Matrix3x3 &Matrix3x3::RotateZ( const BD_FLOAT32 p_Z )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;

		Sine = sinf( p_Z );
		Cosine = cosf( p_Z );

		m_M[ 0 ] = Cosine;
		m_M[ 1 ] = Sine;
		m_M[ 2 ] = 0.0f;

		m_M[ 3 ] = -Sine;
		m_M[ 4 ] = Cosine;
		m_M[ 5 ] = 0.0f;

		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = 1.0f;

		return *this;
	}

	Matrix3x3 &Matrix3x3::Scale( const Vector3 &p_Scale )
	{
		m_M[ 0 ] = p_Scale[ 0 ];
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;

		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = p_Scale[ 1 ];
		m_M[ 5 ] = 0.0f;

		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = p_Scale[ 2 ];

		return *this;
	}

	Matrix3x3 &Matrix3x3::Scale( const BD_FLOAT32 p_Scale )
	{
		m_M[ 0 ] = p_Scale;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;

		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = p_Scale;
		m_M[ 5 ] = 0.0f;

		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = p_Scale;

		return *this;
	}

	Matrix3x3 &Matrix3x3::ScaleX( const BD_FLOAT32 p_X )
	{
		m_M[ 0 ] = p_X;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		
		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = 1.0f;
		m_M[ 5 ] = 0.0f;

		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = 1.0f;

		return *this;
	}

	Matrix3x3 &Matrix3x3::ScaleY( const BD_FLOAT32 p_Y )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;

		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = p_Y;
		m_M[ 5 ] = 0.0f;

		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = 1.0f;

		return *this;
	}

	Matrix3x3 &Matrix3x3::ScaleZ( const BD_FLOAT32 p_Z )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;

		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = 1.0f;
		m_M[ 5 ] = 0.0f;
		
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = p_Z;

		return *this;
	}

	Matrix3x3 &Matrix3x3::Transpose( )
	{
		BD_FLOAT32 Tmp = m_M[ 3 ];
		m_M[ 3 ] = m_M[ 1 ];
		m_M[ 1 ] = Tmp;

		Tmp = m_M[ 6 ];
		m_M[ 6 ] = m_M[ 2 ];
		m_M[ 2 ] = Tmp;

		Tmp = m_M[ 7 ];
		m_M[ 7 ] = m_M[ 5 ];
		m_M[ 5 ] = Tmp;

		return *this;
	}

	void Matrix3x3::Transpose( Matrix3x3 &p_Transpose ) const
	{
		p_Transpose[ 0 ] = m_M[ 0 ];
		p_Transpose[ 1 ] = m_M[ 3 ];
		p_Transpose[ 2 ] = m_M[ 6 ];

		p_Transpose[ 3 ] = m_M[ 1 ];
		p_Transpose[ 4 ] = m_M[ 4 ];
		p_Transpose[ 5 ] = m_M[ 7 ];

		p_Transpose[ 6 ] = m_M[ 2 ];
		p_Transpose[ 7 ] = m_M[ 5 ];
		p_Transpose[ 8 ] = m_M[ 8 ];
	}

	Matrix3x3 &Matrix3x3::TransposeOf( const Matrix3x3 &p_Transpose )
	{
		p_Transpose.Transpose( *this );
		
		return *this;
	}

	Matrix3x3 &Matrix3x3::Inverse( )
	{
		BD_FLOAT32 Determinate = this->Determinate( );

		if( BD::IsZero( Determinate ) )
		{
			return *this;
		}

		BD_FLOAT32 Factor = 1.0f/Determinate;

		*this = this->Adjoint( );

		m_M[ 0 ] *= Factor;
		m_M[ 1 ] *= Factor;
		m_M[ 2 ] *= Factor;
		m_M[ 3 ] *= Factor;
		m_M[ 4 ] *= Factor;
		m_M[ 5 ] *= Factor;
		m_M[ 6 ] *= Factor;
		m_M[ 7 ] *= Factor;
		m_M[ 8 ] *= Factor;

		return *this;
	}

	void Matrix3x3::Inverse( Matrix3x3 &p_Inverse ) const
	{
		BD_FLOAT32 Determinate = this->Determinate( );

		if( BD::IsZero( Determinate ) )
		{
			return;
		}

		BD_FLOAT32 Factor = 1.0f/Determinate;

		p_Inverse = this->Adjoint( );

		p_Inverse[ 0 ] *= Factor;
		p_Inverse[ 1 ] *= Factor;
		p_Inverse[ 2 ] *= Factor;
		p_Inverse[ 3 ] *= Factor;
		p_Inverse[ 4 ] *= Factor;
		p_Inverse[ 5 ] *= Factor;
		p_Inverse[ 6 ] *= Factor;
		p_Inverse[ 7 ] *= Factor;
		p_Inverse[ 8 ] *= Factor;
	}

	Matrix3x3 &Matrix3x3::InverseOf( const Matrix3x3 &p_Inverse )
	{
		p_Inverse.Inverse( *this );

		return *this;
	}

	BD_FLOAT32 Matrix3x3::Determinate( ) const
	{
		return ( m_M[ 0 ]*( ( m_M[ 4 ]*m_M[ 8 ] ) - ( m_M[ 5 ]*m_M[ 7 ] ) ) +
			m_M[ 3 ]*( ( m_M[ 7 ]*m_M[ 2 ] ) - ( m_M[ 1 ]*m_M[ 8 ] ) ) +
			m_M[ 6 ]*( ( m_M[ 1 ]*m_M[ 5 ] ) - ( m_M[ 2 ]*m_M[ 4 ] ) ) );
	}

	Matrix3x3 Matrix3x3::Adjoint( ) const
	{
		Matrix3x3 Adjoint;

		// Get the transposed co-efficients
		Adjoint[ 0 ] = ( m_M[ 4 ]*m_M[ 8 ] ) - ( m_M[ 7 ]*m_M[ 5 ] );
		Adjoint[ 1 ] = ( m_M[ 2 ]*m_M[ 7 ] ) - ( m_M[ 1 ]*m_M[ 8 ] );
		Adjoint[ 2 ] = ( m_M[ 1 ]*m_M[ 5 ] ) - ( m_M[ 2 ]*m_M[ 4 ] );

		Adjoint[ 3 ] = ( m_M[ 5 ]*m_M[ 6 ] ) - ( m_M[ 3 ]*m_M[ 8 ] );
		Adjoint[ 4 ] = ( m_M[ 0 ]*m_M[ 8 ] ) - ( m_M[ 2 ]*m_M[ 6 ] );
		Adjoint[ 5 ] = ( m_M[ 0 ]*m_M[ 5 ] ) - ( m_M[ 3 ]*m_M[ 2 ] );

		Adjoint[ 6 ] = ( m_M[ 3 ]*m_M[ 7 ] ) - ( m_M[ 6 ]*m_M[ 4 ] );
		Adjoint[ 7 ] = ( m_M[ 0 ]*m_M[ 7 ] ) - ( m_M[ 6 ]*m_M[ 1 ] );
		Adjoint[ 8 ] = ( m_M[ 0 ]*m_M[ 4 ] ) - ( m_M[ 3 ]*m_M[ 1 ] );

		return Adjoint;
	}

	BD_FLOAT32 Matrix3x3::Trace( ) const
	{
		return ( m_M[ 0 ] + m_M[ 4 ] + m_M[ 8 ] );
	}

	BD_BOOL Matrix3x3::operator==( const Matrix3x3 &p_Other ) const
	{
		for( BD_MEMSIZE i = 0; i < 9; ++i )
		{
			if( BD::Equal( m_M[ i ], p_Other[ i ] ) == BD_FALSE )
			{
				return BD_FALSE;
			}
		}

		return BD_TRUE;
	}

	BD_BOOL Matrix3x3::operator!=( const Matrix3x3 &p_Other ) const
	{
		for( BD_MEMSIZE i = 0; i < 9; ++i )
		{
			if( BD::Equal( m_M[ i ], p_Other[ i ] ) == BD_TRUE )
			{
				return BD_TRUE;
			}
		}
		return BD_FALSE;
	}

	Matrix3x3 Matrix3x3::operator+( const Matrix3x3 &p_Other ) const
	{
		Matrix3x3 Matrix;

		Matrix[ 0 ] = m_M[ 0 ] + p_Other[ 0 ];
		Matrix[ 1 ] = m_M[ 1 ] + p_Other[ 1 ];
		Matrix[ 2 ] = m_M[ 2 ] + p_Other[ 2 ];
		Matrix[ 3 ] = m_M[ 3 ] + p_Other[ 3 ];
		Matrix[ 4 ] = m_M[ 4 ] + p_Other[ 4 ];
		Matrix[ 5 ] = m_M[ 5 ] + p_Other[ 5 ];
		Matrix[ 6 ] = m_M[ 6 ] + p_Other[ 6 ];
		Matrix[ 7 ] = m_M[ 7 ] + p_Other[ 7 ];
		Matrix[ 8 ] = m_M[ 8 ] + p_Other[ 8 ];

		return Matrix;
	}

	Matrix3x3 Matrix3x3::operator-( const Matrix3x3 &p_Other ) const
	{
		Matrix3x3 Matrix;

		Matrix[ 0 ] = m_M[ 0 ] - p_Other[ 0 ];
		Matrix[ 1 ] = m_M[ 1 ] - p_Other[ 1 ];
		Matrix[ 2 ] = m_M[ 2 ] - p_Other[ 2 ];
		Matrix[ 3 ] = m_M[ 3 ] - p_Other[ 3 ];
		Matrix[ 4 ] = m_M[ 4 ] - p_Other[ 4 ];
		Matrix[ 5 ] = m_M[ 5 ] - p_Other[ 5 ];
		Matrix[ 6 ] = m_M[ 6 ] - p_Other[ 6 ];
		Matrix[ 7 ] = m_M[ 7 ] - p_Other[ 7 ];
		Matrix[ 8 ] = m_M[ 8 ] - p_Other[ 8 ];

		return Matrix;
	}

	Matrix3x3 Matrix3x3::operator*( const Matrix3x3 &p_Other ) const
	{
		Matrix3x3 Matrix;

        Matrix[ 0 ] =	m_M[ 0 ]*p_Other[ 0 ] +
						m_M[ 3 ]*p_Other[ 1 ] +
						m_M[ 6 ]*p_Other[ 2 ];
		Matrix[ 1 ] =	m_M[ 1 ]*p_Other[ 0 ] +
						m_M[ 4 ]*p_Other[ 1 ] +
						m_M[ 7 ]*p_Other[ 2 ];
		Matrix[ 2 ]	=	m_M[ 2 ]*p_Other[ 0 ] +
						m_M[ 5 ]*p_Other[ 1 ] +
						m_M[ 8 ]*p_Other[ 2 ];

		Matrix[ 3 ] =	m_M[ 0 ]*p_Other[ 3 ] +
						m_M[ 3 ]*p_Other[ 4 ] +
						m_M[ 6 ]*p_Other[ 5 ];
		Matrix[ 4 ] =	m_M[ 1 ]*p_Other[ 3 ] +
						m_M[ 4 ]*p_Other[ 4 ] +
						m_M[ 7 ]*p_Other[ 5 ];
		Matrix[ 5 ] =	m_M[ 2 ]*p_Other[ 3 ] +
						m_M[ 5 ]*p_Other[ 4 ] +
						m_M[ 8 ]*p_Other[ 5 ];

		Matrix[ 6 ] =	m_M[ 0 ]*p_Other[ 6 ] +
						m_M[ 3 ]*p_Other[ 7 ] +
						m_M[ 6 ]*p_Other[ 8 ];
		Matrix[ 7 ] =	m_M[ 1 ]*p_Other[ 6 ] +
						m_M[ 4 ]*p_Other[ 7 ] +
						m_M[ 7 ]*p_Other[ 8 ];
		Matrix[ 8 ] =	m_M[ 2 ]*p_Other[ 6 ] +
						m_M[ 5 ]*p_Other[ 7 ] +
						m_M[ 8 ]*p_Other[ 8 ];

		return Matrix;
	}

	Matrix3x3 Matrix3x3::operator*( const BD_FLOAT32 p_Scalar ) const
	{
		Matrix3x3 Matrix;
	
		Matrix[ 0 ] = m_M[ 0 ]*p_Scalar;
		Matrix[ 1 ] = m_M[ 1 ]*p_Scalar;
		Matrix[ 2 ] = m_M[ 2 ]*p_Scalar;
		Matrix[ 3 ] = m_M[ 3 ]*p_Scalar;
		Matrix[ 4 ] = m_M[ 4 ]*p_Scalar;
		Matrix[ 5 ] = m_M[ 5 ]*p_Scalar;
		Matrix[ 6 ] = m_M[ 6 ]*p_Scalar;
		Matrix[ 7 ] = m_M[ 7 ]*p_Scalar;
		Matrix[ 8 ] = m_M[ 8 ]*p_Scalar;

		return Matrix;
	}

	Vector3 Matrix3x3::operator*( const Vector3 &p_Vec ) const
	{
		return Vector3( (	m_M[ 0 ]*p_Vec[ 0 ] +
							m_M[ 3 ]*p_Vec[ 1 ] +
							m_M[ 6 ]*p_Vec[ 2 ] ),
						(	m_M[ 1 ]*p_Vec[ 0 ] +
							m_M[ 4 ]*p_Vec[ 1 ] +
							m_M[ 7 ]*p_Vec[ 2 ] ),
						(	m_M[ 2 ]*p_Vec[ 0 ] +
							m_M[ 5 ]*p_Vec[ 1 ] +
							m_M[ 8 ]*p_Vec[ 2 ] ) );
	}

	Matrix3x3 &Matrix3x3::operator+=( const Matrix3x3 &p_Other )
	{
		m_M[ 0 ] += p_Other[ 0 ];
		m_M[ 1 ] += p_Other[ 1 ];
		m_M[ 2 ] += p_Other[ 2 ];
		m_M[ 3 ] += p_Other[ 3 ];
		m_M[ 4 ] += p_Other[ 4 ];
		m_M[ 5 ] += p_Other[ 5 ];
		m_M[ 6 ] += p_Other[ 6 ];
		m_M[ 7 ] += p_Other[ 7 ];
		m_M[ 8 ] += p_Other[ 8 ];

		return *this;
	}

	Matrix3x3 &Matrix3x3::operator-=( const Matrix3x3 &p_Other )
	{
		m_M[ 0 ] -= p_Other[ 0 ];
		m_M[ 1 ] -= p_Other[ 1 ];
		m_M[ 2 ] -= p_Other[ 2 ];
		m_M[ 3 ] -= p_Other[ 3 ];
		m_M[ 4 ] -= p_Other[ 4 ];
		m_M[ 5 ] -= p_Other[ 5 ];
		m_M[ 6 ] -= p_Other[ 6 ];
		m_M[ 7 ] -= p_Other[ 7 ];
		m_M[ 8 ] -= p_Other[ 8 ];

		return *this;
	}

	Matrix3x3 &Matrix3x3::operator*=( const Matrix3x3 &p_Other )
	{
		Matrix3x3 Copy;
		for( BD_MEMSIZE i = 0; i < 9; ++i )
		{
			Copy[ i ] = m_M[ i ];
		}

		m_M[ 0 ] =	Copy[ 0 ]*p_Other[ 0 ] +
					Copy[ 3 ]*p_Other[ 1 ] +
					Copy[ 6 ]*p_Other[ 2 ];
		m_M[ 1 ] =	Copy[ 1 ]*p_Other[ 0 ] +
					Copy[ 4 ]*p_Other[ 1 ] +
					Copy[ 7 ]*p_Other[ 2 ];
		m_M[ 2 ] =	Copy[ 2 ]*p_Other[ 0 ] +
					Copy[ 5 ]*p_Other[ 1 ] +
					Copy[ 8 ]*p_Other[ 2 ];

		m_M[ 3 ] =	Copy[ 0 ]*p_Other[ 3 ] +
					Copy[ 3 ]*p_Other[ 4 ] +
					Copy[ 6 ]*p_Other[ 5 ];
		m_M[ 4 ] =	Copy[ 1 ]*p_Other[ 3 ] +
					Copy[ 4 ]*p_Other[ 4 ] +
					Copy[ 7 ]*p_Other[ 5 ];
		m_M[ 5 ] =	Copy[ 2 ]*p_Other[ 3 ] +
					Copy[ 5 ]*p_Other[ 4 ] +
					Copy[ 8 ]*p_Other[ 5 ];

		m_M[ 6 ] =	Copy[ 0 ]*p_Other[ 6 ] +
					Copy[ 3 ]*p_Other[ 7 ] +
					Copy[ 6 ]*p_Other[ 8 ];
		m_M[ 7 ] =	Copy[ 1 ]*p_Other[ 6 ] +
					Copy[ 4 ]*p_Other[ 7 ] +
					Copy[ 7 ]*p_Other[ 8 ];
		m_M[ 8 ] =	Copy[ 2 ]*p_Other[ 6 ] +
					Copy[ 5 ]*p_Other[ 7 ] +
					Copy[ 8 ]*p_Other[ 8 ];

		return *this;
	}

	Matrix3x3 &Matrix3x3::operator*=( const BD_FLOAT32 p_Scalar )
	{
		m_M[ 0 ] *= p_Scalar;
		m_M[ 1 ] *= p_Scalar;
		m_M[ 2 ] *= p_Scalar;
		m_M[ 3 ] *= p_Scalar;
		m_M[ 4 ] *= p_Scalar;
		m_M[ 5 ] *= p_Scalar;
		m_M[ 6 ] *= p_Scalar;
		m_M[ 7 ] *= p_Scalar;
		m_M[ 8 ] *= p_Scalar;

		return *this;
	}

	BD_FLOAT32 &Matrix3x3::operator( )( const BD_MEMSIZE p_Row,
		const BD_MEMSIZE p_Column )
	{
		return ( m_M[ p_Row+( p_Column*3 ) ] );
	}

	BD_FLOAT32 Matrix3x3::operator( )( const BD_MEMSIZE p_Row,
		const BD_MEMSIZE p_Column ) const
	{
		return ( m_M[ p_Row+( p_Column*3 ) ] );
	}

	Matrix3x3 &Matrix3x3::operator-( )
	{
		m_M[ 0 ] = -m_M[ 0 ];
		m_M[ 1 ] = -m_M[ 1 ];
		m_M[ 2 ] = -m_M[ 2 ];
		m_M[ 3 ] = -m_M[ 3 ];
		m_M[ 4 ] = -m_M[ 4 ];
		m_M[ 5 ] = -m_M[ 5 ];
		m_M[ 6 ] = -m_M[ 6 ];
		m_M[ 7 ] = -m_M[ 7 ];
		m_M[ 8 ] = -m_M[ 8 ];

		return *this;
	}
}
