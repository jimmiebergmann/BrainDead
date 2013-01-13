#include <Vector2.hpp>

namespace BD
{
	Vector2::Vector2( const BD_FLOAT32 p_X, const BD_FLOAT32 p_Y )
	{
		m_V[ 0 ] = p_X;
		m_V[ 1 ] = p_Y;
	}

	void Vector2::Zero( )
	{
	}

	void Vector2::Clean( )
	{
	}

	void Vector2::Normalise( )
	{
	}

	BD_FLOAT32 Vector2::Magnitude( ) const
	{
		return 1.0f;
	}
	
	BD_FLOAT32 Vector2::MagnitudeSq( ) const
	{
		return 1.0f;
	}
	
	BD_FLOAT32 Vector2::Distance( const Vector2 &p_Other ) const
	{
		return 1.0f;
	}

	BD_FLOAT32 Vector2::DistanceSq( const Vector2 &p_Other ) const
	{
		return 1.0f;
	}

	BD_FLOAT32 Vector2::Dot( const Vector2 &p_Other ) const
	{
		return 1.0f;
	}

	BD_BOOL Vector2::operator==( const Vector2 &p_Other ) const
	{
		return BD_FALSE;
	}

	BD_BOOL Vector2::operator!=( const Vector2 &p_Other ) const
	{
		return BD_FALSE;
	}

	Vector2 Vector2::operator+( const Vector2 &p_Other ) const
	{
		return *this;
	}
	
	Vector2 Vector2::operator-( const Vector2 &p_Other ) const
	{
		return *this;
	}

	Vector2 Vector2::operator*( const Vector2 &p_Other ) const
	{
		return *this;
	}

	Vector2 Vector2::operator*( const BD_FLOAT32 p_Scalar ) const
	{
		return *this;
	}

	Vector2 Vector2::operator/( const BD_FLOAT32 p_Scalar ) const
	{
		return *this;
	}

	Vector2 &Vector2::operator+=( const Vector2 &p_Other )
	{
		return *this;
	}

	Vector2 &Vector2::operator-=( const Vector2 &p_Other )
	{
		return *this;
	}

	Vector2 &Vector2::operator*=( const Vector2 &p_Other )
	{
		return *this;
	}

	Vector2 &Vector2::operator*=( const BD_FLOAT32 p_Scalar )
	{
		return *this;
	}

	Vector2 &Vector2::operator/=( const BD_FLOAT32 p_Scalar )
	{
		return *this;
	}
}

