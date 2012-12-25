#include <Matrix4x4.hpp>
#include <Matrix3x3.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>
#include <Quaternion.hpp>
#include <Arithmetic.hpp>
#include <cmath>

namespace BD
{
	void Matrix4x4::Identity( )
	{
		m_M[ 0 ] = m_M[ 5 ] = m_M[ 10 ] = m_M[ 15 ] = 1.0f;

		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = m_M[ 6 ] = m_M[ 8 ] =
			m_M[ 9 ] = m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
	}

	BD_BOOL Matrix4x4::IsIdentity( ) const
	{
		if( BD::Equal( 1.0f, m_M[ 0 ] ) &&
			BD::IsZero( m_M[ 1 ] ) &&
			BD::IsZero( m_M[ 2 ] ) &&
			BD::IsZero( m_M[ 3 ] ) &&
			BD::IsZero( m_M[ 4 ] ) &&
			BD::Equal( 1.0f, m_M[ 5 ] ) &&
			BD::IsZero( m_M[ 6 ] ) &&
			BD::IsZero( m_M[ 7 ] ) &&
			BD::IsZero( m_M[ 8 ] ) &&
			BD::IsZero( m_M[ 9 ] ) &&
			BD::Equal( 1.0f, m_M[ 10 ] ) &&
			BD::IsZero( m_M[ 11 ] ) &&
			BD::IsZero( m_M[ 12 ] ) &&
			BD::IsZero( m_M[ 13 ] ) &&
			BD::IsZero( m_M[ 14 ] ) &&
			BD::Equal( 1.0f, m_M[ 15 ] ) )
		{
			return BD_TRUE;
		}

		return BD_FALSE;
	}

	BD_BOOL Matrix4x4::IsZero( ) const
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			if( BD::IsZero( m_M[ i ] ) != BD_TRUE )
			{
				return BD_FALSE;
			}
		}
		return BD_TRUE;
	}

	BD_FLOAT32 Matrix4x4::Trace( ) const
	{
		return ( m_M[ 0 ] + m_M[ 5 ] + m_M[ 10 ] + m_M[ 15 ] );
	}

	void Matrix4x4::Clean( )
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			if( BD::IsZero( m_M[ i ] ) )
			{
				m_M[ i ] = 0.0f;
			}
		}
	}

	void Matrix4x4::SetRows( const Vector4 &p_Row1, const Vector4 &p_Row2,
		const Vector4 &p_Row3, const Vector4 &p_Row4 )
	{
		m_M[ 0 ] = p_Row1[ 0 ];
		m_M[ 4 ] = p_Row1[ 1 ];
		m_M[ 8 ] = p_Row1[ 2 ];
		m_M[ 12 ] = p_Row1[ 3 ];

		m_M[ 1 ] = p_Row2[ 0 ];
		m_M[ 5 ] = p_Row2[ 1 ];
		m_M[ 9 ] = p_Row2[ 2 ];
		m_M[ 13 ] = p_Row2[ 3 ];

		m_M[ 2 ] = p_Row3[ 0 ];
		m_M[ 6 ] = p_Row3[ 1 ];
		m_M[ 10 ] = p_Row3[ 2 ];
		m_M[ 14 ] = p_Row3[ 3 ];

		m_M[ 3 ] = p_Row4[ 0 ];
		m_M[ 7 ] = p_Row4[ 1 ];
		m_M[ 11 ] = p_Row4[ 2 ];
		m_M[ 15 ] = p_Row4[ 3 ];
	}

	void Matrix4x4::GetRows( Vector4 &p_Row1, Vector4 &p_Row2,
		Vector4 &p_Row3, Vector4 &p_Row4 ) const
	{
		p_Row1[ 0 ] = m_M[ 0 ];
		p_Row1[ 1 ] = m_M[ 4 ];
		p_Row1[ 2 ] = m_M[ 8 ];
		p_Row1[ 3 ] = m_M[ 12 ];

		p_Row2[ 0 ] = m_M[ 1 ];
		p_Row2[ 1 ] = m_M[ 5 ];
		p_Row2[ 2 ] = m_M[ 9 ];
		p_Row2[ 3 ] = m_M[ 13 ];

		p_Row3[ 0 ] = m_M[ 2 ];
		p_Row3[ 1 ] = m_M[ 6 ];
		p_Row3[ 2 ] = m_M[ 10 ];
		p_Row3[ 3 ] = m_M[ 14 ];

		p_Row4[ 0 ] = m_M[ 3 ];
		p_Row4[ 1 ] = m_M[ 7 ];
		p_Row4[ 2 ] = m_M[ 11 ];
		p_Row4[ 3 ] = m_M[ 15 ];
	}

	Vector4 Matrix4x4::GetRow( const BD_MEMSIZE p_Index ) const
	{
		return Vector4( m_M[ ( p_Index*4 ) ],
						m_M[ ( p_Index*4 ) + 1 ],
						m_M[ ( p_Index*4 ) + 2 ],
						m_M[ ( p_Index*4 ) + 3 ] );
	}

	void Matrix4x4::SetColumns( const Vector4 &p_Column1,
		const Vector4 &p_Column2, const Vector4 &p_Column3,
		const Vector4 &p_Column4 )
	{
		m_M[ 0 ] = p_Column1[ 0 ];
		m_M[ 1 ] = p_Column1[ 1 ];
		m_M[ 2 ] = p_Column1[ 2 ];
		m_M[ 3 ] = p_Column1[ 3 ];

		m_M[ 4 ] = p_Column2[ 0 ];
		m_M[ 5 ] = p_Column2[ 1 ];
		m_M[ 6 ] = p_Column2[ 2 ];
		m_M[ 7 ] = p_Column2[ 3 ];

		m_M[ 8 ] = p_Column3[ 0 ];
		m_M[ 9 ] = p_Column3[ 1 ];
		m_M[ 10 ] = p_Column3[ 2 ];
		m_M[ 11 ] = p_Column3[ 3 ];

		m_M[ 12 ] = p_Column4[ 0 ];
		m_M[ 13 ] = p_Column4[ 1 ];
		m_M[ 14 ] = p_Column4[ 2 ];
		m_M[ 15 ] = p_Column4[ 3 ];
	}

	void Matrix4x4::GetColumns( Vector4 &p_Column1, Vector4 &p_Column2,
		Vector4 &p_Column3, Vector4 &p_Column4 ) const
	{
		p_Column1[ 0 ] = m_M[ 0 ];
		p_Column1[ 1 ] = m_M[ 1 ];
		p_Column1[ 2 ] = m_M[ 2 ];
		p_Column1[ 3 ] = m_M[ 3 ];

		p_Column2[ 0 ] = m_M[ 4 ];
		p_Column2[ 1 ] = m_M[ 5 ];
		p_Column2[ 2 ] = m_M[ 6 ];
		p_Column2[ 3 ] = m_M[ 7 ];

		p_Column3[ 0 ] = m_M[ 8 ];
		p_Column3[ 1 ] = m_M[ 9 ];
		p_Column3[ 2 ] = m_M[ 10 ];
		p_Column3[ 3 ] = m_M[ 11 ];

		p_Column4[ 0 ] = m_M[ 12 ];
		p_Column4[ 1 ] = m_M[ 13 ];
		p_Column4[ 2 ] = m_M[ 14 ];
		p_Column4[ 3 ] = m_M[ 15 ];
	}

	Vector4 Matrix4x4::GetColumn( const BD_MEMSIZE p_Index ) const
	{
		return Vector4( m_M[ p_Index ],
						m_M[ p_Index+1 ],
						m_M[ p_Index+2 ],
						m_M[ p_Index+3 ] );
	}

	Matrix4x4 &Matrix4x4::Orthographic( const BD_FLOAT32 p_Left, const BD_FLOAT32 p_Right,
			const BD_FLOAT32 p_Bottom, const BD_FLOAT32 p_Top,
			const BD_FLOAT32 p_ZNear, const BD_FLOAT32 p_ZFar )
	{
		const BD_FLOAT32 TX =- ( p_Right + p_Left )	/ ( p_Right - p_Left );
		const BD_FLOAT32 TY =- ( p_Top + p_Bottom ) / ( p_Top -	p_Bottom );
		const BD_FLOAT32 TZ =- ( p_ZFar + p_ZNear )	/ ( p_ZFar - p_ZNear );

		//Identity();
		m_M[0] = 2.0f	/ ( p_Right - p_Left );
		m_M[1] = 0;
		m_M[2] = 0;
		m_M[3] = 0;
		m_M[4] = 0;
		m_M[5] = 2.0f	/ ( p_Top - p_Bottom );
		m_M[6] = 0;
		m_M[7] = 0;
		m_M[8] = 0;
		m_M[9] = 0;
		m_M[10] =- 2.0f / ( p_ZFar - p_ZNear );
		m_M[11] = 0;
		m_M[12] = TX;
		m_M[13] = TY;
		m_M[14] = TZ;
		m_M[15] = 1.0f;
		
		return *this;
	}

	Matrix4x4 &Matrix4x4::Translate( const Vector3 &p_Translation )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;
		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = 0.0f;
		m_M[ 12 ] = p_Translation[ 0 ];
		m_M[ 13 ] = p_Translation[ 1 ];
		m_M[ 14 ] = p_Translation[ 2 ];
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Vector3 Matrix4x4::Transform( const Vector3 &p_Point ) const
	{
		return Vector3( m_M[ 0 ]*p_Point[ 0 ] +
						m_M[ 4 ]*p_Point[ 1 ] +
						m_M[ 8 ]*p_Point[ 2 ] +
						m_M[ 12 ],
						m_M[ 1 ]*p_Point[ 0 ] +
						m_M[ 5 ]*p_Point[ 1 ] +
						m_M[ 9 ]*p_Point[ 2 ] +
						m_M[ 13 ],
						m_M[ 2 ]*p_Point[ 0 ] +
						m_M[ 6 ]*p_Point[ 1 ] +
						m_M[ 10 ]*p_Point[ 2 ] +
						m_M[ 14 ] );
	}

	Matrix4x4 &Matrix4x4::Rotate( const Matrix3x3 &p_Rotation )
	{
		m_M[ 0 ] = p_Rotation[ 0 ];
		m_M[ 1 ] = p_Rotation[ 1 ];
		m_M[ 2 ] = p_Rotation[ 2 ];
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = p_Rotation[ 3 ];
		m_M[ 5 ] = p_Rotation[ 4 ];
		m_M[ 6 ] = p_Rotation[ 5 ];
		m_M[ 7 ] = 0.0f;
		
		m_M[ 8 ] = p_Rotation[ 6 ];
		m_M[ 9 ] = p_Rotation[ 7 ];
		m_M[ 10 ] = p_Rotation[ 8 ];
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::Rotate( const Quaternion &p_Quaternion )
	{
		return *this;
	}

	Matrix4x4 &Matrix4x4::Rotate( const BD_FLOAT32 p_Roll,
		const BD_FLOAT32 p_Pitch, const BD_FLOAT32 p_Yaw )
	{
		
		
		return *this;
	}

	Matrix4x4 &Matrix4x4::RotateX( const BD_FLOAT32 p_X )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;
		Sine = sinf( p_X );
		Cosine = cosf( p_X );

		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = Cosine;
		m_M[ 6 ] = -Sine;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = Sine;
		m_M[ 10 ] = Cosine;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::RotateY( const BD_FLOAT32 p_Y )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;
		Sine = sinf( p_Y );
		Cosine = cosf( p_Y );

		m_M[ 0 ] = Cosine;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = -Sine;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		
		m_M[ 8 ] = Sine;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = Cosine;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::RotateZ( const BD_FLOAT32 p_Z )
	{
		BD_FLOAT32 Sine = 0.0f, Cosine = 0.0f;
		Sine = sinf( p_Z );
		Cosine = cosf( p_Z );

		m_M[ 0 ] = Cosine;
		m_M[ 1 ] = Sine;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = -Sine;
		m_M[ 5 ] = Cosine;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;
		
		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::Scale( const Vector3 &p_Scale )
	{
		m_M[ 0 ] = p_Scale[ 0 ];
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;
		
		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = p_Scale[ 1 ];
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = p_Scale[ 2 ];
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::Scale( const BD_FLOAT32 p_Scale )
	{
		m_M[ 0 ] = p_Scale;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = p_Scale;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = p_Scale;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::ScaleX( const BD_FLOAT32 p_X )
	{
		m_M[ 0 ] = p_X;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = 0.0f;
		
		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::ScaleY( const BD_FLOAT32 p_Y )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = p_Y;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::ScaleZ( const BD_FLOAT32 p_Z )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = 0.0f;
		
		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::Transpose( )
	{
		BD_FLOAT32 Tmp = m_M[ 1 ];
		m_M[ 1 ] = m_M[ 4 ];
		m_M[ 4 ] = Tmp;

		Tmp = m_M[ 2 ];
		m_M[ 2 ] = m_M[ 8 ];
		m_M[ 8 ] = Tmp;

		Tmp = m_M[ 3 ];
		m_M[ 3 ] = m_M[ 12 ];
		m_M[ 12 ] = Tmp;

		Tmp = m_M[ 6 ];
		m_M[ 6 ] = m_M[ 9 ];
		m_M[ 9 ] = Tmp;

		Tmp = m_M[ 7 ];
		m_M[ 7 ] = m_M[ 13 ];
		m_M[ 13 ] = Tmp;

		Tmp = m_M[ 11 ];
		m_M[ 11 ] = m_M[ 14 ];
		m_M[ 14 ] = Tmp;

		return *this;
	}

	void Matrix4x4::Transpose( Matrix4x4 &p_Transpose ) const
	{
		p_Transpose[ 0 ] = m_M[ 0 ];
		p_Transpose[ 1 ] = m_M[ 4 ];
		p_Transpose[ 2 ] = m_M[ 8 ];
		p_Transpose[ 3 ] = m_M[ 12 ];

		p_Transpose[ 4 ] = m_M[ 1 ];
		p_Transpose[ 5 ] = m_M[ 5 ];
		p_Transpose[ 6 ] = m_M[ 9 ];
		p_Transpose[ 7 ] = m_M[ 13 ];
		
		p_Transpose[ 8 ] = m_M[ 2 ];
		p_Transpose[ 9 ] = m_M[ 6 ];
		p_Transpose[ 10 ] = m_M[ 10 ];
		p_Transpose[ 11 ] = m_M[ 14 ];

		p_Transpose[ 12 ] = m_M[ 3 ];
		p_Transpose[ 13 ] = m_M[ 7 ];
		p_Transpose[ 14 ] = m_M[ 11 ];
		p_Transpose[ 15 ] = m_M[ 15 ];
	}

	Matrix4x4 &Matrix4x4::TransposeOf( const Matrix4x4 &p_Transpose )
	{
		p_Transpose.Transpose( *this );
		return *this;
	}

	Matrix4x4 &Matrix4x4::AffineInverse( )
	{
		Matrix4x4 AI;

		// Compute the affine matrix's determinate
		BD_FLOAT32 CoFactor0 = ( m_M[ 5 ]*m_M[ 10 ] - m_M[ 6 ]*m_M[ 9 ] );
		BD_FLOAT32 CoFactor4 = ( m_M[ 2 ]*m_M[ 9 ] - m_M[ 1 ]*m_M[ 10 ] );
		BD_FLOAT32 CoFactor8 = ( m_M[ 1 ]*m_M[ 6 ] - m_M[ 2 ]*m_M[ 5 ] );
		BD_FLOAT32 Det = m_M[ 0 ]*CoFactor0 + m_M[ 4 ]*CoFactor4 +
			m_M[ 8 ]*CoFactor8;
		if( BD::IsZero( Det ) )
		{
			return AI;
		}

		// Create the adjunct and multiply by 1/Det
		BD_FLOAT32 InvDet = 1.0f/Det;

		AI[ 0 ] = InvDet * CoFactor0;
		AI[ 1 ] = InvDet * CoFactor4;
		AI[ 2 ] = InvDet * CoFactor8;

		// Pre-transpose the matrix
		AI[ 4 ] = InvDet*( m_M[ 6 ]*m_M[ 8 ] - m_M[ 4 ]*m_M[ 10 ] );
		AI[ 5 ] = InvDet*( m_M[ 0 ]*m_M[ 10 ] - m_M[ 2 ]*m_M[ 8 ] );
		AI[ 6 ] = InvDet*( m_M[ 2 ]*m_M[ 4 ] - m_M[ 0 ]*m_M[ 6 ] );

		AI[ 8 ] = InvDet*( m_M[ 4 ]*m_M[ 9 ] - m_M[ 5 ]*m_M[ 8 ] );
		AI[ 9 ] = InvDet*( m_M[ 1 ]*m_M[ 8 ] - m_M[ 0 ]*m_M[ 9 ] );
		AI[ 10 ] = InvDet*( m_M[ 0 ]*m_M[ 5 ] - m_M[ 1 ]*m_M[ 4 ] );

		// Multiply -Translation by the inverted 3x3 matrix to get its inverse
		AI[ 12 ] = -AI[ 0 ]*m_M[ 12 ] - AI[ 4 ]*m_M[ 13 ] - AI[ 8 ]*m_M[ 14 ];
		AI[ 13 ] = -AI[ 1 ]*m_M[ 12 ] - AI[ 5 ]*m_M[ 13 ] - AI[ 9 ]*m_M[ 14 ];
		AI[ 14 ] = -AI[ 2 ]*m_M[ 12 ] - AI[ 6 ]*m_M[ 13 ] - AI[ 10 ]*m_M[ 14 ];

		return AI;
	}

	void Matrix4x4::AffineInverse( Matrix4x4 &p_AffineInverse ) const
	{
		// Compute the affine matrix's determinate
		BD_FLOAT32 CoFactor0 = ( m_M[ 5 ]*m_M[ 10 ] - m_M[ 6 ]*m_M[ 9 ] );
		BD_FLOAT32 CoFactor4 = ( m_M[ 2 ]*m_M[ 9 ] - m_M[ 1 ]*m_M[ 10 ] );
		BD_FLOAT32 CoFactor8 = ( m_M[ 1 ]*m_M[ 6 ] - m_M[ 2 ]*m_M[ 5 ] );

		BD_FLOAT32 Det = m_M[ 0 ]*CoFactor0 + m_M[ 4 ]*CoFactor4 +
			m_M[ 8 ]*CoFactor8;

		if( BD::IsZero( Det ) )
		{
			return;
		}

		// Create the adjunct and multiply by 1/Det
		BD_FLOAT32 InvDet = 1.0f/Det;

		p_AffineInverse[ 0 ] = InvDet * CoFactor0;
		p_AffineInverse[ 1 ] = InvDet * CoFactor4;
		p_AffineInverse[ 2 ] = InvDet * CoFactor8;

		// Pre-transpose the matrix
		p_AffineInverse[ 4 ] = ( m_M[ 6 ]*m_M[ 8 ] + m_M[ 4 ]*m_M[ 10 ] );
		p_AffineInverse[ 5 ] = ( m_M[ 0 ]*m_M[ 10 ] + m_M[ 2 ]*m_M[ 8 ] );
		p_AffineInverse[ 6 ] = ( m_M[ 2 ]*m_M[ 4 ] - m_M[ 0 ]*m_M[ 6 ] );

		p_AffineInverse[ 8 ] = ( m_M[ 4 ]*m_M[ 9 ] - m_M[ 5 ]*m_M[ 8 ] );
		p_AffineInverse[ 9 ] = ( m_M[ 1 ]*m_M[ 8 ] - m_M[ 0 ]*m_M[ 9 ] );
		p_AffineInverse[ 10 ] = ( m_M[ 0 ]*m_M[ 5 ] - m_M[ 1 ]*m_M[ 4 ] );

		// Multiply -Translation by the inverted 3x3 matrix to get its inverse
		p_AffineInverse[ 12 ] = p_AffineInverse[ 0 ]*m_M[ 12 ] +
								p_AffineInverse[ 4 ]*m_M[ 13 ] +
								p_AffineInverse[ 8 ]*m_M[ 14 ];
		p_AffineInverse[ 13 ] = p_AffineInverse[ 1 ]*m_M[ 12 ] +
								p_AffineInverse[ 5 ]*m_M[ 13 ] +
								p_AffineInverse[ 9 ]*m_M[ 14 ];
		p_AffineInverse[ 14 ] = p_AffineInverse[ 2 ]*m_M[ 12 ] +
								p_AffineInverse[ 6 ]*m_M[ 13 ] +
								p_AffineInverse[ 10 ]*m_M[ 14 ];

	}

	Matrix4x4 &Matrix4x4::AffineInverseOf( const Matrix4x4 &p_AffineInverse )
	{
		p_AffineInverse.AffineInverse( *this );
		return *this;
	}

	BD_BOOL Matrix4x4::operator==( const Matrix4x4 &p_Other ) const
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			if( BD::Equal( m_M[ i ], p_Other[ i ] ) != BD_TRUE )
			{
				return BD_FALSE;
			}
		}
		return BD_TRUE;
	}

	BD_BOOL Matrix4x4::operator!=( const Matrix4x4 &p_Other ) const
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			if( BD::Equal( m_M[ i ], p_Other[ i ] ) )
			{
				return BD_FALSE;
			}
		}

		return BD_TRUE;
	}

	Matrix4x4 Matrix4x4::operator+( const Matrix4x4 &p_Other ) const
	{
		Matrix4x4 Return;

		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			Return[ i ] = m_M[ i ] + p_Other[ i ];
		}

		return Return;
	}

	Matrix4x4 Matrix4x4::operator-( const Matrix4x4 &p_Other ) const
	{
		Matrix4x4 Return;

		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			Return[ i ] = m_M[ i ] - p_Other[ i ];
		}

		return Return;
	}

	Matrix4x4 &Matrix4x4::operator-( )
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			m_M[ i ] = -m_M[ i ];
		}

		return *this;
	}

	Matrix4x4 Matrix4x4::operator*( const Matrix4x4 &p_Other ) const
	{
		Matrix4x4 Return;

		Return[ 0 ] = m_M[ 0 ]*p_Other[ 0 ] + m_M[ 4 ]*p_Other[ 1 ]
					+ m_M[ 8 ]*p_Other[ 3 ] + m_M[ 12 ]*p_Other[ 3 ];
		Return[ 1 ] = m_M[ 1 ]*p_Other[ 0 ] + m_M[ 5 ]*p_Other[ 1 ]
					+ m_M[ 9 ]*p_Other[ 2 ] + m_M[ 13 ]*p_Other[ 3 ];
		Return[ 2 ] = m_M[ 2 ]*p_Other[ 0 ] + m_M[ 6 ]*p_Other[ 1 ]
					+ m_M[ 10 ]*p_Other[ 2 ] + m_M[ 14 ]*p_Other[ 3 ];
		Return[ 3 ] = m_M[ 3 ]*p_Other[ 0 ] + m_M[ 7 ]*p_Other[ 1 ]
					+ m_M[ 11 ]*p_Other[ 2 ] + m_M[ 15 ]*p_Other[ 3 ];

		Return[ 4 ] = m_M[ 0 ]*p_Other[ 4 ] + m_M[ 4 ]*p_Other[ 5 ]
					+ m_M[ 8 ]*p_Other[ 6 ] + m_M[ 12 ]*p_Other[ 7 ];
		Return[ 5 ] = m_M[ 1 ]*p_Other[ 4 ] + m_M[ 5 ]*p_Other[ 5 ]
					+ m_M[ 9 ]*p_Other[ 7 ] + m_M[ 13 ]*p_Other[ 7 ];
		Return[ 6 ] = m_M[ 2 ]*p_Other[ 4 ] + m_M[ 6 ]*p_Other[ 5 ]
					+ m_M[ 10 ]*p_Other[ 6 ] + m_M[ 14 ]*p_Other[ 7 ];
		Return[ 7 ] = m_M[ 3 ]*p_Other[ 4 ] + m_M[ 7 ]*p_Other[ 5 ]
					+ m_M[ 11 ]*p_Other[ 6 ] + m_M[ 15 ]*p_Other[ 7 ];

		Return[ 8 ] = m_M[ 0 ]*p_Other[ 8 ] + m_M[ 4 ]*p_Other[ 9 ]
					+ m_M[ 8 ]*p_Other[ 10 ] + m_M[ 12 ]*p_Other[ 11 ];
		Return[ 9 ] = m_M[ 1 ]*p_Other[ 8 ] + m_M[ 5 ]*p_Other[ 9 ]
					+ m_M[ 9 ]*p_Other[ 10 ] + m_M[ 13 ]*p_Other[ 11 ];
		Return[ 10 ] = m_M[ 2 ]*p_Other[ 8 ] + m_M[ 6 ]*p_Other[ 9 ]
					+ m_M[ 10 ]*p_Other[ 10 ] + m_M[ 14 ]*p_Other[ 11 ];
		Return[ 11 ] = m_M[ 3 ]*p_Other[ 8 ] + m_M[ 7 ]*p_Other[ 9 ]
					+ m_M[ 11 ]*p_Other[ 10 ] + m_M[ 14 ]*p_Other[ 11 ];

		Return[ 12 ] = m_M[ 0 ]*p_Other[ 12 ] + m_M[ 4 ]*p_Other[ 13 ]
					+ m_M[ 8 ]*p_Other[ 14 ] + m_M[ 12 ]*p_Other[ 15 ];
		Return[ 13 ] = m_M[ 1 ]*p_Other[ 12 ] + m_M[ 5 ]*p_Other[ 13 ]
					+ m_M[ 9 ]*p_Other[ 14 ] + m_M[ 13 ]*p_Other[ 15 ];
		Return[ 14 ] = m_M[ 2 ]*p_Other[ 12 ] + m_M[ 6 ]*p_Other[ 13 ]
					+ m_M[ 10 ]*p_Other[ 14 ] + m_M[ 14 ]*p_Other[ 15 ];
		Return[ 15 ] = m_M[ 3 ]*p_Other[ 12 ] + m_M[ 7 ]*p_Other[ 13 ]
					+ m_M[ 11 ]*p_Other[ 14 ] + m_M[ 15 ]*p_Other[ 15 ];

		return Return;
	}

	Vector4 Matrix4x4::operator*( const Vector4 &p_Vec ) const
	{
		Vector4 Return;

		Return[ 0 ] = m_M[ 0 ]*p_Vec[ 0 ] + m_M[ 4 ]*p_Vec[ 1 ]
					+ m_M[ 8 ]*p_Vec[ 2 ] + m_M[ 12 ]*p_Vec[ 3 ];
		Return[ 1 ] = m_M[ 1 ]*p_Vec[ 0 ] + m_M[ 5 ]*p_Vec[ 1 ]
					+ m_M[ 9 ]*p_Vec[ 2 ] + m_M[ 13 ]*p_Vec[ 3 ];
		Return[ 2 ] = m_M[ 2 ]*p_Vec[ 0 ] + m_M[ 6 ]*p_Vec[ 1 ]
					+ m_M[ 10 ]*p_Vec[ 2 ] + m_M[ 14 ]*p_Vec[ 3 ];
		Return[ 3 ] = m_M[ 3 ]*p_Vec[ 0 ] + m_M[ 7 ]*p_Vec[ 1 ]
					+ m_M[ 11 ]*p_Vec[ 2 ] + m_M[ 15 ]*p_Vec[ 3 ];

		return Return;
	}

	Matrix4x4 Matrix4x4::operator*( const BD_FLOAT32 p_Scalar ) const
	{
		Matrix4x4 Return;

		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			Return[ i ] = m_M[ i ]*p_Scalar;
		}

		return Return;
	}

	Matrix4x4 &Matrix4x4::operator+=( const Matrix4x4 &p_Other )
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			m_M[ i ] += p_Other[ i ];
		}

		return *this;
	}

	Matrix4x4 &Matrix4x4::operator-=( const Matrix4x4 &p_Other )
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			m_M[ i ] -= p_Other[ i ];
		}

		return *this;
	}

	Matrix4x4 &Matrix4x4::operator*=( const Matrix4x4 &p_Other )
	{
		Matrix4x4 Copy;

		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			Copy[ i ] = m_M[ i ];
		}

		m_M[ 0 ] = Copy[ 0 ]*p_Other[ 0 ] + Copy[ 4 ]*p_Other[ 1 ]
				+ Copy[ 8 ]*p_Other[ 2 ] + Copy[ 12 ]*p_Other[ 3 ];
		m_M[ 1 ] = Copy[ 1 ]*p_Other[ 0 ] + Copy[ 5 ]*p_Other[ 1 ]
				+ Copy[ 9 ]*p_Other[ 2 ] + Copy[ 13 ]*p_Other[ 3 ];
		m_M[ 2 ] = Copy[ 2 ]*p_Other[ 0 ] + Copy[ 7 ]*p_Other[ 1 ]
				+ Copy[ 10 ]*p_Other[ 2 ] + Copy[ 14 ]*p_Other[ 3 ];
		m_M[ 3 ] = Copy[ 3 ]*p_Other[ 0 ] + Copy[ 8 ]*p_Other[ 1 ]
				+ Copy[ 11 ]*p_Other[ 2 ] + Copy[ 15 ]*p_Other[ 3 ];

		m_M[ 4 ] = Copy[ 0 ]*p_Other[ 4 ] + Copy[ 4 ]*p_Other[ 5 ]
				+ Copy[ 8 ]*p_Other[ 6 ] + Copy[ 12 ]*p_Other[ 7 ];
		m_M[ 5 ] = Copy[ 1 ]*p_Other[ 4 ] + Copy[ 5 ]*p_Other[ 5 ]
				+ Copy[ 9 ]*p_Other[ 6 ] + Copy[ 13 ]*p_Other[ 7 ];
		m_M[ 6 ] = Copy[ 2 ]*p_Other[ 4 ] + Copy[ 6 ]*p_Other[ 5 ]
				+ Copy[ 10 ]*p_Other[ 6 ] + Copy[ 14 ]*p_Other[ 7 ];
		m_M[ 7 ] = Copy[ 3 ]*p_Other[ 4 ] + Copy[ 7 ]*p_Other[ 5 ]
				+ Copy[ 11 ]*p_Other[ 6 ] + Copy[ 15 ]*p_Other[ 7 ];


		m_M[ 8 ] = Copy[ 0 ]*p_Other[ 8 ] + Copy[ 4 ]*p_Other[ 9 ]
				+ Copy[ 8 ]*p_Other[ 10 ] + Copy[ 12 ]*p_Other[ 11 ];
		m_M[ 9 ] = Copy[ 1 ]*p_Other[ 8 ] + Copy[ 5 ]*p_Other[ 9 ]
				+ Copy[ 9 ]*p_Other[ 10 ] + Copy[ 13 ]*p_Other[ 11 ];
		m_M[ 10 ] = Copy[ 2 ]*p_Other[ 8 ] + Copy[ 6 ]*p_Other[ 9 ]
				+ Copy[ 10 ]*p_Other[ 10 ] + Copy[ 14 ]*p_Other[ 11 ];
		m_M[ 11 ] = Copy[ 3 ]*p_Other[ 8 ] + Copy[ 7 ]*p_Other[ 9 ]
				+ Copy[ 11 ]*p_Other[ 10 ] + Copy[ 15 ]*p_Other[ 11 ];

		m_M[ 12 ] = Copy[ 0 ]*p_Other[ 12 ] + Copy[ 4 ]*p_Other[ 13 ]
				+ Copy[ 8 ]*p_Other[ 14 ] + Copy[ 12 ]*p_Other[ 15 ];
		m_M[ 13 ] = Copy[ 1 ]*p_Other[ 12 ] + Copy[ 5 ]*p_Other[ 13 ]
				+ Copy[ 9 ]*p_Other[ 14 ] + Copy[ 13 ]*p_Other[ 15 ];
		m_M[ 14 ] = Copy[ 2 ]*p_Other[ 12 ] + Copy[ 6 ]*p_Other[ 13 ]
				+ Copy[ 10 ]*p_Other[ 14 ] + Copy[ 14 ]*p_Other[ 15 ];
		m_M[ 15 ] = Copy[ 3 ]*p_Other[ 12 ] + Copy[ 7 ]*p_Other[ 13 ]
				+ Copy[ 11 ]*p_Other[ 14 ] + Copy[ 15 ]*p_Other[ 15 ];

		return *this;
	}

	Matrix4x4 &Matrix4x4::operator*=( const BD_FLOAT32 p_Scalar )
	{
		for( BD_MEMSIZE i = 0; i < 16; ++i )
		{
			m_M[ i ] *= p_Scalar;
		}

		return *this;
	}

	BD_FLOAT32 &Matrix4x4::operator( )( const BD_MEMSIZE p_Row,
		const BD_MEMSIZE p_Column )
	{
		return ( m_M[ p_Row+( p_Column*4 ) ] );
	}

	BD_FLOAT32 Matrix4x4::operator( )( const BD_MEMSIZE p_Row,
		const BD_MEMSIZE p_Column ) const
	{
		return ( m_M[ p_Row+( p_Column*4 ) ] );
	}
}

