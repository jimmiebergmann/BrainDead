#include <Level.hpp>
#include <Debugger.hpp>

namespace BD
{

	Level::Level( Renderer * p_pRenderer  ) :
		m_pRenderer( p_pRenderer ),
		m_Loaded( BD_FALSE ),
		m_Generated( BD_FALSE ),
		m_pFont( BD_NULL ),
		m_pHealthText( BD_NULL ),
		m_AmmoText( BD_NULL )
	{
	}

	Level::~Level( )
	{
		if( m_pFont )
		{
			delete m_pFont;
			m_pFont = BD_NULL;
		}
		if( m_pHealthText )
		{
			delete m_pHealthText;
			m_pHealthText = BD_NULL;
		}
		if( m_AmmoText )
		{
			delete m_AmmoText;
			m_AmmoText = BD_NULL;
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

		// Load texts
		m_pHealthText = new Text( m_pFont );
		m_pHealthText->SetString( "Health: 100"  );
		m_pHealthText->SetPosition( Vector3( 30, 30, 0 ) );
		m_pHealthText->SetColor( Vector3( 1.0f, 0.0f, 0.0f ) );
		m_pHealthText->SetAlpha( 0.7f );
		m_pHealthText->SetScale( 4 );

		m_AmmoText = new Text( m_pFont );
		m_AmmoText->SetString( "Ammo: 32"  );
		m_AmmoText->SetPosition( Vector3( 560, 30, 0 ) );
		m_AmmoText->SetColor( Vector3( 1.0f, 0.0f, 0.0f ) );
		m_AmmoText->SetAlpha( 0.7f );
		m_AmmoText->SetScale( 4 );


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
		if( m_Loaded != BD_TRUE )
		{
			return BD_ERROR;
		}

		m_pHealthText->Render();
		m_AmmoText->Render();

		return BD_OK;
	}

}