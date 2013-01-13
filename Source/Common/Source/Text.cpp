#include <Text.hpp>

namespace BD
{

	Text::Text( Font * p_pFont ) :
		m_pFont( p_pFont ) 
	{
	}

	void Text::Render( )
	{
		m_pFont->Render( m_String, m_Position, m_Scale, m_Color, m_Alpha );
	}

}