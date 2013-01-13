#ifndef __DAWN_VECTOR3_HPP__
#define __DAWN_VECTOR3_HPP__

#include <DataTypes.hpp>

namespace BD
{
	// Forward-declarations
	class Matrix3x3;

	class Vector3
	{
	public:

		BD_EXPLICIT Vector3( );

		BD_EXPLICIT Vector3( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y,
			const BD_FLOAT32 p_Z );
		
		void Zero( );
		void Clean( );

		void Normalise( );

		BD_FLOAT32 Magnitude( ) const;
		BD_FLOAT32 MagnitudeSq( ) const;

		BD_FLOAT32 Distance( const Vector3 &p_Other ) const;
		BD_FLOAT32 DistanceSq( const Vector3 &p_Other ) const;

		BD_FLOAT32 Dot( const Vector3 &p_Other ) const;
		Vector3 Cross( const Vector3 &p_Other ) const;

		BD_BOOL operator==( const Vector3 &p_Other ) const;
		BD_BOOL operator!=( const Vector3 &p_Other ) const;

		Vector3 operator+( const Vector3 &p_Other ) const;
		Vector3 operator-( const Vector3 &p_Other ) const;
		Vector3 operator*( const Vector3 &p_Other ) const;
		Vector3 operator*( const Matrix3x3 &p_Matrix ) const;
		Vector3 operator*( const BD_FLOAT32 p_Scalar ) const;
		
		Vector3 operator/( const BD_FLOAT32 p_Scalar ) const;

		Vector3 &operator+=( const Vector3 &p_Other );
		Vector3 &operator-=( const Vector3 &p_Other );
		Vector3 &operator*=( const Vector3 &p_Other );
		Vector3 &operator*=( const BD_FLOAT32 p_Scalar );
		Vector3 &operator/=( const BD_FLOAT32 p_Scalar );

		// Accessors
		BD_FLOAT32 operator[ ]( const BD_MEMSIZE p_Index ) const
			{ return m_V[ p_Index ]; }

		// Manipulators
		BD_FLOAT32 &operator[ ]( const BD_MEMSIZE p_Index )
			{ return m_V[ p_Index ]; }

	private:
		// 0 == X
		// 1 == Y
		// 2 == Z
		BD_FLOAT32 m_V[ 3 ];
	};
}

#endif
