#include <Font.hpp>
#include <System.hpp>
#include <Matrix4x4.hpp>
#include <Debugger.hpp>

namespace BD
{

	BD_UCHAR8 Font::s_DefaultCharset[] =
	{
		// Printable characters in ASCII range
		0x09, 0x0A, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,
		0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
		0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
		0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
		0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,
		0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D,
		0x7E,

		// Printable characters in extended ASCII range
		0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
		0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
		0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
		0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
		0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
		0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,

		// To make it a valid string
		0x00
	};

	Font::Font( Renderer & p_Renderer ) :
		m_Loaded( BD_FALSE ),
		m_Renderer( p_Renderer ),
		m_FreeTypeLibrary( BD_NULL ),
		m_FreeTypeFace( BD_NULL ),
		m_Size( 0 ),
		m_pVertexObject( BD_NULL ),
		m_pTexture( BD_NULL ),
		m_pShaderProgram( BD_NULL ),
		m_pVertexShader( BD_NULL ),
		m_pFragmentShader( BD_NULL )
	{

		// Set all the glyps to NULL
		for( BD_MEMSIZE i = 0; i < 256; i++ )
		{
			m_pGlyphs[i] = BD_NULL;
		}

	}

	Font::~Font( )
	{
		Unload( );
	}

	BD_UINT32 Font::Load( char * p_pFileName, BD_UINT32 p_Size, BD_BOOL p_Monochrome )
	{
		// Make sure the font is not created yet.
		if ( m_Loaded == BD_TRUE )
		{
			bdTrace( BD_NULL, "[BD::Font::Read] <ERROR> "
				"The font is already loaded.\n");
			return BD_ERROR;
		}

		// Make sure the font size is larger than 0
		if( ( m_Size = p_Size ) == 0 )
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"The size is 0.\n" );
			return BD_ERROR;
		}


		FT_Error FTError = 0;

		// Initialize the freetype library.
		if ( ( FTError = FT_Init_FreeType( &m_FreeTypeLibrary ) ) != 0 )
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Failed to initialize the FreeType library, error code: %i\n", FTError );
		}
		
		// Create a new font face.
		if ( ( FTError = FT_New_Face( m_FreeTypeLibrary, p_pFileName, 0, &m_FreeTypeFace ) ) != 0)
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Failed to load font: %s, FreeType error: %i\n", p_pFileName, FTError );
			return BD_ERROR;
		}

		// Setup the font size
		///								  FontFace, 0, p_Size  <-- TEST THIS
		if( ( FTError = FT_Set_Pixel_Sizes( m_FreeTypeFace, p_Size, p_Size ) ) != 0)
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Can not setup the font size, FreeType error: %i\n", FTError );
			return BD_ERROR;
		}

		// Select the unicode character map
		if( ( FTError = FT_Select_Charmap( m_FreeTypeFace, FT_ENCODING_UNICODE ) ) != 0)
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Can not select the unicode character map, FreeType error: %i\n", FTError );
			return BD_ERROR;
		}


		// Preparing for looping through all our glyphs in our default character set.
		BD_UCHAR8 * CharSet = s_DefaultCharset;
		GlyphRowVector GlyphRows;
		Vector3 TextureSize( 0, 0, 0 );
		Vector3 CurrentRowSize( 0, 0, 0 );
		FT_BitmapGlyph FTBitmapGlyph = BD_NULL;
		BD_UINT32 TotalGlyphs = 0;
		FT_Glyph_Metrics CurMetrics;
		BD_BOOL LoopingGlyphs = BD_TRUE;

		// Set the monochrome mode which is going to be used when we create
		// characters with freetype.
		FT_Int32 MonochromeMode = 0;
		if( p_Monochrome == BD_TRUE )
		{
			MonochromeMode = FT_LOAD_MONOCHROME;
		}
		
		// Let's loop our glyphs we want.
		while( TotalGlyphs < 255 )
		{
			CurrentRowSize[ 0 ] = 0;
			TextureGlyphRowStruct TextureGlyphRow;
			BD_BOOL LoadedAnyRowGlyphs = BD_FALSE;

			// Loop 16 glyphs(one row of glyphs). 16 * 16 = 256
			for( int i = 0; i < 16; i++)
			{
				BD_UCHAR8 CurChar = *CharSet;
				// Make sure the current glyph isn't allocated,
				// it is already added to the font class if it is.
				// Then continue the loading of the other glyphs.
				if( m_pGlyphs[ CurChar ] != BD_NULL )
				{
					CharSet++;
					continue;
				}

				// Make sure we want to keep on looping or
				// stop the glyph loader if the current character is 0
				if( LoopingGlyphs == BD_FALSE || CurChar == 0x00 )
				{
					LoopingGlyphs = BD_FALSE;
					break;
				}

				// checking Glyph availability
				//if( FT_Load_Glyph( m_FreeTypeFace, FT_Get_Char_Index( m_FreeTypeFace, CurChar ), FT_LOAD_DEFAULT ) )
				if( FT_Get_Char_Index( m_FreeTypeFace, CurChar ) == 0 )
				{
					CharSet++;
					continue;
				}

				// Size we passed the last check, we now have at least 1 glyph on this row.
				LoadedAnyRowGlyphs = BD_TRUE;

				// Load the glyph corresponding to the current character
				if( ( FTError = FT_Load_Char( m_FreeTypeFace, CurChar, FT_LOAD_RENDER | MonochromeMode ) ) != 0)
				{
					bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
						"Can not load the character '%c'(%i), FreeType error: %i\n",
						CurChar, (int)CurChar, FTError );
					return BD_ERROR;
				}

				// Get the metrics for this glyph
				CurMetrics = m_FreeTypeFace->glyph->metrics;

				// Get the FreeType glypth
				FT_Glyph FTGlyph;
				if( ( FTError = FT_Get_Glyph( m_FreeTypeFace->glyph, &FTGlyph ) ) != 0)
				{
					bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
						"Can not get the glyph, FreeType error: %i\n", FTError );
					return BD_ERROR;
				}

				// Create the FreeType bitmap
				FT_Glyph_To_Bitmap( &FTGlyph, FT_RENDER_MODE_NORMAL, 0, 1 );
				FTBitmapGlyph = (FT_BitmapGlyph)FTGlyph;
				/// Get the Mipmap to get the glyphs size. ( FIX THUIS?! WE HAVE THE METRICS NOW?!)
				FT_Bitmap & Bitmap	= FTBitmapGlyph->bitmap;

				// Increment the row width
				CurrentRowSize[ 0 ] += Bitmap.width;

				// Check if this characters height is bigger than the other glyphs on this row.
				if( Bitmap.rows > CurrentRowSize[ 1 ] )
				{
					CurrentRowSize[ 1 ] = Bitmap.rows;
				}

				// Push back the freetype data to the texture glyph row structure.
				GlypthInRowStruct GlypthInRow;
				GlypthInRow.FTGlyph = FTBitmapGlyph;
				GlypthInRow.Metrics = CurMetrics;

				// Add the GlypthInRow struct to the TextureGlyphRow's BitMapGlyphs vector.
				TextureGlyphRow.BitMapGlyphs.push_back(
					std::pair< BD_UCHAR8, GlypthInRowStruct >( CurChar, GlypthInRow ) );
				
				// Allocate this glyph in the Font class
				m_pGlyphs[ CurChar ] = new BD::Glyph;
				m_pGlyphs[ CurChar ]->Index = TotalGlyphs;
				m_pGlyphs[ CurChar ]->Advance = CurMetrics.horiAdvance / 64.0f;

				// Move to the next character in the charset.
				// Increment the loops counter(used to make sure we don't loop more than 255 glyphs)
				CharSet++;
				TotalGlyphs++;
			}

			// Make sure we break the loop if we don't want to loop anymore
			if( LoopingGlyphs == BD_FALSE )
			{
				break;
			}

			// Increment the textures total height if we loaded any glyphs
			if( LoadedAnyRowGlyphs )
			{
				TextureSize[ 1 ] += CurrentRowSize[ 1 ];
			}

			// Check if the last row is wider than the TextureWidth
			// Then this is the width of the texture we are going to use.
			if( CurrentRowSize[ 0 ] > TextureSize[ 0 ] )
			{
				TextureSize[ 0 ] = CurrentRowSize[ 0 ];
			}

			// Set the last row data and push it to the Glypth row map
			TextureGlyphRow.RowSize = CurrentRowSize;
			GlyphRows.push_back( TextureGlyphRow );

		}


		// Now it's time to use our glyph rows and loop through them all.
		// Then we grab every single glyph in that row and use it's data.
		// Every single glyph contain data about the bitmap and such,
		// This applied to the texture and the vertex object begin used
		// for drawing.

		// Create a buffer holding 
		BD_BYTE * pPixelBuffer = new BD_BYTE[ TextureSize[ 0 ] * TextureSize[ 1 ] * 4];
		memset( pPixelBuffer, 0, ( TextureSize[ 0 ] * TextureSize[ 1 ] * 4 ) ); 

		// Create two buffers holding vertex and texture coordinates
		// Those are generated in the LoadFontPixelData[X] function, to gain performance
		BD_FLOAT32 * pVertexCoords = new BD_FLOAT32[ TotalGlyphs * 18 ];
		BD_FLOAT32 * pTextureCoords = new BD_FLOAT32[ TotalGlyphs * 12 ];

		if( !p_Monochrome )
		{
			LoadGlyphs( pPixelBuffer, TextureSize, &GlyphRows, pVertexCoords, pTextureCoords );
		}
		else
		{
			LoadGlyphsMonochrome( pPixelBuffer, TextureSize, &GlyphRows, pVertexCoords, pTextureCoords );
		}

		// Create the Vertex object
		m_pVertexObject = m_Renderer.CreateVertexObject();
		BD_UINT32 VertexBufferIndex = 0;
		m_pVertexObject->AddVertexBuffer( pVertexCoords, 3, VertexBufferIndex );
		m_pVertexObject->AddVertexBuffer( pTextureCoords, 2, VertexBufferIndex );
		// Load the vertex object.
		if( m_pVertexObject->Load( TotalGlyphs * 2, 3 ) != BD_OK )
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Can not load the vertex object.\n" );
			// Make sure to delete everythink that's temporary allocated.
			delete [] pVertexCoords;
			delete [] pTextureCoords;
			delete [] pPixelBuffer;
			return BD_ERROR;
		}

		// Delete the buffers holding vertex and texture coordinates
		delete [] pVertexCoords;
		delete [] pTextureCoords;

		// Create the texture and load it, set the filters as well.
		m_pTexture = m_Renderer.CreateTexture( );
		if( m_pTexture->Load( TextureSize[ 0 ], TextureSize[ 1 ],
			Texture::PIXEL_FORMAT_RGBA, pPixelBuffer ) != BD_OK)
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Can not load the texture.\n");
			delete [] pPixelBuffer;
			return BD_ERROR;
		}
		// Set texture filters
		Texture::eFilter TextureFilters[ ] =
		{
			Texture::FILTER_MAG,		Texture::FILTER_NEAREST,
			Texture::FILTER_MIN,		Texture::FILTER_NEAREST,
			Texture::FILTER_WRAP_X,		Texture::FILTER_CLAMP,	// Clamp is useful for characters
			Texture::FILTER_WRAP_Y,		Texture::FILTER_CLAMP,	// I think it might get rid of flickering in some cases
			
			Texture::FILTER_NONE, Texture::FILTER_NONE
		};
		m_pTexture->SetFilters( TextureFilters );

		// Delete the pixel data
		delete [] pPixelBuffer;


		// The texture and the vertex is created, finally.
		// Now just load the shaders
		if( LoadShaders() != BD_OK )
		{
			bdTrace( BD_NULL, "[BD::Font::Load] <ERROR> "
				"Can not load the shaders.\n" );
			return BD_ERROR;
		}

		// We are done! 
		m_Loaded = BD_TRUE;
		return BD_OK;
	}

	void Font::Render( std::string p_String, Vector3 p_Position,
		BD_FLOAT32 p_Scale, Vector3 p_Color, BD_FLOAT32 p_Alpha )
	{
		if( m_Loaded == BD_FALSE )
		{
			return;
		}

		// Bind the shader and set uniforms
		m_pShaderProgram->Bind( );
		m_pShaderProgram->SetUniform1f( "Scale", p_Scale );
		m_pShaderProgram->SetUniform4f( "Color", p_Color[ 0 ], p_Color[ 1 ], p_Color[ 2 ], p_Alpha );

		// Bind the texture
		m_pTexture->Bind(0);

		Vector3 GlyphPosition = p_Position;

		// Loop every character we want to render
		for( BD_MEMSIZE i = 0; i < p_String.size(); i++ )
		{
			BD_UCHAR8 CurChar = static_cast< BD_UCHAR8 >( p_String[ i ] );
			Glyph * pGlyph = m_pGlyphs[ CurChar ];
			
			// Make sure the glyph isn't NULL
			// (It is if it's not loaded.)
			if( pGlyph == BD_NULL )
			{
				continue;
			}

			switch( CurChar )
			{
			case ' ':
				GlyphPosition[ 0 ] += ( pGlyph->Advance * p_Scale );
				continue;
			case '\n':
				GlyphPosition[ 0 ] = p_Position[ 0 ];
				GlyphPosition[ 1 ] -= ( m_Size * p_Scale );
				continue;
			case '\t':
				GlyphPosition[ 0 ] += ( m_Size * 3 *  p_Scale );
				continue;
			};

			// Set the glyphs position
			m_pShaderProgram->SetUniform3f( "VertexPosition",
					GlyphPosition[ 0 ],
					GlyphPosition[ 1 ],
					GlyphPosition[ 2 ] );
			m_pVertexObject->RenderParts( VertexObject::RENDERMODE_TRIANGLES, pGlyph->Index * 6, 6 );

			GlyphPosition[ 0 ] += ( pGlyph->Advance * p_Scale );

		}

		m_pTexture->Unbind();
		m_pShaderProgram->Unbind( );

	}

	void Font::Unload( )
	{
		m_Loaded = BD_FALSE;

		for( BD_MEMSIZE i = 0; i < 256; i++ )
		{
			if( m_pGlyphs[i] )
			{
				delete m_pGlyphs[i];
				m_pGlyphs[i] = BD_NULL;
			}
		}

		if( m_pVertexObject )
		{
			delete m_pVertexObject;
			m_pVertexObject = BD_NULL;
		}
		if( m_pTexture )
		{
			delete m_pTexture;
			m_pTexture = BD_NULL;
		}
		if( m_pShaderProgram )
		{
			delete m_pShaderProgram;
			m_pShaderProgram = BD_NULL;
		}
		if( m_pVertexShader )
		{
			delete m_pVertexShader;
			m_pVertexShader = BD_NULL;
		}
		if( m_pFragmentShader )
		{
			delete m_pFragmentShader;
			m_pFragmentShader = BD_NULL;
		}
		if( m_FreeTypeLibrary )
		{
			FT_Done_FreeType( m_FreeTypeLibrary );
		}

	}

	void Font::LoadGlyphs( BD_BYTE * p_pPixelBuffer, const Vector3 p_Size,
			GlyphRowVector * p_pGlyphRows, BD_FLOAT32 * p_pVertexCoords, BD_FLOAT32 * p_pTextureCoords )
	{
		BD_UINT32 GlyphsLooped = 0;
		BD_UINT32 BitmapPosY = 0;

		// Loop through all the glyph rows
		for( GlyphRowVector::iterator it = p_pGlyphRows->begin(); it != p_pGlyphRows->end(); it++ )
		{
			BD_UINT32 BitmapPosX = 0;

			// Loop all the glyphs for this row
			for( BD_MEMSIZE i = 0; i < it->BitMapGlyphs.size(); i++ )
			{
				FT_BitmapGlyph BitmapGlyph = it->BitMapGlyphs[i].second.FTGlyph;
				FT_Bitmap & Bitmap	= BitmapGlyph->bitmap;
				BD_UCHAR8 * Pixels = Bitmap.buffer;
				Vector3 BitmapSize( Bitmap.width, Bitmap.rows, 0 );
				int px = 0;
				int py = BitmapSize[ 1 ] - 1;
				int cx = BitmapPosX;
				int cy = 0;

				// Loop the pixel, X ad Y coords
				for (py = BitmapSize[ 1 ] - 1; py >= 0; py--)
				{
					cy = (BitmapPosY * p_Size[ 0 ]);
					for (px = 0, cx = BitmapPosX; px < BitmapSize[ 0 ]; ++px, ++cx )
					{
						BD_MEMSIZE Index = cy + ( py * p_Size[ 0 ] ) + cx;
						p_pPixelBuffer[Index * 4 + 0] = 255;
						p_pPixelBuffer[Index * 4 + 1] = 255;
						p_pPixelBuffer[Index * 4 + 2] = 255;
						p_pPixelBuffer[Index * 4 + 3] = Pixels[px];
					}
					Pixels += Bitmap.pitch;
				}

				// Create the vertex data for this glyph
				CreateGlyphVertexData( p_pVertexCoords, p_pTextureCoords, p_Size,
					GlyphsLooped, &Bitmap, &BitmapGlyph, Vector3( BitmapPosX, BitmapPosY, 0 ) );

				// The glyph is done, let's move to the next one.
				BitmapPosX += BitmapSize[ 0 ];
				GlyphsLooped++;
			}

			// The row is done, let's move to the next row's position
			BitmapPosY += it->RowSize[ 1 ];
		}

	}

	void Font::LoadGlyphsMonochrome( BD_BYTE * p_pPixelBuffer, const Vector3 p_Size,
			GlyphRowVector * p_pGlyphRows, BD_FLOAT32 * p_pVertexCoords, BD_FLOAT32 * p_pTextureCoords )
	{
		BD_UINT32 GlyphsLooped = 0;
		BD_UINT32 BitmapPosY = 0;

		// Loop through all the glyph rows
		for( GlyphRowVector::iterator it = p_pGlyphRows->begin(); it != p_pGlyphRows->end(); it++ )
		{
			BD_UINT32 BitmapPosX = 0;

			// Loop all the glyphs for this row
			for( BD_MEMSIZE i = 0; i < it->BitMapGlyphs.size(); i++ )
			{

				FT_BitmapGlyph BitmapGlyph = it->BitMapGlyphs[i].second.FTGlyph;
				FT_Bitmap & Bitmap	= BitmapGlyph->bitmap;
				BD_UCHAR8 * Pixels = Bitmap.buffer;
				Vector3 BitmapSize( Bitmap.width, Bitmap.rows, 0 );

				BD_UCHAR8 d = 0, *s = Pixels;
				BD_UCHAR8 * row = s;
				for( int y = 0; y < BitmapSize[ 1 ]; y++ )
				{
					int n = 0; // Bit counter ( 0 - 7 )
					s = row;

					for( int x = 0; x < BitmapSize[ 0 ]; x++ )
					{
						// Move and get the current byte
						if (n == 0)
						{
							d = *s++;
						}
	
						// Get the bit
						BD_UCHAR8 Alpha = 0;
						if ( bdCheckBit( d, (7 - n) ) )
						{
							Alpha = 1;
						}

						// Increase the bit counter
						// Also make sure it's reseted if it's == 8
						if ( ++n == (int) 8) 
						{
							n = 0;
						}

						BD_UINT32 InvertexY = Bitmap.rows - y - 1;
						BD_UINT32 Index = ( BitmapPosY * p_Size[ 0 ] ) + ( InvertexY * p_Size[ 0 ]) + ( BitmapPosX + x );
						p_pPixelBuffer[Index * 4 + 0] = 255;
						p_pPixelBuffer[Index * 4 + 1] = 255;
						p_pPixelBuffer[Index * 4 + 2] = 255;
						p_pPixelBuffer[Index * 4 + 3] = Alpha * 255;

					}

					row += Bitmap.pitch;
				}
				
				// Create the vertex data for this glyph
				CreateGlyphVertexData( p_pVertexCoords, p_pTextureCoords, p_Size,
					GlyphsLooped, &Bitmap, &BitmapGlyph, Vector3( BitmapPosX, BitmapPosY, 0 ) );
			

				// The glyph is done, let's move to the next one
				GlyphsLooped++;
				BitmapPosX += Bitmap.width;
			}

			// The row is done, let's move to the next row's position
			BitmapPosY += it->RowSize[ 1 ];
		}
	
	}

	void Font::CreateGlyphVertexData( BD_FLOAT32 * p_pVertexCoords, BD_FLOAT32 * p_pTextureCoords, Vector3 p_TextureSize,
			BD_UINT32 p_Index, FT_Bitmap * p_pBitmap, FT_BitmapGlyph * p_pGLyph, Vector3 p_GLyphPosition )
	{

				// Let's create the vertex coordinates
				BD_UINT32 VertStartIndex = p_Index * 18;
				BD_UINT32 TexStartIndex = p_Index * 12;
				Vector3 VertCoLow( 0, ( (*p_pGLyph)->top - p_pBitmap->rows ), 0 );
				Vector3 VertCoHigh( p_pBitmap->width, (*p_pGLyph)->top, 0 );

				p_pVertexCoords[ VertStartIndex + 0] = VertCoLow[ 0 ];
				p_pVertexCoords[ VertStartIndex + 1] = VertCoLow[ 1 ];
				p_pVertexCoords[ VertStartIndex + 2] = 0;

				p_pVertexCoords[ VertStartIndex + 3] = VertCoHigh[ 0 ];
				p_pVertexCoords[ VertStartIndex + 4] = VertCoLow[ 1 ];
				p_pVertexCoords[ VertStartIndex + 5] = 0;

				p_pVertexCoords[ VertStartIndex + 6] = VertCoHigh[ 0 ];
				p_pVertexCoords[ VertStartIndex + 7] = VertCoHigh[ 1 ];
				p_pVertexCoords[ VertStartIndex + 8] = 0;

				p_pVertexCoords[ VertStartIndex + 9] = VertCoLow[ 0 ];
				p_pVertexCoords[ VertStartIndex + 10] = VertCoLow[ 1 ];
				p_pVertexCoords[ VertStartIndex + 11] = 0;

				p_pVertexCoords[ VertStartIndex + 12] = VertCoHigh[ 0 ];
				p_pVertexCoords[ VertStartIndex + 13] = VertCoHigh[ 1 ];
				p_pVertexCoords[ VertStartIndex + 14] = 0;

				p_pVertexCoords[ VertStartIndex + 15] = VertCoLow[ 0 ];
				p_pVertexCoords[ VertStartIndex + 16] = VertCoHigh[ 1 ];
				p_pVertexCoords[ VertStartIndex + 17] = 0;



				// Calculate the coordinates for for glyph
				Vector3 TexCoLow( 0, 0, 0 );
				TexCoLow[ 0 ] = static_cast<BD_FLOAT32>( p_GLyphPosition[ 0 ] ) /
					  static_cast<BD_FLOAT32>( p_TextureSize[ 0 ] );
				TexCoLow[ 1 ] = static_cast<BD_FLOAT32>( p_GLyphPosition[ 1 ] ) /
					  static_cast<BD_FLOAT32>( p_TextureSize[ 1 ] );

				Vector3 TexCoHigh( 0, 0, 0 );
				TexCoHigh[ 0 ] = static_cast<BD_FLOAT32>( p_GLyphPosition[ 0 ] + p_pBitmap->width ) /
					  static_cast<BD_FLOAT32>( p_TextureSize[ 0 ] );
				TexCoHigh[ 1 ] = static_cast<BD_FLOAT32>( p_GLyphPosition[ 1 ] + p_pBitmap->rows ) /
						  static_cast<BD_FLOAT32>( p_TextureSize[ 1 ] );


				p_pTextureCoords[ TexStartIndex + 0] = TexCoLow[ 0 ];
				p_pTextureCoords[ TexStartIndex + 1] = TexCoLow[ 1 ];

				p_pTextureCoords[ TexStartIndex + 2] = TexCoHigh[ 0 ];
				p_pTextureCoords[ TexStartIndex + 3] = TexCoLow[ 1 ];

				p_pTextureCoords[ TexStartIndex + 4] = TexCoHigh[ 0 ];
				p_pTextureCoords[ TexStartIndex + 5] = TexCoHigh[ 1 ];
		
				p_pTextureCoords[ TexStartIndex + 6] = TexCoLow[ 0 ];
				p_pTextureCoords[ TexStartIndex + 7] = TexCoLow[ 1 ];
			
				p_pTextureCoords[ TexStartIndex + 8] = TexCoHigh[ 0 ];
				p_pTextureCoords[ TexStartIndex + 9] = TexCoHigh[ 1 ];
				
				p_pTextureCoords[ TexStartIndex + 10] = TexCoLow[ 0 ];
				p_pTextureCoords[ TexStartIndex + 11] = TexCoHigh[ 1 ];
		
	}


	BD_UINT32 Font::LoadShaders( )
	{
		// Create the shaders
		m_pVertexShader = m_Renderer.CreateShader( Shader::SHADERTYPE_VERTEX );
		m_pFragmentShader = m_Renderer.CreateShader( Shader::SHADERTYPE_FRAGMENT );

		std::string VertexSource =
			"#version 330 \n"
			"precision highp float; \n"

			"in vec3 Position; \n"
			"in vec2 Texture; \n"
			"out vec2 out_Texture; \n"
			"uniform mat4 Matrix; \n"
			"uniform float Scale; \n"
			"uniform vec3 VertexPosition; \n"

			"void main(void) \n"
			"{ \n"
			"	gl_Position = Matrix * vec4( ( Position * Scale ) + VertexPosition, 1.0); \n"
			"	out_Texture = Texture; \n"
			"} \n";

		std::string FragmentSource =
			"#version 330 \n"
			"precision highp float; \n"

			"in vec2 out_Texture; \n"
			"out vec4 out_Color; \n"

			"uniform sampler2D Texture; \n"
			"uniform vec4 Color; \n"

			"void main(void) \n"
			"{ \n"
			"	vec4 TexureColor = texture2D( Texture, out_Texture ); \n"
				
			"	if(TexureColor .a == 0.0) \n"
			"	{ \n"
			"		discard; \n"
			"	} \n"
				
			"	out_Color = TexureColor * Color; \n"
			"} \n";


		m_pVertexShader->SetSource( VertexSource );
		m_pFragmentShader->SetSource( FragmentSource );

		// compile the shaders
		std::string ShaderValidation = "";
		if( m_pVertexShader->Compile( ShaderValidation ) != BD_OK )
		{
			bdTrace( BD_NULL, "[BD::Font::LoadShaders] <ERROR> "
				"Vertex shader compilation failed: %s\n", ShaderValidation.data( ) );
			return BD_ERROR;
		}
		if( m_pFragmentShader->Compile( ShaderValidation ) != BD_OK )
		{
			bdTrace( BD_NULL, "[BD::Font::LoadShaders] <ERROR> "
				"Fragment shader compilation failed: %s\n", ShaderValidation.data( ) );
			return BD_ERROR;
		}

		
		// Load the shader program
		m_pShaderProgram = m_Renderer.CreateShaderProgram( );
		if( m_pShaderProgram->Load( ) != BD_OK )
		{
			bdTrace( NULL, "[BD::Font::LoadShaders] <ERROR> "
				"Can not load the shader program.\n" );
			return BD_ERROR;
		}
		m_pShaderProgram->AttachShaders( m_pVertexShader );
		m_pShaderProgram->AttachShaders( m_pFragmentShader );

		// Let's set the attribute values before we continue the shader
		// program linking
		m_pShaderProgram->SetAttributeLocation( "Position", 0 );
		m_pShaderProgram->SetAttributeLocation( "Texture", 1 );

		std::string ShaderProgramValidation = "";
		if( m_pShaderProgram->Link( ShaderProgramValidation ) != BD_OK )
		{
			bdTrace( NULL, "[BD::Font::LoadShaders] <ERROR> "
				"Shader program shader validation:\n" );
			bdTrace( NULL, "%s", ShaderProgramValidation.data() );
			return BD_ERROR;
		}

		// Set uniforms
		Vector3 WindowSize = m_Renderer.GetViewPortSize( );
		Matrix4x4 Matrix;
		Matrix.Orthographic( 0, WindowSize[ 0 ], 0, WindowSize[ 1 ], -1.0f, 1.0f );

		m_pShaderProgram->Bind( );
		m_pShaderProgram->SetUniform1i( "Texture", 0 );
		m_pShaderProgram->SetUniform4f( "Color", 1.0f, 0.0f, 1.0f, 1.0f );
		m_pShaderProgram->SetUniform3f( "VertexPosition", 0, 0, 0.0f );
		m_pShaderProgram->SetUniformMatrix4x4f( "Matrix", Matrix );
		m_pShaderProgram->Unbind( );

		return BD_OK;
	}



}