#ifndef __DAWN_VECTOR4_HPP__
#define __DAWN_VECTOR4_HPP__

#include <DataTypes.hpp>

namespace BD
{
	class Vector4
	{
	public:
		BD_EXPLICIT Vector4( )
			{ m_V[ 0 ] = m_V[ 1 ] = m_V[ 2 ] = m_V[ 3 ] = 0.0f; }
		BD_EXPLICIT Vector4( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y,
			const BD_FLOAT32 p_Z, const BD_FLOAT32 p_W );
		~Vector4( ){ }

		void Normalise( );

		BD_FLOAT32 Magnitude( ) const;
		BD_FLOAT32 MagnitudeSq( ) const;

		BD_FLOAT32 Dot( const Vector4 &p_Other ) const;

		void Set( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y,
			const BD_FLOAT32 p_Z, const BD_FLOAT32 p_W );
		BD_INLINE void SetX( const BD_FLOAT32 p_X ) { m_V[ 0 ] = p_X; }
		BD_INLINE void SetY( const BD_FLOAT32 p_Y ) { m_V[ 1 ] = p_Y; }
		BD_INLINE void SetZ( const BD_FLOAT32 p_Z ) { m_V[ 2 ] = p_Z; }
		BD_INLINE void SetW( const BD_FLOAT32 p_W ) { m_V[ 3 ] = p_W; }

		BD_INLINE BD_FLOAT32 GetX( ) const { return m_V[ 0 ]; }
		BD_INLINE BD_FLOAT32 GetY( ) const { return m_V[ 1 ]; }
		BD_INLINE BD_FLOAT32 GetZ( ) const { return m_V[ 2 ]; }
		BD_INLINE BD_FLOAT32 GetW( ) const { return m_V[ 3 ]; }

		BD_BOOL IsZero( ) const;
		void Zero( );
		void Clean( );

		BD_BOOL operator==( const Vector4 &p_Other ) const;
		BD_BOOL operator!=( const Vector4 &p_Other ) const;

		Vector4 operator-( ) const;

		Vector4 operator+( const Vector4 &p_Other ) const;
		Vector4 operator-( const Vector4 &p_Other ) const;
		Vector4 operator*( const Vector4 &p_Other ) const;
		Vector4 operator*( const BD_FLOAT32 p_Scalar ) const;
		Vector4 operator/( const BD_FLOAT32 p_Scalar ) const;

		Vector4 &operator+=( const Vector4 &p_Other );
		Vector4 &operator-=( const Vector4 &p_Other );
		Vector4 &operator*=( const Vector4 &p_Other );
		Vector4 &operator*=( const BD_FLOAT32 p_Scalar );
		Vector4 &operator/=( const BD_FLOAT32 p_Scalar );

		// Accessor
		BD_FLOAT32 operator[ ]( const BD_MEMSIZE p_Index ) const
			{ return m_V[ p_Index ]; }

		// Manipulator
		BD_FLOAT32 &operator[ ]( const BD_MEMSIZE p_Index )
			{ return m_V[ p_Index ]; }

	private:
		BD_FLOAT32 m_V[ 4 ];
	};
}

#endif

