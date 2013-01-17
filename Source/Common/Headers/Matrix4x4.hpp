#ifndef __BRAINDEAD_MATRIX4X4_HPP__
#define __BRAINDEAD_MATRIX4X4_HPP__

#include <DataTypes.hpp>

namespace BD
{
	// Forward-declarations
	class Vector3;
	class Vector4;
	class Matrix3x3;
	class Quaternion;

	class Matrix4x4
	{
	public:
		BD_EXPLICIT Matrix4x4( ){ this->Identity( ); }
		~Matrix4x4( ){ }

		void Identity( );
		BD_BOOL IsIdentity( ) const;
		BD_BOOL IsZero( ) const;
		BD_FLOAT32 Trace( ) const;

		void Clean( );

		void SetRows( const Vector4 &p_Row1, const Vector4 &p_Row2,
			const Vector4 &p_Row3, const Vector4 &p_Row4 );
		void GetRows( Vector4 &p_Row1, Vector4 &p_Row2, Vector4 &p_Row3,
			Vector4 &p_Row4 ) const;
		Vector4 GetRow( const BD_MEMSIZE p_Index ) const;

		void SetColumns( const Vector4 &p_Column1, const Vector4 &p_Column2,
			const Vector4 &p_Column3, const Vector4 &p_Column4 );
		void GetColumns( Vector4 &p_Column1, Vector4 &p_Column2,
			Vector4 &p_Column3, Vector4 &p_Column4 ) const;
		Vector4 GetColumn( const BD_MEMSIZE p_Index ) const;

		void GetMatrix( BD_FLOAT32 *p_pArray ) const
		{
			for( BD_MEMSIZE i = 0; i < 16; ++i )
			{
				p_pArray[ i ] = m_M[ i ];
			}
		}

		Matrix4x4 &Orthographic( const BD_FLOAT32 p_Left,
			const BD_FLOAT32 p_Right,
			const BD_FLOAT32 p_Bottom, const BD_FLOAT32 p_Top,
			const BD_FLOAT32 p_ZNear, const BD_FLOAT32 p_ZFar );

		Matrix4x4 &Translate( const Vector3 &p_Translation );
		Vector3 Transform( const Vector3 &p_Point ) const;

		Matrix4x4 &Rotate( const Matrix3x3 &p_Rotation );
		Matrix4x4 &Rotate( const Quaternion &p_Quaternion );
		Matrix4x4 &Rotate( const BD_FLOAT32 p_Roll, const BD_FLOAT32 p_Pitch,
			const BD_FLOAT32 p_Yaw );
		Matrix4x4 &Rotate( const Vector3 p_Axis, const BD_FLOAT32 p_Angle );
		Matrix4x4 &RotateX( const BD_FLOAT32 p_X );
		Matrix4x4 &RotateY( const BD_FLOAT32 p_Y );
		Matrix4x4 &RotateZ( const BD_FLOAT32 p_Z );

		Matrix4x4 &Scale( const Vector3 &p_Scale );
		Matrix4x4 &Scale( const BD_FLOAT32 p_Scale );
		Matrix4x4 &ScaleX( const BD_FLOAT32 p_X );
		Matrix4x4 &ScaleY( const BD_FLOAT32 p_Y );
		Matrix4x4 &ScaleZ( const BD_FLOAT32 p_Z );

		Matrix4x4 &Transpose( );
		void Transpose( Matrix4x4 &p_Transpose ) const;
		Matrix4x4 &TransposeOf( const Matrix4x4 &p_Transpose );

		Matrix4x4 &AffineInverse( );
		void AffineInverse( Matrix4x4 &p_AffineInverse ) const;
		Matrix4x4 &AffineInverseOf( const Matrix4x4 &p_AffineInverse );

		BD_BOOL operator==( const Matrix4x4 &p_Other ) const;
		BD_BOOL operator!=( const Matrix4x4 &p_Other ) const;

		Matrix4x4 operator+( const Matrix4x4 &p_Other ) const;
		Matrix4x4 operator-( const Matrix4x4 &p_Other ) const;
		Matrix4x4 &operator-( );
		Matrix4x4 operator*( const Matrix4x4 &p_Other ) const;
		Vector4 operator*( const Vector4 &p_Vec ) const;
		Matrix4x4 operator*( const BD_FLOAT32 p_Scalar ) const;
		
		Matrix4x4 &operator+=( const Matrix4x4 &p_Other );
		Matrix4x4 &operator-=( const Matrix4x4 &p_Other );
		Matrix4x4 &operator*=( const Matrix4x4 &p_Other );
		Matrix4x4 &operator*=( const BD_FLOAT32 p_Scalar );

		// Manipulators
		BD_FLOAT32 &operator( )( const BD_MEMSIZE p_Row,
			const BD_MEMSIZE p_Column );
		BD_FLOAT32 &operator[ ]( const BD_MEMSIZE p_Index )
			{ return m_M[ p_Index ]; }
		BD_FLOAT32 &operator[ ]( const int p_Index )
			{ return m_M[ p_Index ]; }

		// Accessors
		BD_FLOAT32 operator( )( const BD_MEMSIZE p_Row,
			const BD_MEMSIZE p_Column ) const;
		BD_FLOAT32 operator[ ]( const BD_MEMSIZE p_Index ) const 
			{ return m_M[ p_Index ]; }
		BD_FLOAT32 operator[ ]( const int p_Index ) const
			{ return m_M[ p_Index ]; }

	private:
		BD_FLOAT32 m_M[ 16 ];
	};
}

#endif

