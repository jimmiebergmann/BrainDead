#ifndef __BRAINDEAD_FRONT_HPP__
#define __BRAINDEAD_FRONT_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
#include <VertexObject.hpp>
#include <Texture.hpp>
#include <ShaderProgram.hpp>
#include <Shader.hpp>
#include <Vector3.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <map>
#include <string>

namespace BD
{
	// Font glypth
	struct Glyph
	{
		BD_FLOAT32 Advance; // Total width of the character
		BD_UCHAR8 Index; // Texture / vertex index.
	};

	// Font class
	class Font
	{

	public:

		Font( Renderer & p_Renderer );
		~Font( );
		BD_UINT32 Load( char * p_pFileName, BD_UINT32 p_Size, BD_BOOL p_Monochrome );
		void Render( std::string p_String, Vector3 p_Position,
			BD_FLOAT32 p_Scale, Vector3 p_Color, BD_FLOAT32 p_Alpha);

	private:

		friend class FontLoader;

		// Private structures
		// strucutre holding data for a glyph in the row data
		struct GlypthInRowStruct
		{
			GlypthInRowStruct() { }
			FT_BitmapGlyph FTGlyph;
			FT_Glyph_Metrics Metrics;
		};


		// Stucture holding data for all glyphs for a row
		struct TextureGlyphRowStruct
		{
			TextureGlyphRowStruct() { }
			typedef std::vector< std::pair< BD_UCHAR8, GlypthInRowStruct> > BitMapVector;
			BitMapVector BitMapGlyphs;
			Vector3 RowSize;
		};

		// private Typedefs
		typedef std::map< BD_UCHAR8, Glyph> GlyphMap;
		typedef std::pair< BD_UCHAR8, Glyph> GlyphMapPair;
		typedef std::vector< TextureGlyphRowStruct > GlyphRowVector;


		void Unload( );
		void LoadGlyphs( BD_BYTE * p_pPixelBuffer, const Vector3 p_Size,
			GlyphRowVector * p_pGlyphRows, BD_FLOAT32 * p_pVertexCoords, BD_FLOAT32 * p_pTextureCoords );

		void LoadGlyphsMonochrome( BD_BYTE * p_pPixelBuffer, const Vector3 p_Size,
			GlyphRowVector * p_pGlyphRows, BD_FLOAT32 * p_pVertexCoords, BD_FLOAT32 * p_pTextureCoords );

		void CreateGlyphVertexData( BD_FLOAT32 * p_pVertexCoords, BD_FLOAT32 * p_pTextureCoords, Vector3 p_TextureSize,
			BD_UINT32 p_Index, FT_Bitmap * p_pBitmap, FT_BitmapGlyph * p_pGLyph, Vector3 p_GLyphPosition );
		
		BD_UINT32 LoadShaders( );
		
		BD_BOOL m_Loaded;
		Renderer & m_Renderer;
		FT_Library m_FreeTypeLibrary;
		FT_Face m_FreeTypeFace;
		BD_UINT32 m_Size;
		Glyph * m_pGlyphs[ 256 ];
		VertexObject * m_pVertexObject;
		Texture * m_pTexture;
		ShaderProgram * m_pShaderProgram;
		Shader * m_pVertexShader;
		Shader * m_pFragmentShader;
		
		static BD_UCHAR8 s_DefaultCharset[];

	};

}

#endif
