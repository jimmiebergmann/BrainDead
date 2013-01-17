#ifndef __BRAINDEAD_VECTOR2_HPP__
#define __BRAINDEAD_VECTOR2_HPP__

#include <DataTypes.hpp>

namespace BD
{
	class Vector2
	{
	public:
		BD_EXPLICIT Vector2( const BD_FLOAT32 p_X, const  BD_FLOAT32 p_Y );
		BD_INLINE ~Vector2( ){ }

		void Zero( );
		BD_BOOL IsZero( ) const;
		void Clean( );
	
		void Normalise( );

		BD_FLOAT32 Magnitude( ) const;
		BD_FLOAT32 MagnitudeSq( ) const;

		BD_FLOAT32 Distance( const Vector2 &p_Other ) const;
		BD_FLOAT32 DistanceSq( const Vector2 &p_Other ) const;

		BD_FLOAT32 Dot( const Vector2 &p_Other ) const;
		BD_INLINE Vector2 Perpendicular( ) const
			{ return Vector2( -m_V[ 1 ], m_V[ 0 ] ); }
		BD_FLOAT32 PerpendicularDot( const Vector2 &p_Other ) const;
	
		Vector2 &operator=( const Vector2 &p_Other );
		BD_BOOL operator==( const Vector2 &p_Other ) const;
		BD_BOOL operator!=( const Vector2 &p_Other ) const;

		Vector2 operator+( const Vector2 &p_Other ) const;
		Vector2 operator-( const Vector2 &p_Other ) const;
		Vector2 operator*( const Vector2 &p_Other ) const;
		Vector2 operator*( const BD_FLOAT32 p_Scalar ) const;
		Vector2 operator/( const BD_FLOAT32 p_Scalar ) const;
		
		Vector2 &operator+=( const Vector2 &p_Other );
		Vector2 &operator-=( const Vector2 &p_Other );
		Vector2 &operator*=( const Vector2 &p_Other );
		Vector2 &operator*=( const BD_FLOAT32 p_Scalar );
		Vector2 &operator/=( const BD_FLOAT32 p_Scalar );

		// Accessors
		BD_INLINE BD_FLOAT32 GetX( ) const { return m_V[ 0 ]; }
		BD_INLINE BD_FLOAT32 GetY( ) const { return m_V[ 1 ]; }

		BD_INLINE BD_FLOAT32 operator[ ]( const BD_MEMSIZE p_Index ) const
			{ return m_V[ p_Index ]; }

		// Manipulators
		BD_INLINE void Set( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y )
			{ m_V[ 0 ] = p_X; m_V[ 1 ] = p_Y; }
		BD_INLINE void SetX( const BD_FLOAT32 p_X ) { m_V[ 0 ] = p_X; }
		BD_INLINE void SetY( const BD_FLOAT32 p_Y ) { m_V[ 1 ] = p_Y; }

		BD_INLINE BD_FLOAT32 &operator[ ]( const BD_MEMSIZE p_Index )
			{ return m_V[ p_Index ]; }

	private:
		// 0 == X
		// 1 == Y
		BD_FLOAT32 m_V[ 2 ];
	};
}

#endif

