#ifndef __DAWN_MATRIX3X3_HPP__
#define __DAWN_MATRIX3X3_HPP__

#include <DataTypes.hpp>

namespace BD
{
	// Forward-declarations
	class Vector3;
	class Quaternion;

	// The matix is stored in column-major form:
	// 0 3 6
	// 1 4 7
	// 2 5 8

	class Matrix3x3
	{
	public:
		BD_EXPLICIT Matrix3x3( );

		// Set this matrix to the identity matrix
		void Identity( );
		BD_BOOL IsIdentity( ) const;
		BD_BOOL IsZero( ) const;

		// Any near-zero values are to be zeroed
		void Clean( );

		// Access and manipulate the matrix via vectors [both row and column]
		void SetRows( const Vector3 &p_Row1, const Vector3 &p_Row2,
			const Vector3 &p_Row3 );
		void GetRows( Vector3 &p_Row1, Vector3 &p_Row2,
			Vector3 &p_Row3 ) const;
		Vector3 GetRow( const BD_MEMSIZE p_Index ) const;

		void SetColumns( const Vector3 &p_Column1, const Vector3 &p_Column2,
			const Vector3 &p_Column3 );
		void GetColumns( Vector3 &p_Column1, Vector3 &p_Column2,
			Vector3 &p_Column3 ) const;
		Vector3 GetColumn( const BD_MEMSIZE p_Index ) const;

		// Get the matrix as a contiguous array
		BD_INLINE void GetMatrix( BD_FLOAT32 *p_pArray ) const
		{
			for( BD_MEMSIZE i = 0; i < 9; ++i )
			{
				p_pArray[ i ] = m_M[ i ];
			}
		}

		// -- ROTATION OPERATIONS -- //
		// Quaternion rotation
		Matrix3x3 &Rotate( const Quaternion &p_Quaternion );
		// Axis-angle rotation
		Matrix3x3 &Rotate( const Vector3 &p_Axis, const BD_FLOAT32 p_Angle );
		// Euler rotation
		Matrix3x3 &Rotate( const BD_FLOAT32 p_Roll, const BD_FLOAT32 p_Pitch,
			const BD_FLOAT32 p_Yaw );

		// Rotate on an individual axis
		Matrix3x3 &RotateX( const BD_FLOAT32 p_X );
		Matrix3x3 &RotateY( const BD_FLOAT32 p_Y );
		Matrix3x3 &RotateZ( const BD_FLOAT32 p_Z );

		// -- SCALING OPERATIONS -- //
		// Scale on a per-axis basis as defined via a Vector3
		Matrix3x3 &Scale( const Vector3 &p_Scale );
		// Uniformly scale
		Matrix3x3 &Scale( const BD_FLOAT32 p_Scale );
		// Scale each axis individually
		Matrix3x3 &ScaleX( const BD_FLOAT32 p_Scale );
		Matrix3x3 &ScaleY( const BD_FLOAT32 p_Scale );
		Matrix3x3 &ScaleZ( const BD_FLOAT32 p_Scale );

		// Get this matrix as its transpose
		Matrix3x3 &Transpose( );
		// Transpose another matrix using this matrix
		void Transpose( Matrix3x3 &p_Transpose ) const;
		// Transpose this matrix by another matrix
		Matrix3x3 &TransposeOf( const Matrix3x3 &p_Transpose );

		// Get this matrix as its inverse
		Matrix3x3 &Inverse( );
		// Put this matrix's inverse into the parameter
		void Inverse( Matrix3x3 &p_Inverse ) const;
		// Use another matrix's transpose for this matrix
		Matrix3x3 &InverseOf( const Matrix3x3 &p_Inverse );

		BD_FLOAT32 Determinate( ) const;
		Matrix3x3 Adjoint( ) const;

		// The diagonal summed
		BD_FLOAT32 Trace( ) const;

		// Equality
		BD_BOOL operator==( const Matrix3x3 &p_Other ) const;
		BD_BOOL operator!=( const Matrix3x3 &p_Other ) const;

		Matrix3x3 operator+( const Matrix3x3 &p_Other ) const;
		Matrix3x3 operator-( const Matrix3x3 &p_Other ) const;
		Matrix3x3 operator*( const Matrix3x3 &p_Other ) const;
		Matrix3x3 operator*( const BD_FLOAT32 p_Scalar ) const;
		// Column-wise multiplication with a vector
		Vector3 operator*( const Vector3 &p_Vec ) const;

		Matrix3x3 &operator+=( const Matrix3x3 &p_Other );
		Matrix3x3 &operator-=( const Matrix3x3 &p_Other );
		Matrix3x3 &operator*=( const Matrix3x3 &p_Other );
		Matrix3x3 &operator*=( const BD_FLOAT32 p_Scalar );

		// Manipulators
		operator BD_FLOAT32*( ){ return m_M; }
		BD_FLOAT32 &operator( )( const BD_MEMSIZE p_Row,
			const BD_MEMSIZE p_Column );
		BD_FLOAT32 &operator[ ]( const BD_MEMSIZE p_Index )
			{ return m_M[ p_Index ]; }
		BD_FLOAT32 &operator[ ]( const int p_Index )
			{ return m_M[ p_Index ]; }

		// Accessors
		operator const BD_FLOAT32*( ){ return m_M; }
		BD_FLOAT32 operator( )( const BD_MEMSIZE p_Row,
			const BD_MEMSIZE p_Column ) const;
		BD_FLOAT32 operator[ ]( const int p_Index ) const
			{ return m_M[ p_Index ]; }
		BD_FLOAT32 operator[ ]( const BD_MEMSIZE p_Index ) const
			{ return m_M[ p_Index ]; }

		// Unary negation
		Matrix3x3 &operator-( );

	private:
		BD_FLOAT32 m_M[ 9 ];
	};
}

#endif
