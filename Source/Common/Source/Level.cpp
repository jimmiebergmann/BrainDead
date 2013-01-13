#include <Level.hpp>
#include <Debugger.hpp>

namespace BD
{

	Level::Level( Renderer * p_pRenderer  ) :
		m_pRenderer( p_pRenderer ),
		m_Loaded( BD_FALSE ),
		m_Generated( BD_FALSE ),
		m_pFont( BD_NULL )
	{
	}

	Level::~Level( )
	{
		if( m_pFont )
		{
			delete m_pFont;
			m_pFont = BD_NULL;
		}
	

		m_Loaded = BD_FALSE;
	}

	BD_UINT32 Level::Load( )
	{
		// Load the font
		m_pFont= new Font( *m_pRenderer );
		if( m_pFont->Load( "Data/Fonts/slkscrb.ttf", 8, BD_TRUE ) != BD_OK )
		{
			bdTrace( BD_NULL, "[Level::Load] <ERROR> Can not load the font.\n" );
			return BD_ERROR;
		}

		m_Loaded = BD_TRUE;
		return BD_OK;
	}

	void Level::Generate( )
	{

		const BD_UINT32 MapSizeX = 40;
		const BD_UINT32 MapSizeY = 20;
		BD_BYTE MapData[ MapSizeX ][ MapSizeY ];
		
		memset( MapData, 0, MapSizeX * MapSizeY );

		for( BD_MEMSIZE y = 0; y < MapSizeY; y++ )
		{
			for( BD_MEMSIZE x = 0; x < MapSizeX; x++ )
			{
				bdTrace( NULL, "%i", static_cast< int >( MapData[ x ][ y ] ) );
			}

			bdTrace( NULL, "\n" );
		}

		m_Generated = BD_TRUE;
	}

	BD_UINT32 Level::Update( BD_FLOAT64 p_DeltaTime )
	{
		
		return BD_OK;
	}

	BD_UINT32 Level::Render( )
	{

		m_pFont->Render( "Test string.", Vector3( 100, 100, 0 ), 4.0f, Vector3( 1.0f, 1.0f, 1.0f ), 0.7f );

		return BD_OK;
	}

}