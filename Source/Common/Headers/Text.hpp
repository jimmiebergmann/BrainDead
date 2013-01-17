#ifndef __BIT_GRAPHICS_TEXT_HPP__
#define __BIT_GRAPHICS_TEXT_HPP__

#include <Font.hpp>

namespace BD
{

	class Text
	{

	public:

		Text( Font * p_pFont );
		void Render( );
		BD_INLINE void SetString( std::string p_String ) { m_String = p_String; }
		BD_INLINE void SetPosition( Vector3 p_Position ) { m_Position = p_Position; }
		BD_INLINE void SetAlpha( BD_FLOAT32 p_Alpha ) { m_Alpha = p_Alpha; }
		BD_INLINE void SetColor( Vector3 p_Color ) { m_Color = p_Color; }
		BD_INLINE void SetScale( BD_UINT32 p_Scale ) { m_Scale = p_Scale; }
		
	private:

		std::string m_String;
		Vector3 m_Position;
		Vector3 m_Color;
		BD_FLOAT32 m_Alpha;
		BD_UINT32 m_Scale;
		Font * m_pFont;
		
	};

}

#endif